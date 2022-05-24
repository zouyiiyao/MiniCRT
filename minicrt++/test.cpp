#include "minicrt.h"
#include "iostream"
#include "cppstring"

int main(int argc, char* argv[]) {
	minicrt::string s("Hello, minicrt++");
	minicrt::cout << s << minicrt::endl;

	minicrt::ofstream ofs("./test.txt", minicrt::ofstream::out);
	ofs << "Hello, micrt++" << minicrt::endl;
	return 0;
}
