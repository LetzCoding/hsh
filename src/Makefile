# 由configure生成的Makefile
helpdir="/usr/share/hsh/help"
hshdir="/usr/share/hsh"
install:
	make compile
	make config
compile: main.c
	gcc main.c -g -static -o hsh
config: ../help/*
	rm -rf $(hshdir)
	mkdir $(hshdir)
	rm -rf $(helpdir)
	mkdir $(helpdir)
	cp ../help/*.help $(helpdir)/
	cp gpl.txt $(hshdir)/
help:
	@echo "sudo make install：编译并拷贝必需文件"
	@echo "make compile：编译文件"
	@echo "sudo make config：拷贝必须文件"
	@echo "make help：查看编译的帮助"
