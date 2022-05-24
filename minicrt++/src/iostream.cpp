// iostream.cpp

#include "minicrt.h"
#include "iostream"
#ifdef WIN32
#include <Windows.h>
#endif

namespace minicrt {

	stdout_stream::stdout_stream(): ofstream() {
		printf("call stdout_stream::stdout_stream(): ofstream()\n");
		fp = stdout;
	}

	stdout_stream::~stdout_stream() {
		printf("call stdout_stream::~stdout_stream()\n");
	}

	stdout_stream cout;

	ofstream::ofstream(): fp(0) {
	}

	ofstream::ofstream(const char* filename, ofstream::openmode md): fp(0) {
		open(filename, md);
	}

	ofstream::~ofstream() {
		printf("call ~ofstream() %d\n", fp);
		close();
	}

	ofstream& ofstream::operator<<(char c) {
		fputc(c, fp);
		return *this;
	}

	ofstream& ofstream::operator<<(int n) {
		fprintf(fp, "%d", n);
		return *this;
	}

	ofstream& ofstream::operator<<(const char* str) {
		fprintf(fp, "%s", str);
		return *this;
	}

	ofstream& ofstream::operator<<(ofstream& (*manip)(ofstream&)) {
		return manip(*this);
	}

	void ofstream::open(const char* filename, ofstream::openmode md) {
		char mode[4];
		close();

		switch (md) {
			case out:
				strcpy(mode, "w");
				break;
			}
		fp = fopen(filename, mode);
	}

	void ofstream::close() {
		if (fp) {
			fclose(fp);
			fp = 0;
		}
	}

	ofstream& ofstream::write(const char* buf, unsigned size) {
		fwrite(buf, 1, size, fp);
		return *this;
	}
}
