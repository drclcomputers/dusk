#pragma once
#pragma warning(disable : 4996)

#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
#include "calculator.h"

using namespace std;

struct var {
	string name;
	string value;
	string type;
};

struct func {
	string name;
	string args[20];
};

class interpreter {
public:
	vector <var> variabile;
	int execute(char* cmd);
};