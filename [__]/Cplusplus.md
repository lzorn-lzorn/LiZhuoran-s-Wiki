#### 内存分配器
### 内存
> **malloc 和 new 的区别**

回答: `malloc` 是一个C语言的内存分配器。只负责分配内存, 不会调用构造函数。但是`new` 在分配内存的同时还会调用构造函数。

但是如果构造函数抛出异常, 则已经分配好的内存无法复用。所以我们会常常将这两个操作进行分离: ::operator new + placement new
```C++
void* memory = ::operator new(sizeof(Foo));
Foo* obj = new (memory) Foo(args...);
```

**以这个问题作为出发点**:
在C++17中, 往往我们更加推荐使用内存分配器 `std::allocator<_Ty>{}.allocate(count)` 而不是 `malloc`
其中的原因是:
1. `std::allocator<_Ty>{}.allocate(count) -> _Ty*` 是类型安全的, 而`malloc` 统一返回 `void*`
2. `std::allocator<_Ty>{}.allocate(count)` 可以通过 `std::allocator_traits<Alloc>` 获得更多的元信息, 同时可以自定义分配器
3. `std::allocator<_Ty>{}.allocate(count)` 是现代 C++ 的接口能获得更多优化的可能, 例如编译期内存分配`constexpr`. 

同时 malloc/::operator new 的对齐类型是 `alignof(std::max_align_t)` 即也就是 16 字节. 但是现代的内存分配器是不存在这个问题的。(在新标准C++20中的 `::operator new` 也不存在这样的问题)
(这个实际上也不是问题, 因为 malloc 是 glibc++ 提供的函数, 如果 malloc 支持对齐到更高位的话, 会导致系统出现非常多的内部虽然, 同时也拖慢性能)
如果说你希望手动实现更高的内存对齐, 可以参考 glibc 中 malloc 实现.
> ```C++
> template <typename T>
> T* allocate_aligned(size_t alignment, size_t size) {
>     // 1. 分配额外空间存储原始指针（用于释放）
>    size_t header_size = sizeof(void*);
>    size_t total_size = size + alignment - 1 + header_size;
>    // 2. 分配原始内存
>    void* original_ptr = ::operator new(total_size);
>    // 3. 计算对齐后的地址
>    // glibc 中的掩码操作
>    void* aligned_ptr = reinterpret_cast<void*>(
>        (reinterpret_cast<uintptr_t>(original_ptr) + header_size + alignment - 1) 
>        & ~(alignment - 1)
>    );
>    // 4. 在对齐地址前存储原始指针
>    *(reinterpret_cast<void**>(aligned_ptr) - 1) = original_ptr;  
>    return static_cast<T*>(aligned_ptr);
> }
> template <typename T>
> void deallocate_aligned(T* ptr) {
>     // 1. 取出原始指针
>     void* original_ptr = *(reinterpret_cast<void**>(ptr) - 1);  
>     // 2. 释放内存
>     ::operator delete(original_ptr);
> }
> ```


在以前的C++程序中, 我们更多使用 placement new operator 来在一块特定的内存上调用构造函数. 
placement new 最危险的地方在于, 其不符合 RAII 的思想。使用 placement new 构造的对象需要手动析构
```C++
alignas(T) unsigned char buf[sizeof(T)];
T* ptr = new (buf) T;
// ...
ptr->~T(); // 手动析构
```
同时, `T* ptr = new (nullptr) T;` 是未定义行为, 但是 对于老是的内存分配器是会在内存分配失败的时候直接返回 nullptr 的。 
最后, 作为补充, 如果你重写了 operator new 但是没有重写 operator delete会出现内存泄漏。


在现代 C++ 程序中,我们同样的倾向于将 new 这个操作分成两操作: 
```Cpp
auto ptr = std::allocator<_Ty>().allocate(1);
auto obj = std::construct_at(ptr, ...); // ... 是构造器的参数
```
这也是更现代的做法.


> 术语普及: 何为 "状态"
> 本质上状态就是内存栈帧, Eg:
> ```Cpp
> struct A {
>   bool a, b;   
> };
> ```
> 那么此时 A 一共就会有 4 种状态 `{true, true}, {true, false}, {false, true}, {false, false}`
> 一个非常暴力的理解就是, <u>只要一个结构或函数存在内部变量, 那么他就是有状态的. 反之, 如果一个结构或者函数没有内部变量, 就说其是无状态的</u>。
> (实际上, 有状态在一些语境下被认为是不安全的, 所有 bug 的本质就是程序的进入了一个非法的状态, 也就是内存栈帧出现了未定义的取值)
> 在 C++ 中, 所谓 "无状态的分配器" 或者 "无状态的比较器" 等等。都是指代 struct 中没有变量, 只有函数和元信息。
> 之后会非常广泛的用到这个术语
>
> [CPP STD对可调用对象的要求](https://en.cppreference.com/w/cpp/named_req/Callable)
> [CPP STD对Allocator的要求](https://en.cppreference.com/w/cpp/named_req/Allocator)





#### 智能指针


