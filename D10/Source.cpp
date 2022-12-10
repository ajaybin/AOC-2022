#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

int cycle = 1, next_cycle = 2, total = 0, weigth = 20, X = 1;
string s;

void shift() {
	if (cycle == weigth) {
		total += weigth * X;
		weigth += 40;
	}
	s.push_back(((cycle - 1) % 40 >= X - 1 && (cycle - 1) % 40 <= X + 1) ? '#' : '.');
	cycle = next_cycle;
	next_cycle++;
}

int main() {
	ifstream infile("Input.txt");
	string line;

	while (getline(infile, line)) {
		smatch sm;
		if (regex_match(line, regex("noop"))) {
			shift();
		}
		else if (regex_match(line, sm, regex("addx (-?\\d+)"))) {
			//cout << stoi(string(sm[1])) << endl;
			for (int i = 0; i < 2; i++) {
				shift();
			}
			X += stoi(string(sm[1]));
		}
	}
	for (size_t i = 0; i < s.size(); i += 40)
		cout << s.substr(i, 40) << endl;
	cout << total;
	infile.close();
	return 0;
}
