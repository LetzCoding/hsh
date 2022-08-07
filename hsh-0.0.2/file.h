// file.h
char *hsh_chdir()
{
    char *newdir=(char*)malloc(DEFAULTSIZE);
    for(int i=0; i<DEFAULTSIZE; newdir[i]='\0', i++);
    scoutput("目录名: ", 3*CNSIZE+2);
    kbinput(newdir, DEFAULTSIZE);
    if(access(newdir, 0)!=0) {
        scoutput("目录未找到。请重新输入位置。\n", CNSIZE*14+1);
        return NULL;
    } else {
        return newdir;
    }
}

int hsh_showfile(const char *nd, const char *filename)
{
    FILE *file;
    char *newname=(char*)malloc(DEFAULTSIZE);
    //for(int i=0; i<DEFAULTSIZE; newname[i]='\0', i++);
    memset(newname, DEFAULTSIZE, '\0');
	*newname=*nd;
	strcat(newname, nd);
    strcat(newname, "/");
    strcat(newname, filename);
    printf("\n");
    if(access(newname, 4)) {
        scoutput("错误：文件不可读。\n", CNSIZE*9+1);
		printf("%s, %s\n", newname, filename);
        return 1;
    }
    printf("%s的内容\n", newname);
    file=fopen(newname, "r");
    size_t filesize=0, lines=1;
    bool line=0;
    printf("%ld\t", lines);
    lines++;
    for(char c='\0'; (c=fgetc(file))!=EOF; filesize++) {
        putchar(c);
        if(c=='\n') printf("%ld\t", lines), lines++, line=1;
        if((lines%10==0)&&(line==1)) {
            line=0;
            printf("\n按下回车继续输出。。。");
            if(getchar()=='\n') {
                printf("%ld\t", lines);
                lines++;
                continue;
            }
        }
    }
    printf("\n文件大小：%ld\n", filesize);
    return 0;
}

int hsh_writefile_w(const char *nd, const char *filename)
{
	FILE *file;
    char *newname=(char*)malloc(DEFAULTSIZE);
    memset(newname, DEFAULTSIZE, '\0');
	*newname=*nd;
	strcat(newname, nd);
    strcat(newname, "/");
    strcat(newname, filename);
    printf("\n");
    //if(access(newname, R_OK)&&access(newname, W_OK)) {
        //scoutput("错误：文件不可读写。\n", CNSIZE*10+1);
		//printf("%s, %s\n", newname, filename);
        //return 1;
    //}
	scoutput("警告！请确认您想要重写该文件！您之前所作的内容将会全部消失！\n", CNSIZE*30+1);
	scoutput("请输入y或者n: ", CNSIZE*6+1);
	char is;
	is=getchar();
	if(is=='N'||is=='n') {
		printf("取消。\n");
		return 0;
	}
	else {
		printf("%s\n", newname); //debug
		file=fopen(newname, "w+");
		char *buffer=(char*)malloc(DEFAULTSIZE*2);
		memset(buffer, DEFAULTSIZE*2, '\0');
		char c='\0';
		short getout=0;
		int i=0;
		printf("命令模式，请输入命令。\n");
		printf("命令列表：\n1: i: 输入。\n2. q: 退出。\n");
		for(i=0; i<DEFAULTSIZE*2; i++) {
			putchar('|');
			c=getchar();
			buffer[i]=c;
			if(buffer[i]=='i') {
				memset(buffer, DEFAULTSIZE*2, '\0');
				c='\0';
				printf("输入\"GeToUt\"退出编辑模式。\n");
				for(i=0; i<DEFAULTSIZE*2; i++) {
					c=getchar();
					if(c=='G'&&getout==0) {
						/*if(getout==0) */getout++;
					}
					else if(c=='e' && getout==1) {
						/*if(getout==1) */getout++;
						//else getout=0;
					}
					else if(c=='T' && getout==2) {
						/*if(getout==2) */getout++;
						//else getout=0;
					}
					else if(c=='o' && getout==3) {
						/*if(getout==3) */getout++;
						//else getout=0;
					}
					else if(c=='U' && getout==4) {
						/*if(getout==4) */getout++;
						//else getout=0;
					}
					else if(c=='t' && getout==5) {
						/*if(getout==5) */getout++;
						//else getout=0;
					}
					else if(getout==6) {
						printf("退出编辑模式。\n");
						break;
					}
					else {
						//buffer[i]=c;
						//printf("%s\n", buffer); //debug
						printf("%c", c);
						fputc(c, file);
						getout=0;
					}
				}
			}
			else if(buffer[i]=='q') {
				fclose(file);
				return 0;
			}
		}
	}
}
