#include "functii.h"

bool iscifra2(char x) {
	if (x >= 48 && x <= 57)
		return 1;
	return 0;
}

bool isnumar(char* x) {
	for (int i = 0; x[i]; i++) {
		if (!iscifra2(x[i]))
			return 0;
	}
	return 1;
}

bool issemn(char x) {
	if (strchr("!+-*/<>=&|%", x))
		return 1;
	return 0;
}

bool isstring(char* x) {
	for (int i = 0; x[i]; i++) {
		if (iscifra2(x[i]) || issemn(x[i]))
			return 0;
	}
	return 1;
}

bool check_oper(char* s) {
	for (int i = 0; i < strlen(s); i++) {
		if (strchr("!+-*/<>=&|%", s[i])) {
			return 1;
		}
	}
	return 0;
}



bool doar_cifre(char* s) {
	for (int i = 0; i < strlen(s); i++) {
		if (issemn(s[i]))
			continue;
		if (!iscifra2(s[i])) {
			return 0;
		}
	}
	return 1;
}