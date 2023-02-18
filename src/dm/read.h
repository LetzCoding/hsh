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
		int charNumInSingleLine=0; // XD
		size_t filesize=0, lines=1, realLines=1;
    	bool line=0;
    	printf("\033[35m%ld\t\033[0m", lines);
    	lines++;
    	for(char c='\0'; (c=fgetc(file))!=EOF; filesize++) {
        	putchar(c);
			charNumInSingleLine++;
	        if(c=='\n') {
				printf("\033[35m%ld\t\033[0m", lines);
				lines++;
				realLines++;
				line=1;
				charNumInSingleLine=0;
			}
    	    if((realLines%30==0)&&(line==1)) {
    	        line=0;
        	    printf("\n\033[32m按下回车继续输出。。。\033[0m");
				char abc=getchar();
            	if(abc=='\n') {
                	printf("\033[35m%ld\t\033[0m", lines);
	                lines++;
					realLines++;
    	            continue;
        	    }
				if(abc==EOF) {
					printf("\033[31m退出read程序。\033[0m\n");
					goto readend;
				}
        	}
			if(charNumInSingleLine>=56) {
				printf("\n\t");
				realLines++;
				charNumInSingleLine=0;
			}
    	}
		readend:
	    printf("\n\033[32m读取的数据量：%ld字节。\n\033[0m", filesize);
		fclose(file);
		return 0;
	}
}

