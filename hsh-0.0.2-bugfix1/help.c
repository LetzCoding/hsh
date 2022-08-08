int hsh_help();
int hsh_help()
{
    scoutput("欢迎来到HSH帮助，版本为", CNSIZE*11);
    printf("%s。\n", VERSION);
    scoutput("输入q来退出。\n", CNSIZE*6+2);

    char *cmd=(char*)malloc(DEFAULTSIZE);
    while(1) {
        for(int i=0; i<DEFAULTSIZE; cmd[i]='\0', i++);
        scoutput("HELP ", 5);
        kbinput(cmd, DEFAULTSIZE);
        if(cmd[0]=='q'&&cmd[1]=='\0') break;
        else if(cmd[0]=='e'&&cmd[1]=='x'&&cmd[2]=='i'&&cmd[3]=='t') {
            printf("exit: 退出HSH。\n%s",
				   "您可以通过输入exit命令退出HSH。返回值总是1。\n");
		}
		else if(cmd[0]=='w'&&cmd[1]=='e'&&cmd[2]=='d'&&cmd[3]=='i'&&cmd[4]=='t') {
			printf("wedit: 重写型的编辑器。\n%s%s%s%s%s", 
				   "wedit是一个（真）最小化的ex编辑器。\n",
				   "它有2个命令：i和q。\n",
				   "i命令是编辑模式，它可以通过输入GeToUt来退出。\n",
				   "q命令是退出，它会返回0.\n",
				   "已知的一个bug是：你不可能输入大写的G到你的文件里。\n");
        } else {
            scoutput("help: 命令未找到。\n", CNSIZE*6+7);
        }
    }
}
