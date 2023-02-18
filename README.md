# 读我 -- HSH
**HSH**是主要由Hangco开发的一款SHELL，使用C语言制作，运行于Linux/Unix上。它最新的版本是0.0.3 Build8。您可以通过编译的方式安装此软件。以下是编译的方法。

## 1. 下载存储库
HSH的下载主要可以通过两种方式：使用GIT或者直接下载。

### + 使用GIT获取软件源代码
如果需要使用GIT下载源代码，需要GIT软件。假设您已经拥有这款软件，请在**Bourne Shell或与其兼容的SHELL**中输入代码：
`git clone https://github.com/LetzCoding/hsh.git`
源代码将会被下载到您执行命令的地方的hsh目录中。

### + 直接下载
如果需要直接下载源代码，请点击这个界面中“Code”按钮的**“Download ZIP”**选项。

## 2. 生成Makefile
HSH使用自制的configure工具来生成Makefile。假设您已经位于“hsh”目录中了，那么请使用如下命令来生成Makefile： 
`cd src ./configure`
如果您发现configure文件无法执行，请使用如下命令来让其变成可执行文件：
`chmod 755 configure`或者`chmod u+x configure`
如果生成失败，您可能需要安装gcc编译器。

## 3. 编译
假设您位于刚刚提到的“hsh/src”目录中，则您需要使用如下命令来编译HSH：`make`
如果您发现权限不足，请使用`sudo make`。

## 4. 运行
HSH文件出现在您的src目录中。您可以通过`./hsh`运行此文件。如果需要更多帮助，请在HSH中输入`help intro`。

