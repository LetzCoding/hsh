helpdir="/usr/share/hsh/help"
hshdir="/usr/share/hsh/"
install:
	make compile
	make config
compile: main.c
	gcc main.c -g -o hsh 
config: help/*
	 rm -rf $(helpdir)
	 mkdir $(helpdir)
	 cp help/*.help $(helpdir)
	 cp help/.help $(helpdir)
	 cp gpl.txt $(hshdir)
