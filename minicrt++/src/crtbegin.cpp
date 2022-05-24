// crtbegin.cpp

#ifndef WIN32

typedef void (*ctor_func)(void);

/* g++4.8使用.init_array段代替.ctors段 */
ctor_func ctors_begin[1] __attribute__ ((section(".init_array"))) = {
	(ctor_func)(-1)
};

void run_hooks() {
	const ctor_func* list = ctors_begin;
	while ((int)*++list != -1) {
		(**list)();
	}
}

#endif
