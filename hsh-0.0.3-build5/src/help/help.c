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
				isdown=true;
			}
			else if(buf[i]=='_'&&isdown==true) {
				isdown=false;
			}
			else if(buf[i]=='|'&&isreverse==false) {
				isreverse=true;
			}
			else if(buf[i]=='|'&&isreverse==true) {
				isreverse=false;
			}
			else if(buf[i]=='#') {
				if(ishl) ishl=false;
				else ishl=true;
			}
			else {
				if(isdown==true) {
					printf("\033[4m");
				}
				if(isreverse==true) {
					printf("\033[7m");
				}
				if(ishl) {
					printf("\033[1m");
				}
				printf("%c\033[0m", c);
			}
		}
	}
}
int hsh_help(char *arg) {
	printf("HSH帮助%s。", "0.0.1");
	char *hcmd=malloc(512);
	memset(hcmd, '\0', 512);
	if(arg==NULL) scanf("%s", hcmd);
	else { strcpy(hcmd, arg); putchar('\n'); }
	char *hrcmd=malloc(512);
	memset(hrcmd, '\0', 512);
	strcpy(hrcmd, "/usr/share/hsh/help/");
	strcat(hrcmd, hcmd);
	strcat(hrcmd, ".help");
	FILE *file=fopen(hrcmd, "r");
	if(file==NULL) {
		printf("文件未找到：%s。请检查是否输入正确。\n", hrcmd);
		return 1;
	}
	if(strcmp(hrcmd, "/usr/share/hsh/help/.help")==0) {
		printf("help: 请输入命令行选项。\n");
	}
	hdoc(file);
	return 0;
}
