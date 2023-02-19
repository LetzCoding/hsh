# 由configure生成的Makefile
helpdir="/home/hangco/.hsh/help/"
hshdir="/home/hangco/.hsh"
sampledir="/home/hangco/.hsh/samples/"
configadr="/home/hangco/.hsh/config"
CC="gcc"
install:
	make compile
	make config
	make gencfg
compile: main.c userspec.h
	$(CC) main.c -g -static -o hsh
config: ../help/*
	rm -rf $(hshdir)
	mkdir $(hshdir)
	rm -rf $(helpdir)
	mkdir $(helpdir)
	rm -rf $(sampledir)
	mkdir $(sampledir)
	cp ../help/*.help $(helpdir)/
	cp gpl.txt $(hshdir)/
	cp ../samples/* $(sampledir)/
gencfg:
	$(CC) genFile.c -o genFile
	./genFile
	rm -f genFile
	mv config.skel $(configadr)
help:
	@echo "make install：编译并拷贝必需文件"
	@echo "make compile：编译文件"
	@echo "sudo make config：拷贝必须文件"
	@echo "make help：查看编译的帮助"
