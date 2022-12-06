#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main() {
	ifstream infile("Input.txt");
	string line1, line2, line3;
	int total = 0;

	while (infile >> line1 >> line2 >> line3) {
		size_t found;
		char common;
		int value;
		string tempstr;

		//cout << line1 << " " << line2 << " " << line3 << endl;

		found = line1.find_first_of(line2);
		while (found != std::string::npos)
		{
			tempstr.push_back(line1[found]);
			found = line1.find_first_of(line2, found + 1);
		}
		found = line3.find_first_of(tempstr);
		common = line3[found];


		if (isupper(common)) {
			value = common - 'A' + 27;
		}
		else {
			value = common - 'a' + 1;
		}

		//cout << comp1 << " " << comp2 << " CommonChar:" << comp1[found] << " " << value << endl;
		total += value;

	}
	infile.close();
	cout << total;
	return 0;
}