![[Git的基本命令概览.excalidraw|800]]

# 基础用法
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

# 多人协作场景
如果你希望能为某一个开源库提交代码, 你应该先将对方的库 fork 到自己的仓库，然后你需要建立一个自己的分支而不是直接在主分支上工作。你开发结束之后先同步最新的分支然后修改冲突, 提交RP, 合并之后删除你的本地分支
以下工作流总结于 [[#Reference|4.reference]] 
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

# Git 使用规范

# Reference
1. [Git 使用规范 from 阮一峰](https://www.ruanyifeng.com/blog/2015/08/git-use-process.html)
2. [常用Git命令清单 from 阮一峰](https://www.ruanyifeng.com/blog/2015/12/git-cheat-sheet.html)
3. [Git远程操作详解 from 阮一峰](https://www.ruanyifeng.com/blog/2014/06/git_remote.html)
4. [十分钟学会正确的github工作流，和开源作者们使用同一套流程_哔哩哔哩_bilibili from 码农高天](https://www.bilibili.com/video/BV19e4y1q7JJ/?spm_id_from=333.337.search-card.all.click&vd_source=75cdf78dd1707c1077825f0501243c43)
