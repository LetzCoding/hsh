#include <stdio.h>
int main() {
	FILE *f=fopen("config.skel", "w");
	fprintf(f, "1"); // showdir=1
	for(int i=0; i<1023; i++) {
		fputc('\0', f);
	}
	fclose(f);
	return 0;
}
