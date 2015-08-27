#include <bits/stdc++.h>
#include "convert.h"
using namespace std;

const int Converter::callFrameInformation(string &line) const {
    if(line.find(".cfi_startproc") != string::npos)
	return CONVERTER_OK;
    if(line.find(".cfi_def_cfa_offset") != string::npos) {
	line = "	.cfi_def_cfa_offset 16";
	return CONVERTER_OK;
    }
    if(line.find(".cfi_offset") != string::npos) {
	line = "	.cfi_offset 6, -16";
	return CONVERTER_OK;
    }
    if(line.find(".cfi_def_cfa_register") != string::npos) {
	line = "	.cfi_def_cfa_register 6";
	return CONVERTER_OK;
    }
    if(line.find(".cfi_restore") != string::npos) {
	line = "";
	return CONVERTER_OK;
    }
    if(line.find(".cfi_def_cfa") != string::npos) {
	line = "	.cfi_def_cfa 7, 8";
	return CONVERTER_OK;
    }
    if(line.find(".cfi_endproc") != string::npos)
	return CONVERTER_OK;
}

const int Converter::registerOps(string &line) const {
    size_t start_pos;
    if(line.find("eax, 0") != string::npos) {
    	return CONVERTER_OK;
    }
    if(line.find("leave") != string::npos) {
    	if(!mainFunc)
    		line = "	pop	rbp";
    	return CONVERTER_OK;
    }
    if(line.find("push	12") != string::npos) {
    	line = "	mov	esi, 12";
    	return CONVERTER_OK;
    }
    if(line.find("push	eax") != string::npos) {
    	line = "	mov	rdi, rax";
    	return CONVERTER_OK;
    }
    if(line.find("esp, 8") != string::npos) {
    	line = "";
    	return CONVERTER_OK;
    }
    if(line.find("sub	esp, 16") != string::npos) {
    	if(!mainFunc) {
    		line = "	mov	QWORD PTR [rbp-24], rdi\n	mov	QWORD PTR [rbp-32], rsi";
    	}
    }
    if((start_pos = line.find("ebp")) != string::npos) {
	line.replace(start_pos, 3, "rbp");
    }
    if((start_pos = line.find("esp")) != string::npos) {
	line.replace(start_pos, 3, "rsp");
    }
    if((start_pos = line.find("eax")) != string::npos) {
	line.replace(start_pos, 3, "rax");
    }
    if((start_pos = line.find("edx")) != string::npos) {
	line.replace(start_pos, 3, "rdx");
    }
    if((start_pos = line.find("DWORD")) != string::npos) {
	line.replace(start_pos, 5, "QWORD");
    }
    if((start_pos = line.find("+8")) != string::npos) {
	line.replace(start_pos, 2, "-24");
    }
    if((start_pos = line.find("+12")) != string::npos) {
	line.replace(start_pos, 3, "-32");
    }
    if((start_pos = line.find("-8")) != string::npos) {
	line.replace(start_pos, 2, "-16");
    }
    if((start_pos = line.find("-4")) != string::npos) {
	line.replace(start_pos, 2, "-8");
    }
    return CONVERTER_OK;
}
