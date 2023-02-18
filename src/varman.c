// 所有提供的函数：
//int newvar(); //新建变量
//int delvar(int num); //删除变量
//int inputvar(int num) //输入变量
//int cmodvar(int num, char *new); 
//int imodvar(int num, int new); //改变变量内容
//char * crtvar()
//int irtvar()

// 变量管理
typedef struct {
	char *con;
	int intcon;
	bool used;
} HVar;

// 变量表
#define MAXVAR 128
HVar varList[MAXVAR]; // 正式登记的变量表
int var=-1; // 正在使用的变量

// 新建变量
int newvar() { // 返回值为它在变量表中的位置
	for(int i=0; i<MAXVAR; i++) {
		if((varList[i].used)==0) {
			//varList[i].con=malloc(512); // 分配内容
			//if(varList[i].con==NULL) return -2; // 没有剩余空间
			varList[i].intcon=0;
			varList[i].used=1; // 标注此变量为“已用”
			return i;
		}
	}
	return -1; // 没有空闲的变量
}

// 删除变量
int delvar(int num) {
	if(varList[num].used) {
		free(varList[num].con); // 清空内容
		varList[num].con=NULL;
		varList[num].used=0; // 解除占用
		varList[num].intcon=0;
		return 0;
	}
	else return -1; // 本来就是空闲的
}

// 输入变量
int inputvar(int num) {
	varList[num].con=malloc(512);
	memset(varList[num].con, '\0', 512);
	char x;
	int i=0;
	while((x=getchar())!='\n') {
		varList[num].con[i]=x;
		i++;
	}
	varList[num].con[i]='\0';
	varList[num].intcon=atoi(varList[num].con);
	return 0;
}

// 访问变量内容
char *crtvar(int num) {
	return varList[num].con;
}

int irtvar(int num) {
	return varList[num].intcon;
}

// 设置变量
int cmodvar(int num, char *new) {
	if(strlen(new)>512);
	else {
		varList[num].con=malloc(512);
		memset(varList[num].con, '\0', 512);
		int x=strlen(new);
        size_t i;
        for (i=0; i<x && new[i] != '\0'; i++)
        	varList[num].con[i] = new[i];
        varList[num].con[x] = '\0';
	}
	return 0;
}
int imodvar(int num, int new) {
	varList[num].intcon=new;
	return 0;
}

// 确认正在使用
bool isusing(int num) {
	return varList[num].used;
}

