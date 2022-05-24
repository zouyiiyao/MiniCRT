// crtend.cpp

#ifndef WIN32

typedef void (*ctor_func)(void);

ctor_func ctors_end[1] __attribute__ ((section(".init_array"))) = {
	(ctor_func)(-1)
};

#endif
