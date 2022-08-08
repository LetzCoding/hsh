void *hsh_wait()
{
	while(1) {
		//printf("\033[31m|\b");
		putchar('|');
		putchar('\b');
		usleep(60);
		//printf("\033[32m/\b");
		putchar('/');
		putchar('\b');
		usleep(60);
		//printf("\033[33m-\b");
		putchar('-');
		putchar('\b');
		usleep(60);
		//putchar('\\');
		//putchar('\b');
		//usleep(60);
	}
}
