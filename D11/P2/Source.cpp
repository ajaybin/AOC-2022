#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <deque>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;
int product = 1;
class monkey {
public:
	int mynumber;
	deque<unsigned long long int> items;

	int divisor;
	int true_monkey, false_monkey;
	int myinspect_count = 0;
	int arg1, arg2;
	string oper;

	bool test(unsigned long long int worry) {
		return (worry%divisor == 0);
	}

	unsigned long long int operate() {
		unsigned long long int temp1, temp2;
		if (arg1 == -1) {
			temp1 = items[0];
		}
		else {
			temp1 = arg1;
		}
		if (arg2 == -1) {
			temp2 = items[0];
		}
		else {
			temp2 = arg2;
		}
		if (oper == "*") {
			return (temp1 * temp2)%product;
		}
		else if (oper == "+") {
			return (temp1 + temp2)%product;
		}
	}
};


int main() {
	ifstream infile("Input.txt");
	ofstream fout("output");
	string line;
	deque<monkey> monkeys;
	int current_monkey = 0;
	while (getline(infile, line)) {
		smatch sm;
		if (regex_match(line, sm, regex("Monkey (\\d+):"))) {
			monkey monk;
			monk.mynumber = stoi(string(sm[1]));
			current_monkey = monk.mynumber;
			monkeys.push_back(monk);
		}
		else if (regex_match(line, sm, regex(".*Starting items: (.*)"))) {
			string itemstr = string(sm[1]);
			std::size_t prevpos = 0, pos;
			while ((pos = itemstr.find_first_of(",\n", prevpos)) != std::string::npos) {
				monkeys[current_monkey].items.push_back(stoi(itemstr.substr(prevpos, prevpos - pos)));
				prevpos = pos + 1;
			}
			monkeys[current_monkey].items.push_back(stoi(itemstr.substr(prevpos, std::string::npos)));
		}
		else if (regex_match(line, sm, regex(".*Operation.*= (old|\\d+) (.) (old|\\d+)"))) {
			if (sm[1] == "old") {
				monkeys[current_monkey].arg1 = -1;
			}
			else {
				monkeys[current_monkey].arg1 = stoi(string(sm[1]));
			}
			monkeys[current_monkey].oper = string(sm[2]);
			if (sm[3] == "old") {
				monkeys[current_monkey].arg2 = -1;
			}
			else {
				monkeys[current_monkey].arg2 = stoi(string(sm[3]));
			}
		}
		else if (regex_match(line, sm, regex(".*Test: divisible by (\\d+)"))) {
			monkeys[current_monkey].divisor = stoi(string(sm[1]));
			product *= stoi(string(sm[1]));
		}
		else if (regex_match(line, sm, regex(".*true.*(\\d+)"))) {
			monkeys[current_monkey].true_monkey = stoi(string(sm[1]));
		}
		else if (regex_match(line, sm, regex(".*false.*(\\d+)"))) {
			monkeys[current_monkey].false_monkey = stoi(string(sm[1]));
		}
	}

	for (int i = 0; i < 10000; i++) { // 20 rounds
		for (size_t _monkey = 0; _monkey < monkeys.size(); _monkey++) {
			//fout << "Monkey " << _monkey << ":" << endl;
			while (monkeys[_monkey].items.size()) {
				//fout << "  Monkey inspects an item with a worry level of " << monkeys[_monkey].items[0] << endl;
				unsigned long long int worry = monkeys[_monkey].operate();
				//fout << "    Worry level is increased to " << worry << endl;
				int monmon;
				monkeys[_monkey].items.pop_front();
				monkeys[_monkey].myinspect_count++;
				//worry /= 3;
				//fout << "    Monkey gets bored with item. Worry level is divided by 3 to " << worry << endl;
				monmon = ((monkeys[_monkey].test(worry) == true) ? monkeys[_monkey].true_monkey : monkeys[_monkey].false_monkey);
				//fout << "    Current worry level " << ((monkeys[_monkey].test(worry) == true) ? "is " : "is not ") << "divisible by " << monkeys[_monkey].divisor << endl;
				monkeys[monmon].items.push_back(worry);
				//fout << "    Item with worry level " << worry << " is thrown to monkey " << monmon << endl;
			}
		}
	}

	infile.close();
	return 0;
}
