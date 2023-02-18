int dm_cd(char *nd, char *arg) {
	if(!strcmp(arg, "")) {
		printf("cd: 需要参数。\n");
		return 1;
	}
	char *dir=malloc(512);
	memset(dir, '\0', 512);
	if((strncmp(arg, "..", 2)==0)&&(strcmp(nd, "/")!=0)) {
		int i;
		for(i=strlen(nd); i>0; i--) {
			if(nd[i]=='/') {
				break;
			}
		}
		strcpy(dir, nd);
		dir[i]='\0';
		//printf("dir: %s, i: %d\n", dir, i);
	}
	else if(strncmp(arg, ".", 1)==0) {
		return 0;
	}
	else {
		strcpy(dir, arg);
		if(dir[0]!='/') {
			strcpy(dir, nd);
			strcat(dir, "/");
			strcat(dir, arg);
		}
	}
	DIR *direc;
	if((direc=opendir(dir))==NULL) {
		printf("cd: 目录“%s”未找到。\n", dir);
		return 2;
	}
	strcpy(nd, dir);
	closedir(direc);
	return 0;
}

