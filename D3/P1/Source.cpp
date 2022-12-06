#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

int main() {
	ifstream infile("Test.txt");
	string line;
	int total = 0;

	while (getline(infile, line)) {
		string comp1, comp2, string_intersection;
		size_t found;
		char common;
		int value;

		comp1 = line.substr(0, line.length()/2);
		comp2 = line.substr(line.length()/ 2);

		found  = comp1.find_first_of(comp2);
		common = comp1[found];


		if (isupper(common)) {
			value = common - 'A' + 27;
		}
		else {
			value = common - 'a' + 1;
		}

		cout << comp1 << " " << comp2 << " CommonChar:" << comp1[found] << " " << value << endl;
		total += value;


	}
	infile.close();
	cout << total;
	return 0;
}