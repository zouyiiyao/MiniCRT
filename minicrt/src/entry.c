// entry.c

#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char* argv[]);
void exit(int);

static void crt_fatal_error(const char* msg) {
	printf("fatal error: %s", msg);
	exit(1);
}

void mini_crt_entry(void) {
	int ret;

#ifdef WIN32
	int flag = 0;
	int argc = 0;
	char* argv[16];    // 最多16个参数
	char* cl = GetCommandLineA();

	/* 解析命令行 */
	argv[0] = cl;
	argc++;
	while (*cl) {
		if (*cl == '\"') {
			if (flag == 0) {
				flag = 1;
			} else {
				flag = 0;
			}
		} else if (*cl == ' ' && flag == 0) {
			if (*(cl + 1)) {
				argv[argc] = cl + 1;
				argc++;
			}
			*cl = '\0';
		}
		cl++;
	}
#else
	int argc;
	char** argv;

	char* ebp_reg = 0;
	asm ("movl %%ebp, %0 \n" : "=r"(ebp_reg));    // ebp_reg = %ebp

	/* 从栈中取调用main函数需要传入的参数 */
	argc = *(int*)(ebp_reg + 4);
	argv = (char**)(ebp_reg + 8);
#endif

	/* 初始化堆 */
	if (!mini_crt_heap_init()) {
		crt_fatal_error("heap initialize failed");
	}

	/* 初始化IO */
	if (!mini_crt_io_init()) {
		crt_fatal_error("IO initailize faile");
	}

	/* 调用main */
	ret = main(argc, argv);

	/* 进程结束，调用exit */
	exit(ret);
}

void exit(int exitCode) {
	/* 执行由atexit注册的退出回调函数 */
	// mini_crt_call_exit_routine();

#ifdef WIN32
	ExitProcess(exitCode);
#else
	/* sys_exit */
	asm ("movl %0,%%ebx \n\t"
	     "movl $1,%%eax \n\t"
	     "int $0x80 \n\t"
	     "hlt \n\t"::"m"(exitCode));
#endif
}
