#include <bits/stdc++.h>
#include "convertAssembly.h"

using namespace std;

int main(int argc, char *argv[]) {
    ifstream f_32;
    ofstream f_64;
    Converter c;
    f_32.open(argv[1]);
    f_64.open(argv[2]);
    string line;
    string bfunc = "LFB";
    string efunc = "LFE";
    bool funcBegin = false;
    bool funcEnd = true;
    if(f_32.is_open()) {
	while(getline(f_32, line)) {
	    if(line.find("main") != string::npos)
		c.mainFunc = true;
	    if(line.find(bfunc) != string::npos) {
		funcBegin = true;
		funcEnd = false;
	    }
	    else if(line.find(efunc) != string::npos) {
		funcEnd = true;
		funcBegin = false;
	    }

	    if(funcEnd) {
		f_64 << line << endl;
	    }
	    else {
		if(line.find(".cfi") != string::npos) {
		    if(c.callFrameInformation(line) != CONVERTER_OK) {
			cout << "Error in parsing CFI directives" << endl;
		    }
		}
		else {
		    if(c.registerOps(line) != CONVERTER_OK) {
			cout << "Error in parsing the register operations" << endl;
		    }
		}
		if(line != "")
			f_64 << line << endl;
	    }
	}
    }
    else {
	cout << "Unable to open file" << endl;
    }
    return 0;
}
