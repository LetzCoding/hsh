#include "defines.h"
#include "help.c"
#include "file.h"
int main(int argc, char *argv[], char **env) {
	pthread_t *threadid=(pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(threadid, NULL, hsh_wait, NULL);
	scoutput("正在加载变量。\n", CNSIZE*7+1);
	char *cmd=(char*)malloc(DEFAULTSIZE);
	int rt=0;
	scoutput("正在加载文件。\n", CNSIZE*7+1);
	FILE *file=NULL;
	char *dir=(char*)malloc(DEFAULTSIZE);
	//char *newdir=(char*)malloc(DEFAULTSIZE);
	for(int i=0; i<DEFAULTSIZE; dir[i]=='\0', i++);
	//for(int i=0; i<DEFAULTSIZE; newdir[i]=='\0', i++);
	dir="/";
	//newdir=dir;
	printf("完成。");
	sleep(1);
	pthread_cancel(*threadid);
	//for(int i=0; i<DEFAULTSIZE; putchar('\n'), i++);
	//printf("\nHSH %s, 由%s制作。\n", VERSION, AUTHOR);
	printf("\n\033[32mHSH\033[36m %s\033[0m, 由\033[35m%s\033[0m制作。\n", VERSION, AUTHOR);
	while(1) {
		for(int i=0; i<DEFAULTSIZE; cmd[i]='\0', i++);
		printf("\033[33m> \033[0m");
		kbinput(cmd, DEFAULTSIZE);
		if(cmd[0]=='e'&&cmd[1]=='x'&&cmd[2]=='i'&&cmd[3]=='t'&&cmd[4]=='\0') {
			printf("退出。\n");
			break;
		}
		else if(cmd[0]=='h'&&cmd[1]=='e'&&cmd[2]=='l'&&cmd[3]=='p'&&cmd[4]=='\0') {
			rt=hsh_help();
		}
		else if(cmd[0]=='c'&&cmd[1]=='l'&&cmd[2]=='e'&&cmd[3]=='a'&&cmd[4]=='r'&&cmd[5]=='\0') {
			printf("\033[2J");
		}
		else if(cmd[0]=='c'&&cmd[1]=='d'&&cmd[3]=='\0') {
			dir=hsh_chdir();
			//newdir=dir;
		}
		else if(cmd[0]=='p'&&cmd[1]=='w'&&cmd[2]=='d') {
			printf("当前目录：%s\n", dir);
		}
		else if(cmd[0]=='r'&&cmd[1]=='e'&&cmd[2]=='a'&&cmd[3]=='d'&&cmd[4]=='\0') {
			char *s=(char*)malloc(DEFAULTSIZE);
			for(int i=0; i<DEFAULTSIZE; s[i]='\0', i++);
			//printf("%s\n", dir);
			scoutput("输入文件名：", 6*CNSIZE);
			kbinput(s, DEFAULTSIZE);
			//gets(s);
			//printf("%s, %s\n", dir, s);
			hsh_showfile(dir, s);
			//printf("%s, %s\n", dir, s);
		}
		else if(cmd[0]=='w'&&cmd[1]=='e'&&cmd[2]=='d'&&cmd[3]=='i'&&cmd[4]=='t'&&cmd[5]=='\0') {
			char *s=(char*)malloc(DEFAULTSIZE);
			for(int i=0; i<DEFAULTSIZE; s[i]='\0', i++);
			//printf("%s\n", dir);
			scoutput("输入文件名：", 6*CNSIZE);
			//gets(s);
			kbinput(s, DEFAULTSIZE);
			//printf("%s, %s\n", dir, s);
			hsh_writefile_w(dir, s);
			//printf("%s, %s\n", dir, s);
		}
		else if(cmd[0]=='v'&&cmd[1]=='e'&&cmd[2]=='r') {
			printf("%s", logo);
			printf("HSH, Version %s.\n", VERSION);
			printf("这个软件在GNU GPL v3协议下开源。\n");
		}
		else {
			if(cmd[0]=='\0') continue;
			else printf("\033[31m错误\033[0m：命令未找到。\n");
		}
		if(rt!=0) {
			geterr(rt);
		}
	}
	return 0;
}
