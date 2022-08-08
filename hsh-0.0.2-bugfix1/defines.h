// language: C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "waiting.c"
#define DEFAULTSIZE 1024
#define VERSION "0.0.2-bugfix1"
#define CNSIZE 3
// 注意！一个汉语字符占3个字节！！！
#define AUTHOR "Hangco"
const char logo[] = "\033[35m.......................................\n.....@@.....@@..*@@@@@@`..@@.....@@....\n.....@@.....@@..@@........@@.....@@....\n.....@@@@@@@@@..,@@@@.....@@@@@@@@@....\n.....@@.....@@......[@@^..@@.....@@....\n.....@@.....@@..,.....@@..@@.....@@....\n.....@@.....@@..@@@@@@*...@@.....@@....\n.......................................\n\033[0m";
// size_t:
// long long unsigned int
// or
// long unsigned int
size_t kbinput(char *s, size_t size)
{
    size_t nsize;
    if(size==0) nsize=DEFAULTSIZE;
    else nsize=size;
    size_t i;
    char c;
    for(i=0; i<nsize; i++) {
        c=getchar();
        if(c=='\n') {
            s[i]=='\0';
            break;
        } else s[i]=c;
    }
    return i;
}

size_t scoutput(char *s, size_t size)
{
    for(int i=0; i<size; i++) {
        if(s[i]=='\0') break;
        else putchar(s[i]);
    }
}

void geterr(int err)
{
    if(err==0) return;
    else {
        if(err==127) {
            scoutput("错误：未找到。\n", 22);
        } else if(err==1) {
            scoutput("错误：文件未找到。\n", 9*CNSIZE+1);
        } else {
            printf("无法识别的错误，错误码为%d。\n", err);
        }
    }
}
