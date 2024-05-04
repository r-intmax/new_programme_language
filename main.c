#include <stdio.h>
#include <stdlib.h>

#include "str.h"

//after processing user language

typedef struct{
	size_t c, l;
	char* strval;
	size_t strlen;
} Position;

void get(const char* testWord);

// void addVal(void* ptr, const char* cond, const char* st);

void pif(){
	size_t l = pos.l;
	size_t t = ctab;
	while(get("\n"));
	if(ctab != t + 1){
		error("invaild \\t after \"if\"");
	}
	char* cond = mainloop(l);
	char* strt = mktab(ctab);
	string asm, ifasm, elseasm;
	while(ctab > t && get("\n"));
	/* // cond statements
	 * jnz else_ln/label_ln
	 * // if statements
	 * jmp label_ln // optional
	 * else_ln // optional
	 * //else statememts
	 * label_ln
	 * // other statemets 
	 */
	if(!get("else")){
		addstr(ifasm, mainloop(l));
		addstrsn(asm, cond, "jnz +", numToChar(newLineNum(ifasm)), "\n", strToChar(ifasm));
	}else{
		addstr(ifasm, mainloop(l));
		l = pos.l;
		while(ctab > t && get("\n"));
		addstr(elseasm, mainloop(l));
		addstrsn(asm, cond, "jnz +", numToChar(newLineNum(ifasm) + newLineNum(elseasm)), "\n",strToChar(ifasm),
			strToChar(ifasm), "jmp +", numToChar(newLineNum(elseasm)), "\n", strToChar(elseasm));
	}
	return strToChar(asm);
}

void ploop();

void mainloop(size_t ul){
	size_t cl = pos.l;
	pos.l = ul;
	size_t t = ctab;
	string asm;
	while(pos.l < cl){
		get(mktab(t));
		if(get("if")){
			addstrsn(asm, pif());
		}else if(get("else")){
			error("else with no \"if\" match");
		}else if(get("loop")){
			addstrsn(asm, ploop());
		}else if(get("break")){
			error("\"break\" with no \"loop\" match");
		}else if(get("continue")){
			error("\"continue\" with no \"loop\" match");
		}else{
            // ...
        }
	}

}
