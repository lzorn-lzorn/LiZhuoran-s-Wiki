# 指定C/C++标准 
C_STD = /std:c11
CPP_STD = /std:c++20


all: main.exe List.dll
#(改动态链接)    cl /SUBSYSTEM:CONSOLE main.obj List.lib  # 链接 List.lib (导入库)

# /SUBSYSTEM:CONSOLE 可以不写, 如果是窗口要指定/SUBSYSTEM:WINDOW
# 静态链接
main.exe: main.obj List.lib
	cl /SUBSYSTEM:CONSOLE main.obj List.lib

# /c: 只编译不链接, 最后生成 .obj 文件
# 使用 main.c 和 List/List.h 生成 main.obj
main.obj: main.c List/List.h
	cl /c $(C_STD) main.c

# 使用 List.obj 直接生成 List.lib
List.lib: List.obj
	lib /out:List.lib List.obj

List.dll: List.obj
	link /dll /out:List.dll List.obj

List.obj: List/List.c List/List.h
	cl /c /FoList.obj $(C_STD) List/List.c

clean:
	del main.obj List.obj List.lib List.dll main.exe

# 打包目标，将文件拷贝到 package 目录结构
package: all
	if not exist package mkdir package
	if not exist package\include mkdir package\include
	if not exist package\lib mkdir package\lib
	copy List\List.h package\include
	copy List.lib package\lib
	copy List.dll package
	copy main.exe package
	del main.obj List.obj List.lib List.dll main.exe
	powershell Compress-Archive -Path package\* -DestinationPath package.zip
	rmdir /s /q package

# 安装目标，将文件拷贝到项目根目录下的指定目录
install: all
	if not exist install\include mkdir install\include
	if not exist install\lib mkdir install\lib
	if not exist install\source mkdir install\source
	copy List\List.c install\source	
	copy List\List.h install\include	
	copy List.lib install\lib	
	copy List.dll install	
	copy main.exe install
	del main.obj List.obj List.lib List.dll main.exe