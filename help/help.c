// 已经include了。。。
int hdoc(FILE *file) {
	char c='\0', *buf=malloc(512);
	bool isdown = false, isreverse=false, ishl=false;
	for(int i=0; ; i++) {
		memset(buf, '\0', 512);
		c=fgetc(file);
		if(c==EOF) return 0;
		buf[i]=c;
		if(c=='\\') {
			if(isdown) printf("\033[4m%c\033[0m", (c=fgetc(file)));
			if(isreverse) printf("\033[7m%c\033[0m", (c=fgetc(file)));
			else putchar(c=fgetc(file));
		}
		else {
			if(buf[i]=='_'&&isdown==false) {
				printf("\033[4m");
				isdown=true;
			}
			else if(buf[i]=='_'&&isdown==true) {
				printf("\033[0m");
				isdown=false;
			}
			else if(buf[i]=='|'&&isreverse==false) {
				printf("\033[7m");
				isreverse=true;
			}
			else if(buf[i]=='|'&&isreverse==true) {
				printf("\033[0m");
				isreverse=false;
			}
			else if(buf[i]=='#') {
				if(ishl) {
					ishl=false;
					printf("\033[0m");
				}
				else { 
					ishl=true;
					printf("\033[1m");
				}
			}
			else {
				if(isdown==true) {
				}
				if(isreverse==true) {
				}
				if(ishl) {
				}
				printf("%c", c);
			}
		}
	}
}
int hsh_help(char *arg) {
	printf("HSH帮助%s, HDOC 0.2。", "0.0.1");
	char *hcmd=malloc(512);
	memset(hcmd, '\0', 512);
	strcpy(hcmd, arg); putchar('\n');
	if(!strcmp(hcmd, "")) {
		printf("用法：help <命令名>，help intro显示命令列表。\n");
		return 1;
	}
	char *hrcmd=malloc(512);
	memset(hrcmd, '\0', 512);
	strcpy(hrcmd, "/usr/share/hsh/help/");
	strcat(hrcmd, hcmd);
	strcat(hrcmd, ".help");
	FILE *file=fopen(hrcmd, "r");
	if(file==NULL) {
		printf("对不起，暂无此命令的帮助。\n");
		return 1;
	}
	if(strcmp(hrcmd, "/usr/share/hsh/help/.help")==0) {
		printf("help: 请输入命令行选项。\n");
	}
	else hdoc(file);
	return 0;
}
