#include "interpreter.h"
#include "functii.h"

int interpreter::execute(char* cmd) {
	char* p = strtok(cmd, " =\"");
	if (p != NULL) {
		if (strstr(p, "print")!=NULL) {
			p = strtok(NULL, " \"'");
			//check for math operations
			if (check_oper(p) && doar_cifre(p)) {
				cout << evaluare_exp(p);
				return 1;
			}
			else if(check_oper(p)) {
				string a, exp;
				for (int i = 0; p[i]; i++) {
					
					if (issemn(p[i])) {
						char aux[100];
						strcpy(aux, a.c_str());
						if (isnumar(aux)) {
							exp += a;
							exp += p[i];
							a.clear();
							continue;
						}
						else if (!a.empty()) {
							char s[100];
							strcpy(s, a.c_str());
							//cout << s << "    ";
							auto it = find_if(variabile.begin(), variabile.end(), [&s](const var& item) {
								return item.name == s;
								});
							if (it != variabile.end()) {
								exp += it->value;
							}
							else {
								cout << "Error: Unitialised variable with name '" << s << "'!";
								return 1;
							}
							a.clear();
						}
						exp += p[i];
					}
					else
						a += p[i];
				}
				char aux[100];
				strcpy(aux, a.c_str());
				if (isnumar(aux)) {
					exp += a;
				}
				else if(a.empty()==0){
					auto it = find_if(variabile.begin(), variabile.end(), [&aux](const var& item) {
						return item.name == aux;
						});
					if (it != variabile.end()) {
						exp += it->value;
					}
					else {
						cout << "Error: Unitialised variable with name '" << aux << "'!";
						return 1;
					}
				}
				//cout << "Expresie: " << exp;
				char exp2[3000];
				strcpy(exp2, exp.c_str());
				cout<<evaluare_exp(exp2);
				return 1;
			}


			//cauta variabile
			auto it = find_if(variabile.begin(), variabile.end(), [&p](const var& item) {
				return item.name == p;
				});
			if (it != variabile.end()) {
				//p[strlen(p)+1] = ' ';
				cout << it->value;
			}
			else {
				if (strstr(p, "@spc")) {
					cout << ' ';
					return 1;
				}
				if (p[strlen(p)] == '\0' && p[strlen(p) + 1] >= 32 && p[strlen(p)+1]<127) p[strlen(p)] = ' ';
				cout << p;
			}
			return 1;
		}

		else if (strstr(p, "var") != NULL) {
			p = strtok(NULL, " =\"");
			if (p == NULL) {
				cout << "Error: No name for variable!";
				return 0;
			}

			for (int i = 0; p[i]!=0 ; i++) {
				if (iscifra(p[i])) {
					cout << "Error: Variable name cannot contain numbers!";
					return 0;
				}
			}

			auto it = find_if(variabile.begin(), variabile.end(), [&p](const var& item) {
				return item.name == p;
				});
			if (it != variabile.end()) {
				cout << "Error! Variable with name " << p << " already exists!";
				return 0;
			}

			var new_var;
			new_var.name = p;
			p = strtok(NULL, " =\"");
			if (p == NULL) {
				cout <<p<< "Error: No value for variable!";
				return 0;
			}

			if (isnumar(p)) {
				new_var.type = "int";
				new_var.value = p;
				variabile.push_back(new_var);
				return 1;
			}

			

			if (check_oper(p) && doar_cifre(p)) {
				new_var.type = "int";
				int a = evaluare_exp(p);
				new_var.value = to_string(a);
			}
			else if(check_oper(p)){
				string a, exp;
				bool semn = 0;
				for (int i = 0; p[i]; i++) {
					if (issemn(p[i])) {
						semn = 1;
						char aux[100];
						strcpy(aux, a.c_str());
						if (isnumar(aux)) {
							exp += a;
							exp += p[i];
							a.clear();
							continue;
						}
						else if (!a.empty()) {
							char s[100];
							strcpy(s, a.c_str());
							//cout << s << "    ";
							auto it = find_if(variabile.begin(), variabile.end(), [&s](const var& item) {
								return item.name == s;
								});
							if (it != variabile.end()) {
								exp += it->value;
							}
							else {
								cout << "Error: Unitialised variable with name '" << s << "'!";
								return 1;
							}
							a.clear();
						}
						exp += p[i];
					}
					else 
						a += p[i];
				}
				char aux[100];
				strcpy(aux, a.c_str());
				if (isnumar(aux)) {
					exp += a;
				}
				else if (!a.empty()) {
					//cout << s;
					auto it = find_if(variabile.begin(), variabile.end(), [&aux](const var& item) {
						return item.name == aux;
						});
					if (it != variabile.end()) {
						exp += it->value;
					}
					else {
						cout << "Error: Unitialised variable with name '" << aux << "'!";
						return 1;
					}
				}
				if (!semn) {
					new_var.value = exp;
					variabile.push_back(new_var);
					return 1;
				}

				char exp2[3000];
				strcpy(exp2, exp.c_str());
				new_var.value = to_string(evaluare_exp(exp2));
				variabile.push_back(new_var);
				return 1;
			}

			new_var.type = "string";
			new_var.value = p;
			variabile.push_back(new_var);
			return 1;

		}
	
		else if (strstr(p, "put") != NULL) {
			cin.clear();
			p = strtok(NULL, " =\"");
			if (p == NULL) {
				cout << "Error: No variable for input!";
				return 0;
			}
			string name = p, mesaj, value;
			p = strtok(NULL, " \"'");
			if (p != NULL) {
				p[strlen(p)] = ' ';
				mesaj = p;
				cout << mesaj;
			}
			//cin.ignore();
			getline(cin, value);
			auto it = find_if(variabile.begin(), variabile.end(), [&name](const var& item) {
				return item.name == name;
				});
			if (it != variabile.end()) {
				it->value = value;
			}
			else {
				cout << "Uninitialised variable!";
				return 0;
			}
		}

		else if (strstr(p, "if") != NULL) {
			p = strtok(NULL, " \"'");
			if (p == NULL) {
				cout << "Error: No arguments to evaluate for if!";
				return 3;
			}
			bool result=0;

				if (check_oper(p) && doar_cifre(p)) {
					//new_var.type = "int";
					//cout << p;
					int a = evaluare_exp(p);
					if (a) result = 1;
					else result = 0;
				}
				else if (check_oper(p)) {
					string a, exp;
					bool semn = 0;
					for (int i = 0; p[i]; i++) {
						if (issemn(p[i])) {
							semn = 1;
							char aux[100];
							strcpy(aux, a.c_str());
							if (isnumar(aux)) {
								exp += a;
								exp += p[i];
								a.clear();
								continue;
							}
							else if (!a.empty()) {
								char s[100];
								strcpy(s, a.c_str());
								//cout << s << "    ";
								auto it = find_if(variabile.begin(), variabile.end(), [&s](const var& item) {
									return item.name == s;
									});
								if (it != variabile.end()) {
									exp += it->value;
								}
								else {
									cout << "Error: Unitialised variable with name '" << s << "'!";
									return 3;
								}
								a.clear();
							}
							exp += p[i];
						}
						else
							a += p[i];
					}
					char aux[100];
					strcpy(aux, a.c_str());
					if (isnumar(aux)) {
						exp += a;
					}
					else if (!a.empty()) {
						//cout << s;
						auto it = find_if(variabile.begin(), variabile.end(), [&aux](const var& item) {
							return item.name == aux;
							});
						if (it != variabile.end()) {
							exp += it->value;
						}
						else {
							cout << "Error: Unitialised variable with name '" << aux << "'!";
							return 3;
						}
					}
					if (!semn) {
						if (strcmp("exp", "0") == 0)
							result = 0;
						else result = 1;
						//new_var.value = exp;
						//variabile.push_back(new_var);
						//return 1;
					}
					//cout << exp;
					char exp2[3000];
					strcpy(exp2, exp.c_str());
					int b = evaluare_exp(exp2);
					if (b) result = 1;
					else result = 0;
					//variabile.push_back(new_var);
					//return 1;
				}
				if (result)
					return 2;
				else
					return 3;	
		}

		else if (strstr(p, "while") != NULL) {
			p = strtok(NULL, " \"'");
			if (p == NULL) {
				cout << "Error: No arguments to evaluate for while!";
				return 5;
			}
			//cout << "Evaluare: " << p << '\n';
			bool result = 0;

			if (check_oper(p) && doar_cifre(p)) {
				//new_var.type = "int";
				//cout << p;
				int a = evaluare_exp(p);
				if (a) result = 1;
				else result = 0;
			}
			else if (check_oper(p)) {
				string a, exp;
				bool semn = 0;
				for (int i = 0; p[i]; i++) {
					if (issemn(p[i])) {
						semn = 1;
						char aux[100];
						strcpy(aux, a.c_str());
						if (isnumar(aux)) {
							exp += a;
							exp += p[i];
							a.clear();
							continue;
						}
						else if (!a.empty()) {
							char s[100];
							strcpy(s, a.c_str());
							//cout << s << "    ";
							auto it = find_if(variabile.begin(), variabile.end(), [&s](const var& item) {
								return item.name == s;
								});
							if (it != variabile.end()) {
								exp += it->value;
							}
							else {
								cout << "Error: Unitialised variable with name '" << s << "'!";
								return 5;
							}
							a.clear();
						}
						exp += p[i];
					}
					else
						a += p[i];
				}
				char aux[100];
				strcpy(aux, a.c_str());
				if (isnumar(aux)) {
					exp += a;
				}
				else if (!a.empty()) {
					//cout << s;
					auto it = find_if(variabile.begin(), variabile.end(), [&aux](const var& item) {
						return item.name == aux;
						});
					if (it != variabile.end()) {
						exp += it->value;
					}
					else {
						cout << "Error: Unitialised variable with name '" << aux << "'!";
						return 5;
					}
				}
				if (!semn) {
					if (strcmp("exp", "0") == 0)
						result = 0;
					else result = 1;
					//new_var.value = exp;
					//variabile.push_back(new_var);
					//return 1;
				}
				//cout << exp;
				char exp2[3000];
				strcpy(exp2, exp.c_str());
				int b = evaluare_exp(exp2);
				if (b) result = 1;
				else result = 0;
				//variabile.push_back(new_var);
				//return 1;
			}
			if (result)
				return 4;
			else
				return 5;
		}

		else if (strstr(p, "newline") != NULL) {
			cout << '\n';
		}

		else if (strstr(p, "stoploop") != NULL) {
			return 5;
		}


		else {
			auto it = find_if(variabile.begin(), variabile.end(), [&p](const var& item) {
				return item.name == p;
				});
			if (it != variabile.end()) {
				p = strtok(NULL, " \"'");
				if (p != NULL) {
					if (isnumar(p)) {
						it->type = "int";
						it->value = p;
						//variabile.push_back(new_var);
						return 1;
					}
					p[-1] = '=';
					if (check_oper(p-1) && doar_cifre(p)) {
						it->type = "int";
						int a = evaluare_exp(p);
						it->value = to_string(a);
					}
					else if (check_oper(p-1)) {
						
						string a, exp;
						bool semn = 0;
						for (int i = 0; p[i]; i++) {
							if (issemn(p[i])) {
								semn = 1;
								char aux[100];
								strcpy(aux, a.c_str());
								if (isnumar(aux)) {
									exp += a;
									exp += p[i];
									a.clear();
									continue;
								}
								else if (!a.empty()) {
									char s[100];
									strcpy(s, a.c_str());
									//cout << s << "    ";
									auto it = find_if(variabile.begin(), variabile.end(), [&s](const var& item) {
										return item.name == s;
										});
									if (it != variabile.end()) {
										exp += it->value;
									}
									else {
										cout << "Error: Unitialised variable with name '" << s << "'!";
										return 1;
									}
									a.clear();
								}
								exp += p[i];
							}
							else
								a += p[i];
						}
						char aux[100];
						strcpy(aux, a.c_str());
						if (isnumar(aux)) {
							exp += a;
						}
						else if (!a.empty()) {
							//cout << s;
							auto it = find_if(variabile.begin(), variabile.end(), [&aux](const var& item) {
								return item.name == aux;
								});
							if (it != variabile.end()) {
								exp += it->value;
							}
							else {
								cout << "Error: Unitialised variable with name '" << aux << "'!";
								return 1;
							}
						}
						char exp2[3000];
						strcpy(exp2, exp.c_str());
						it->value = to_string(evaluare_exp(exp2));
						//variabile.push_back(new_var);
						return 1;
					}
					else {
						it->type = "string";
						it->value = p;
					}
					//variabile.push_back(new_var);
					return 1;
				}
			}
			else {
				cout << "Error: Uninitialized variable with name '" << p << "'!";
				return 0;
			}
		}
	}
}