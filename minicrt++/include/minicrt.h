#ifndef __MINICRT_H
#define __MINICRT_H

#ifdef __cplusplus
/* 指示以下代码用C语言方式编译，不用名称修饰 */
extern "C" {
#endif

/* malloc */
#ifndef NULL
#define NULL (0)
#endif

void free(void* ptr);
void* malloc(unsigned size);
static int brk(void* end_data_segment);
int mini_crt_init_heap();

/* 字符串 */
char* itoa(int n, char* str, int radix);
int strcmp(const char* src, const char* dst);
char* strcpy(char* dest, const char* src);
unsigned strlen(const char* str);

/* 文件与IO */
typedef int FILE;

#define EOF (-1)

#ifdef WIN32
#define stdin ((FILE*)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout ((FILE*)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr ((FILE*)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)
#endif

int mini_crt_init_io();
FILE* fopen(const char* filename, const char* mode);
int fread(void* buffer, int size, int count, FILE* stream);
int fwrite(const void* buffer, int size, int count, FILE* stream);
int fclose(FILE* fp);
int fseek(FILE* fp, int offset, int set);

/* printf */
int fputc(int c, FILE* stream);
int fputs(const char* str, FILE* stream);
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);

/* internal */
void do_global_ctors();
void mini_crt_call_exit_routine();

/* atexit */
typedef void (*atexit_func_t)(void);
typedef void (*cxa_func_t)(void*);
int __cxa_atexit(cxa_func_t func, void* arg, void* unused);
int atexit(atexit_func_t);

#ifdef __cplusplus
}
#endif

#endif
