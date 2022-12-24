install:
	make compile
	make config
compile: main.c
	gcc main.c -o hsh
config: help/*
	 rm -rf /usr/share/hsh
	 mkdir /usr/share/hsh
	 cp help/*.help /usr/share/hsh
	 cp help/.help /usr/share/hsh
