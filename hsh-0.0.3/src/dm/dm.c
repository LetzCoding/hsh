// dm: directory management ( 目录管理 )
#include <sys/types.h>
#include <dirent.h>
int ls(char *arg) {
	DIR *dir;
	struct dirent *dp;
	if(!strcmp(arg, "")) dir=opendir(".");
	else {
			dir = opendir(arg);
	}
	if(dir==NULL) {
		printf("错误：目录未找到。\n");
		return 1;
	}
	while ((dp = readdir(dir)) != NULL) {
		if (!(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")));
		else {
			if(dp->d_type==DT_DIR) printf("\033[34m\033[1m");
			if(dp->d_type==DT_LNK) printf("\033[32m");
			printf("%s ", dp->d_name);
			printf("\033[0m");
		}
	}
	printf("\n");
	closedir(dir);
	return 0;
}

int hsh_read(char *arg) {
	if((strcmp(arg, "")==1)||(arg==NULL)) {
		printf("read: 需要参数。\n");
		return 1;
	}
	else {
		FILE *file=fopen(arg, "r");
		if(file==NULL) {
			printf("错误：文件未找到。\n");
			return 1;
		}
		setvbuf(file, NULL, _IONBF, 0);
		char c;
		int line=1, charNumInSingleLine=0; // XD
		printf("\033[33m%d\t\033[0m", line);
		while(c!=EOF) {
			c=fgetc(file);
			if(c=='\n') {
				line++;
				printf("\n\033[33m%d\t\033[0m", line);
				charNumInSingleLine=0;
				continue;
			}
			if(charNumInSingleLine==60) {
				line++;
				printf("\n\033[33m%d_\t\033[0m", line);
				charNumInSingleLine=0;
				putchar(c);
				continue;
			}
			if(line%23==0) {
				printf("\033[32m按下回车继续...\033[0m");
				if(getchar()==EOF) {
					fclose(file);
					putchar('\n');
					return 0;
				}
				else {
					line++;
					printf("\n\033[33m%d\t\033[0m", line-1);
					continue;
				}
			}
			putchar(c);
			charNumInSingleLine++;
		}
		putchar('\n');
		fclose(file);
		return 0;
	}
}

