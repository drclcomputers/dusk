#include "main.h"

ifstream fin;

int linia=0;
int insideloop = 0, insideif = 0, nrloops=0, maxloop=0;

int loops[5000], stoploops[5000];

void clean(char* s) {
	for (int i = 0; i < 1000; i++)
		s[i] = '\0';
}

int run_if(char* command) {
	int res = interpreter.execute(command);
	command[2] = ' ';
	return res;
}


int run_while(char* command, char* p) {
	int nrloop = insideloop, nrif = insideif;
	while (fin.getline(command, 1000)) {
		//cout << "COM: " << command << '\n';
		if (command[0] == '/') continue;
		if (command[0] == '\0') continue;
		if (strstr(command, "exit")) return 0;
		if (strstr(command, "stopif")) {
			insideif--;
			return 3;
		}
		if (strstr(command, "stoploop")) {
			return 5;
		}
		int res = interpreter.execute(command);
		if (res == 2) {
			insideif++;
			//cout << insideif;
			run_while(command, p);
			insideif--;
			return 2;
		}
		else if (res == 3) {
			while (fin.getline(command, 1000)) {
				if (strstr(command, "exit")) break;
				if (strstr(command, "stopif")) break;
			}
			return 3;
		}
		else if (res == 4) {
			insideloop++;
			maxloop = max(maxloop, insideloop);
			int loop;
			loop = nrloops + insideloop;
			
			command[5] = ' ';
			char* po = strtok(command, " \"'");
			po = strtok(NULL, " \"'");
			char paux[300] = "if ";
			strcat(paux, po);
			while (run_if(paux) == 2) {
				for (int i = loops[loop] + 1; i < stoploops[loop]; i++) {
					if (run_while(command, p) == 5) break;
					clean(command);
				}
				fin.close();
				fin.open(p);
				for (int j = 1; j <= loops[loop]; j++)
					fin.getline(command, 1000);
				clean(command);
			}
			for (int i = loops[loop] + 1; i <= stoploops[loop]; i++)
				fin.getline(command, 1000);
			insideloop--;
		}
		else if (res == 5) {
			for (int i = loops[insideloop] + 1; i <= stoploops[insideloop]; i++)
				fin.getline(command, 1000);
			return 5;
		}
	}
	return 0;
}

void run(char *command, char *p) {
	while (fin.getline(command, 1000)) {
		//cout << "COM: " << command << '\n';
		if (command[0] == '/') continue;
		if (command[0] == '\0') continue;
		if (strstr(command, "exit")) break;
		int res = interpreter.execute(command);
		if (res == 2) {
			insideif++;
			run(command, p);
			insideif--;
		}
		else if (res == 3) {
			while (insideif > 0 && fin.getline(command, 1000)) {
				if (strstr(command, "exit")) break;
				if (strstr(command, "stopif")) break;
			}
		}
		else if (res == 4) {
			insideloop++;
			maxloop = max(maxloop, insideloop);
			int loop;
			loop = nrloops + insideloop;

			command[5] = ' ';
			char* po = strtok(command, " \"'");
			po = strtok(NULL, " \"'");
			char paux[300] = "if ";
			strcat(paux, po);
			while (run_if(paux) == 2) {
				for (int i = loops[loop] + 1; i < stoploops[loop]; i++) {
					if (run_while(command, p) == 5) break;
					clean(command);
				}
				fin.close();
				fin.open(p);
				for (int j = 1; j <= loops[loop]; j++)
					fin.getline(command, 1000);
				clean(command);
			}
			for (int i = loops[loop]+1; i <= stoploops[loop]; i++)
				fin.getline(command, 1000);
			insideloop--;
			nrloops += maxloop;
			maxloop = 0;
		}
		else if (res == 5) {
			for (int i = loops[insideloop] + 1; i <= stoploops[insideloop]; i++)
				fin.getline(command, 1000);
		}
		run(command, p);
		clean(command);
	}
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		char command[1001];
		while (true) {
			cout << "dusk > ";
			cin.getline(command, 1000);
			if (command[0] == '/') continue;
			if (command[0] == '\0') continue;
			if (strstr("exit", command)) break;
			interpreter.execute(command);
			cout << "\n";
			clean(command);
		}
	}
	else {
		char command[1001];
		
		queue <int> loopsstack;
		
		fin.open(argv[1]);
		int aux = 1, auxaux=1, i=1, stopsaux=1, stops[5000];
		
		while (fin.getline(command, 1000)) {
			if (command[0] == '/') { i++; continue; }
			if (command[0] == '\0'){ i++; continue; }
			char* p = strtok(command, " \"'");
			if (strcmp(p, "while") == 0) {
				loopsstack.push(i); 
			}
			if (strcmp(p, "stoploop") == 0) {
				stops[stopsaux++] = i;
				//cout << "stoploop:" << i << '\n';
				loops[aux++] = loopsstack.front();
				loopsstack.pop();
				if (loopsstack.empty()) {
					for (int k = stopsaux - 1; k > 0 && stops[k]!=0; k--)
						stoploops[auxaux++] = stops[k], stops[k]=0;
				}
			}
			i++;
		}

		/*
		for (int i = 0; i < 10; i++)
			cout << loops[i] << " ";
		cout << '\n';
		for (int i = 0; i < 10; i++)
			cout << stoploops[i] << " ";
		cout << '\n';
		*/

		fin.close();
		fin.open(argv[1]);
		run(command, argv[1]);
	}
	return 0;
}