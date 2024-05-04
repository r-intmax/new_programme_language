#ifndef str_H_
#define str_H_ 0.1

#include <stdarg.h>

typedef struct{
	char* str;
	size_t len;
	int id;
} string;

int sid = 0;

char* strToChar(string str){
	return str.str;
}

char* numToChar(int val){
	size_t n = 0;
	while(val >> 4){
		n++;
	}
	char* str = malloc(n * sizeof(char));
	do{
		int i = val & 0xf;
		if(i < 10){
			*(str++) = char(i + 0x30);
		}else{
			*(str++) = char(i + 0x61 - 10);
		}
	}while(val >> 4);
	char* ret = malloc(n * sizeof(char));
	for(int i = 0; i <= n; i++){
		*(ret + i) = *(str + n - i);
	}
	string s = {ret, n, ++sid};
	free(str);
	return ret;
}

int StrToInt(string str){
	size_t l = str.len;
	int hex = 0;
	if(*str == '0' && *(str + 1) == 'x'){
		hex = 1;
	}
	int ret;
	while(l--){
		int c = (int)*(str + l - 1);
		if(c >= 0x30 && c <= 0x39){
			ret += c - 0x30;
		}else if(c >= 0x41 && c < 0x46){
			ret += c - 0x41 + 10;
		}else if(c >= 0x61 && c < 0x66){
			ret += c - 0x61 + 10;
		}else if(c == (int)'x' && l == 2){
			break;
		}else{
			program_error("invaild input");
		}
		ret *= (hex ? 10 : 16);
	}
	return ret;
}

char* addstrr(string s1, char* s2){
	int l = (int)s1.len;
	s1.len += strlen(s2);
	realloc((void*)s1.str, s1.len);
	char* c = &s2;
	for(int i = l; i < s1.len; i++){
		s1[i] = *(c++);
	}
}

void addstr(string s1, char* s2){
	s1 = addstrr(s1, s2);
}

void addstrs(char *asm, ...) {
	va_list args;
	va_start(args, asm);
	char *s;
	while ((s = va_arg(args, char *)) != NULL) {
		addstr(asm, s);
	}
	va_end(args);
}

void addstrsn(char *asm, ...) {
	va_list args;
	va_start(args, asm);
	char *s;
	while ((s = va_arg(args, char *)) != NULL) {
		addstrs(asm, s, "\n", NULL);
	}
	va_end(args);
}

size_t newLineNum(string str){
	char* c = &str.str;
	size_t l = str.len;
	size_t n = 0;
	while(--l){
		if(*(c++) == "\n"){
			n++;
		}
	}
	return n;
}

#endif
