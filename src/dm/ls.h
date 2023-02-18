int ls(char *shellDir, char *arg) {
	char *dirName=malloc(512);
	memset(dirName, '\0', 512);
	strcpy(dirName, shellDir);
	DIR *dir;
	struct dirent *dp;
	if(!strcmp(arg, "")) dir=opendir(dirName);
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


