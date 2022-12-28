#include <stdio.h>
#include <stdio_ext.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define VERSION "0.0.3 build 7"
#define logo "\033[35m                                       \n\
    HHHH   HHHH  SSSSSS  HHHH   HHHH   \n\
     HH     HH  SS     S  HH     HH    \n\
     HHHHHHHHH   SSSS     HH@@@@@HH    \n\
     HH     HH      SSS   HH     HH    \n\
     HH     HH  S     SS  HH     HH    \n\
    HHHH   HHHH  SSSSSS  HHHH   HHHH   \n\
              \033[32m0.0.3 \033[36mBuild 7\033[35m            \n\033[0m"
#include "dm/dm.c"
#include "help/help.c"
#include "varman.c"
void showver() {
	printf("%s\n", logo);
	printf("\033[32mHSH %s\033[0m, \033[36m版权所有©Hangco, 2022\033[0m。\n", VERSION);
	printf("这个软件是基于GPL3的开源软件，要查看完整的GPL文档，请输入showGPL。\n");
}
void showGPL() {
	hsh_read("/usr/share/hsh/gpl.txt");
}
bool isstrblank(char *arg) {
	return (arg[0]=='\0')?1:0;
}
int hshcmd(FILE *infile) {
	bool usestdin=0;
	if(infile==stdin) usestdin=1;
	if(usestdin) printf("正在启动HSH...\n");
	//int setvbuf(FILE *stream, char *buf, int mode, size_t size);
	if(setvbuf(infile, NULL, _IONBF, 0)) {
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
	int opvar=-1; // 正在操作的变量
	if(usestdin) printf("HSH %s。如需帮助请输入help intro。\n", VERSION);
	while(1) {
		__fpurge(stdin);
		__fpurge(stdout);
		memset(cmd, '\0', 512);
		if(usestdin) printf("HSH> \033[32m");
		// 将文件内容读入内存
		for(int i=0; ; i++) {
			inputed=fgetc(infile);
			if(inputed=='\n') {
				line++;
				cmd[i]=' ';
				if(i<512) cmd[i+1]='\0';
				break;
			}
			if(inputed==EOF) {
				rtnum=20;
				break;
			}
			else cmd[i]=inputed;
		}
		printf("\033[0m");
		// 解析
		char *arg=strstr(cmd, " ");
		arg[0]='\0';
		arg++;
		arg[strlen(arg)-1]='\0';
		for(int i=0; i<strlen(cmd); i++) {
			cmd[i]=tolower(cmd[i]);
		}
		//printf("<%s> [%s]\n", cmd, arg);
		if(!strcmp(cmd, "exit")) {
			if(!strcmp(arg, "")) {
				rtnum=0;
				break;
			}
			else {
				rtnum=atoi(arg);
				break;
			}
		}
		else if(!strcmp(cmd, "help")) {
			hsh_help(arg);
		}
		else if(!strcmp(cmd, "hsh")) {
			int returnval=0;
			if(!strcmp(arg, "")) returnval=hshcmd(stdin);
			else {
				FILE *nfile=fopen(arg, "r");
				if(nfile==NULL) {
					printf("文件未找到。\n");
					continue;
				}
				returnval=hshcmd(nfile);
			}
			if(returnval!=0) {
				printf("返回代码：%d(0x%x)。\n", returnval, returnval);
				if(returnval==20) {
					printf("返回原因：读到EOF。\n");
				}
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
		else if(!strcmp(cmd, "newvar")) {
			opvar=newvar();
		}
		else if(!strcmp(cmd, "delvar")) {
			if(isstrblank(arg)) {delvar(opvar);}
			else {
				int delnum;
				delnum=atoi(arg);
				delvar(delnum);
			}
		}
		else if(!strcmp(cmd, "inputvar")) {
			if(isstrblank(arg)) {inputvar(opvar);}
			else {
				int numinput;
				numinput=atoi(arg);
				inputvar(numinput);
			}
		}
		else if(!strcmp(cmd, "cmodvar")) {
			cmodvar(opvar, arg);
		}
		else if(!strcmp(cmd, "imodvar")) {
			imodvar(opvar, atoi(arg));
		}
		else if(!strcmp(cmd, "ctrlvar")) {
			if(isstrblank(arg)) {printf("ctrlvar: 需要参数。\n"); continue;}
			int new; new=atoi(arg);
			opvar=new;
		}
		else if(!strcmp(cmd, "cechovar")) {
			if(isstrblank(arg)) {printf("%s\n", varList[opvar].con);}
			else {
				int new; new=atoi(arg);
				printf("%s\n", varList[new].con);
			}
		}
		else if(!strcmp(cmd, "iechovar")) {
			if(isstrblank(arg)) {printf("%d\n", varList[opvar].intcon);}
			else {
				int new; new=atoi(arg);
				printf("%d\n", varList[new].intcon);
			}
		}
		// the + - * / of the variables
		else if(!strcmp(cmd, "v+v")) {
			if(isstrblank(arg)) {
				continue;
			} else {
				// x=arg, y=y
				char *y=strstr(arg, " ");
				y[0]='\0';
				y++;
				y[strlen(y)]='\0';
				int a,b;
				a=atoi(arg); b=atoi(y);
				//printf("|%s| |%s|, |%d| |%d|\n", arg, y, a, b);
				varList[opvar].intcon=varList[a].intcon+varList[b].intcon;
			}
		}
		else if(!strcmp(cmd, "v-v")) {
			if(isstrblank(arg)) {
				continue;
			} else {
				char *x=strstr(arg, " ");
				x[0]='\0';
				x++;
				x[strlen(x)]='\0';
				int a,b;
				a=atoi(arg); b=atoi(x);
				varList[opvar].intcon=varList[a].intcon-varList[b].intcon;
			}
		}
		else if(!strcmp(cmd, "v*v")) {
			if(isstrblank(arg)) {
				continue;
			} else {
				char *x=strstr(arg, " ");
				x[0]='\0';
				x++;
				x[strlen(x)]='\0';
				int a,b;
				a=atoi(arg); b=atoi(x);
				varList[opvar].intcon=varList[a].intcon*varList[b].intcon;
			}
		}
		else if(!strcmp(cmd, "v/v")) {
			if(isstrblank(arg)) {
				continue;
			} else {
				char *x=strstr(arg, " ");
				x[0]='\0';
				x++;
				x[strlen(x)]='\0';
				int a,b;
				a=atoi(arg); b=atoi(x);
				varList[opvar].intcon=varList[a].intcon/varList[b].intcon;
			}
		}
		else if(!strcmp(cmd, "v%v")) {
			if(isstrblank(arg)) {
				continue;
			} else {
				char *x=strstr(arg, " ");
				x[0]='\0';
				x++;
				x[strlen(x)]='\0';
				int a,b;
				a=atoi(arg); b=atoi(x);
				varList[opvar].intcon=varList[a].intcon%varList[b].intcon;
			}
		}
		else if(!strcmp(cmd, "version")) {
			showver();
		}
		else if(!strcmp(cmd, "showgpl")) {
			showGPL();
		}
		else if(!strcmp(cmd, "//"));
		else {
			if(!strcmp(cmd, "")) continue;
			printf("\033[31m在第%d行发生错误\033[0m：\"%s %s\"不是命令。\n", line, cmd, arg);
		}
	}
	return rtnum;
}

int main(int argc, char *argv[]) {
	if(argc>1) {
		for(int i=1; i<argc; i++) {
			if(argv[i][0]=='-') continue;
			else {
				char *opened=malloc(512);
				memset(opened, '\0', 512);
				strcpy(opened, argv[i]);
				FILE *file=fopen(opened, "r");
				if(file==NULL) {
					printf("\033[31mHSH在初始化遭遇错误：文件“%s”未找到。\n\033[0m", opened);
					return -1;
				}
				int rt;
				rt=hshcmd(file);
				return rt;
			}	
		}
	}
	else {
		int rt;
		rt=hshcmd(stdin);
		return rt;
	}
}

