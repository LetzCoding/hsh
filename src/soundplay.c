// soundplay: used PulseAudio to make sounds
// modiefied from PulseAudio sample files
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fcntl.h>
#include <errno.h>
#include <pulse/simple.h>
#include <pulse/error.h>

int soundplay(char *arg) {
	// the sample format
	static const pa_sample_spec ss = {
		.format=PA_SAMPLE_S16LE,
		.rate=44100,
		.channels=2
	};
	pa_simple *s=NULL;
	int ret=1, error;
	// read from file
	if(!strcmp(arg, "")) {
		printf("soundplay: 参数不足。\n");
		return 1;
	}
	else {
		FILE *f=fopen(arg, "r");
		if(f==NULL) {
			printf("soundplay: 没有“%s”文件。", arg);
			return 2;
		}
		fclose(f);
	}
	// create stream
	if(!(s=pa_simple_new(NULL, "hsh_soundplay", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
		printf("\033[31m错误\033[0m: pa_simple_new()失败（错误码%s）。\n", pa_strerror(error));
		goto finish;
	}
	for(;;) {
		uint8_t buf[1024];
		ssize_t r;
#if 0
	pa_usec_t latency;
	if((latency=pa_simple_get_latency(s, &error))==(pa_usec_t)-1) {
		printf("\033[31m错误：pa_simple_get_latency()失败（错误码%s）。\n", pa_strerror(error));
		goto finish;
	}
	printf("%0.0f usec	\r", (float)latency);
#endif
	// 读取数据
	int fd=open(arg, 0); //read only
	if((r=read(fd, buf, sizeof(buf)))<=0) {
		if(r==0) { // EOF
			break;
		}
		printf("\033[31m错误\033[0m: 文件读取失败。\n");
		goto finish;
	}
	// 播放！！
	if((pa_simple_write(s, buf, (size_t)r, &error))<0) {
		printf("\033[31m错误\033[0m: 音频输出失败。\n");
		goto finish;
	}
	}
	if(pa_simple_drain(s, &error)<0) {
		printf("\033[31m错误\033[0m: pa_simple_drain()失败。\n");
		goto finish;
	}
	ret=0;
finish:
	if(s) pa_simple_free(s);
	return ret;
}

