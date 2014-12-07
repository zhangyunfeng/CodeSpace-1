1 安装git for windows 一般有个命令行还有个gui的东西，比如git gui和 git bash
2 配置好个人的git信息
	查看git配置信息： git config --list
 	配置用户名：	git config --global user.name  "username"
 	配置email: 		git config --global user.email "username@exmple.com"

3 安装配置好git 之后创建一个文件夹，比如d盘下面下面创建codespace

4 然后使用git clone 将github上面的代码同步下来
	git clone https://github.com/wuyougongzi/CodeSpace

5 然后提交一个文件上去试一下
	记得进入到包含.git的那个目录下面 cd 
	创建一个本地文件：test.txt
	添加文件： git add text.txt	
	commit :   git commit -m "message"
	一般来说避免冲突： git pull --rebase
	push: git push origin master 



注意：提交的文件最好采用utf-8 不带bom的