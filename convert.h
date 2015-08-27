#ifndef __CONVERTASSEMBLY_H__
#define __CONVERTASSEMBLY_H__

#include <bits/stdc++.h>
using namespace std;

#define CONVERTER_OK 0x0000
#define CONVERTER_ERROR 0x0001

class Converter {
    public:
	bool isx86;
	bool isx86_64;
	bool mainFunc;
	Converter(bool _32, bool _64) : isx86(_32), isx86_64(_64) {
		mainFunc = false;
	}
	Converter() : isx86(true), isx86_64(false) {
		mainFunc = false;
	}

	const int callFrameInformation(string &line) const;
	const int registerOps(string &line) const;
};

#endif
