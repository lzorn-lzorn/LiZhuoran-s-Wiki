![[Git的基本命令概览.excalidraw|800]]
以下是术语的页内链接, 可以直接跳转(注意，如果你想知道更多指令使用细节请看文档 [[#^ae139a|Git文档]])：
- [[#^f3864a|git reset]]
	- [[#^f9fb1f|commit-hast]]
	- [[#^109b92|HEAD指针]]
- [[#^7a8959|git stash]]


# 工作流：基础用法
如果该项目基本是个人开发，也不会有什么人和你一起协同，那你可以在直接在你的主分支上开发(加粗的是git的关键字, 为加粗的是你要自己的)

1. 初始化本地文件夹为一个仓库 <b>git init</b>
2. 拉取一个Github远程的仓库, 这里最好是自己的：<b>git clone</b> URL
3. 你在本地开发...
4. 完成之后将对文件或者文件夹 <b>git add</b> "file-name" or "file-path" or .
5. 提交更改, 附带信息 <b>git commit -m</b> "…"
6. 推送到远程仓库 <b>git push</b> origin(远程仓库的名字) master(分支名)

这是一个基本用法, 如果你想使用这套流程：最好全程只有一个人给自己的仓库提交代码
![[Git基础工作流.excalidraw|800]]

可能会用到命令(以下只是简单描述命令功能更详细的说明见后或git文档): 
- 从暂存区中移除文件: <b>git rm</b> file-name
- 查看文件状态: <b>git status</b>
- 查询具体的修改: <b>git diff</b>
- 提交历史: <b>git log</b>
- 添加一个远程仓库: <b>git remote add</b> origin(名字)  URL(网址)

# 工作流：多人协作场景
如果你希望能为某一个开源库提交代码, 你应该先将对方的库 fork 到自己的仓库，然后你需要建立一个自己的分支而不是直接在主分支上工作。你开发结束之后先同步最新的分支然后修改冲突, 提交RP, 合并之后删除你的本地分支
以下工作流总结于[[#^353809|来自高天的分享]]
1. 首先对对方的分支使用\[fork] 到自己的仓库哦
2. 对于远端仓库:  <b>git clone</b> my-github.git
3. 在本地仓库 ：<b>git chenkout -b</b> my-feature
4. <可选>: 确认自己的修改: <b>git diff</b>
5. 写完之后, <b>git add</b> <changed_file> 上传至暂存区
6. 上传至本地仓库: <b>git commit -m</b>
7. 上传至远程仓库: <b>git push origin</b> my-feature
8. <如果远端有更新>: <b>git pull origin</b> master 同步更新至master分支
9. <此时你修改的代码还在my-fearture上, 远端的更新还没同步>: <b>git checkout</b> my-feature
10. <将远端和my-feature同步>: <b>git rebase</b> master, 意思是先不管我的更新把master的更新同步过来, 在把我的更新加入其中
11. <本地更新之后>: <b>git push -f origin</b> my-feature 同步至远程仓库的my-feature
12. <合并到主分支>: github上有个按钮 \[New pull request]
13. <同意之后>: 对方 \[Squash and merge]
14. <远端删除这个分支>: \[delete branch]
15. <处理本地分支>: <b>git branch -D</b> my-feature
16. <拉取最新的更新>: <b>git pull origin</b> master

![[多人协同的工作流.excalidraw|800]]

# Git的基本设定
Remote: 你的远程仓库
Repository：你的本地仓库
Index(or stage): git中的暂存区
Branch: 抽象概念-分支
Workspace: 你当前的工作区，也就是当前文件的一个切片

Git中的基本设定是你的本地文件夹在逻辑上有这样的一个划分：你在Workspace工作完上传到Index然后commit到Repository才算真的上传，才能push到Remote。
你的每一个commit都是一个版本，一个在某个Branch上的版本。git会把每一个版本的文件切片都保存，这样可以实现版本控制，每次push都会把该分支上的最新commit同步至远程。而不同分支往往会有不同的功能，最后在确认没有问题之后将所有的功能分支合并到master分支
![[git的基本设定.excalidraw|900]]

HEAD: head本质上是一个指针，它指向的是一个commit，一般情况下HEAD指针指向的commit和我们当前workspace的工作区应该是一致的(某些情况下会有detached head的情况)

git中有很多命令用来操作branch, commit, file。所以当我说到一个命令的参数是branch-level，就意味着他的参数是一个branch。commit-level, file-level 也是同理

# 添加至暂存区，提交以及撤销
使用 <b>git add</b> file-name/file-path 可以将文件(file-name)或文件夹(file-path)提交至暂存区
使用 <b>git commit -m</b> "..." 可以将暂存区的文件<b>一次性全部提交</b>至本地仓库, 由于是一次性全部提交, 所以一点一点add, 一点一点commit。如果暂存区此时有多个文件，你只想提交其中的几个，只能将剩余的全部<b>git reset</b> 然后再重新 commit。这里的 <b>-m</b> 是一定要加的

## git reset
reset 命令格式 <b>git reset</b> \[参数选项] \[参数] 以下列出具体的参数： ^f3864a

| 参数选项   | 参数          | 参数含义           | 功能                                           |
| ------ | ----------- | -------------- | -------------------------------------------- |
|        | file-name   | 文件名            | 重置暂存区的指定文件，与上一次commit保持一致，但工作区不变;            |
|        | commit-hash | commit对应的hash值 | 重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变            |
| --hard |             |                | 重置暂存区与工作区，与上一次commit保持一致:                    |
| --hard | commit-hash | commit对应的hash值 | 重置当前分支的HEAD为指定commit，同时重置暂存区和工作区，与指定commit一致 |
| –keep  | commit-hash | commit对应的hash值 | 重置当前HEAD为指定commit，但保持暂存区和工作区不变               |

git reset 的参数既可以是commit-level 也可以是一个file-level, 如果是一个file-leve就是取消文件的暂存(unstage file)

<b>commit-hash</b> 
commit-hash 是指你想将当前分支的指针重置到的特定提交的哈希值（commit hash）。每个提交都有一个唯一的哈希值，通常是一个长字符串（例如 `d1f2b3c`），你可以通过 `git log` 命令查看提交历史，找到想要重置到的提交的哈希值。 ^f9fb1f

<b>git stash [pop]</b>  ^7a8959
(pop可有可无)：暂时将未提交的变化移除，稍后再移入 

## git revert
<b>git revert</b>: 该命令允许你将你的错误commit回滚至某个正确的版本，并在LOG中增加一条新的revet commit.
EG: git revert HEAD~3 回滚到<b>最近第四次提交-the fourth last commit</b>
git revert -n master~5..master~2 回滚master分支上的从最近第五次到最近第三次提交(含最近第五次和最近第三次), 但是不会创建新的commit只是修改working tree和index

注意git revert的参数只能是一个commit-level不能是一个file-level的

## revert, reset 总结
<b>关于命令本身的含义</b>

| 命令       | 含义                                                                                         | 作用范围             |
| -------- | ------------------------------------------------------------------------------------------ | ---------------- |
| revert   | 专门用于回滚分支                                                                                   | 只能用于分支           |
| reset    | 重置：可以重置分支与某一次commit一致，也能重置文件                                                               | 既可以用于文件, 也可以用于分支 |
| checkout | 切换：对于文件就是切换回上次commit的状态；对于commit就是切换到特定的commit(因为HEAD没有动, 所以不能操作分支, 只能查看)；对于分支就是单纯切换到某一个分支 | 文件, 提交, 分支都已操作   |


<b>关于 HEAD 指针的变化</b> 
HEAD 指针指向当前分支的最新提交。在 Git 中，HEAD 用来表示当前检出的提交。当你在分支上工作时，HEAD 指向该分支的最新提交，执行 git commit 时，新提交会成为 HEAD 的新目标。 ^109b92

| 命令       | HEAD的变化                               | LOG                              |
| -------- | ------------------------------------- | -------------------------------- |
| revert   | 由于revert新建了一个commit去撤销, 所以HEAD会后移     | 之前的记录被保留                         |
| reset    | 更改指向的commit index                     | 被撤销的commit不会存在于LOG中, 被git的垃圾回收清理 |
| checkout | checkout commit之后会自动进入detached HEAD状态 |                                  |

![[reset, revert和checkout .excalidraw|900]]

# 分支的创建, 合并
```bash
# 恢复暂存区的指定文件到工作区
$ git checkout [file]

# 恢复某个commit的指定文件到暂存区和工作区
$ git checkout [commit] [file]

# 恢复暂存区的所有文件到工作区
$ git checkout .

```
# HEAD 指针




# Reference
1. [Git 使用规范 from 阮一峰](https://www.ruanyifeng.com/blog/2015/08/git-use-process.html)
2. [常用Git命令清单 from 阮一峰](https://www.ruanyifeng.com/blog/2015/12/git-cheat-sheet.html)
3. [Git远程操作详解 from 阮一峰](https://www.ruanyifeng.com/blog/2014/06/git_remote.html)
4. [十分钟学会正确的github工作流，和开源作者们使用同一套流程_哔哩哔哩_bilibili from 码农高天](https://www.bilibili.com/video/BV19e4y1q7JJ/?spm_id_from=333.337.search-card.all.click&vd_source=75cdf78dd1707c1077825f0501243c43) ^353809
5. [Git - Reference](https://git-scm.com/docs) ^ae139a
6. [Git|极客教程](https://geek-docs.com/git)
7. [ATLASSIAN GIT教程](https://www.atlassian.com/zh/git/tutorials/)
8. [git魔法：HEAD的指针变化 - 知乎](https://zhuanlan.zhihu.com/p/132406345)
