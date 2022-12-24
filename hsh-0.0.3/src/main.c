#include <stdio.h>
#include <stdio_ext.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define VERSION "0.0.3"
#include "dm/dm.c"
#include "help/help.c"
int hshcmd(FILE *file) {
	bool usestdin=0;
	if(file==stdin) usestdin=1;
	if(usestdin) printf("正在启动HSH...\n");
	//int setvbuf(FILE *stream, char *buf, int mode, size_t size);
	if(setvbuf(file, NULL, _IONBF, 0)) {
		printf("\033[31m流设置失败。\033[0m\n");
		return 1;
	}
	if(usestdin) if(setvbuf(stdout, NULL, _IONBF, 0)) { printf("\033[31m流设置失败。\033[0m\n"); return 1; }
	char *cmd; char *arg=NULL;
	cmd=malloc(512); 
	memset(cmd, '\0', 512); 
	char inputed='\0';
	int line=0;
	int rtnum=0;
	if(usestdin) printf("HSH %s。\n", VERSION);
	while(1) {
		__fpurge(stdin);
		__fpurge(stdout);
		memset(cmd, '\0', 512);
		if(usestdin) printf("HSH> \033[32m");
		// 将文件内容读入内存
		for(int i=0; ; i++) {
			inputed=fgetc(file);
			if(inputed=='\n') {
				line++;
				cmd[i]=' ';
				if(i<512) cmd[i+1]='\0';
				break;
			}
			else cmd[i]=inputed;
		}
		printf("\033[0m");
		// 解析
		arg=strstr(cmd, " ");
		arg[0]='\0';
		arg++;
		arg[strlen(arg)-1]='\0';
		for(int i=0; i<strlen(cmd); i++) {
			cmd[i]=tolower(cmd[i]);
		}
		if(!strcmp(cmd, "exit")) {
			if(!strcmp(arg, "")) break;
			else {
				bool digtype=0;
				rtnum=0;
				if(arg[0]=='-') {
					digtype=1; // 负数
					arg++;
				}
				if(arg[0]=='+') {
					arg++;
				}
				for(int i=0; isalnum(arg[i]); i++) {
					if(digtype=0) rtnum=rtnum*10+(arg[i]-48);
					else rtnum=rtnum*10-(arg[i]-48);
				}
				break;
			}
		}
		else if(!strcmp(cmd, "help")) {
			hsh_help(arg);
		}
		else if(!strcmp(cmd, "hsh")) {
			if(!strcmp(arg, "")) hshcmd(stdin);
			else {
				FILE *file=fopen(arg, "r");
				if(file==NULL) {
					printf("文件未找到。\n");
					continue;
				}
				else hshcmd(file);
			}
		}
		else if(!strcmp(cmd, "echo")) {
			if(!strcmp(arg, "")) {
				printf("echo: 需要参数。\n");
			}
			else {
				printf("%s\n", arg);
			}
		}
		else if(!strcmp(cmd, "clear")) {
			printf("\033[2J\033[114514A");
		}
		else if(!strcmp(cmd, "ls")) {
			ls(arg);
		}
		else if(!strcmp(cmd, "read")) {
			hsh_read(arg);
		}
		else if(!strcmp(cmd, "//"));
		else {
			if(!strcmp(cmd, "")) continue;
			printf("\033[31m在第%d行发生错误\033[0m：\"%s %s\"不是命令。\n", line, cmd, arg);
		}
	}
	return rtnum;
}

int main() {
	int rt;
	rt=hshcmd(stdin);
	return rt;
}

