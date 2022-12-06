#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
	ifstream infile("Input.txt");
	string line;

	while (getline(infile, line)) {
		for (size_t pos = 0; pos < line.length(); pos += 1) {
			string temp = line.substr(pos, 4);
			std::map<char, int> mymap;
			int flag = 1;

			for (size_t i = 0; i < temp.length(); i++) {
				mymap[temp[i]] = 0;
			}
			for (size_t i = 0; i < temp.length(); i++) {
				mymap[temp[i]] += 1;
				if (mymap[temp[i]] == 2) {
					flag = 0;
					break;
				}
			}
			if (flag == 1) {
				cout << pos + 4 << endl;  //Part1
				break;
			}

		}
		for (size_t pos = 0; pos < line.length(); pos += 1) {
			string temp = line.substr(pos, 14);
			std::map<char, int> mymap;
			int flag = 1;

			for (size_t i = 0; i < temp.length(); i++) {
				mymap[temp[i]] = 0;
			}
			for (size_t i = 0; i < temp.length(); i++) {
				mymap[temp[i]] += 1;
				if (mymap[temp[i]] == 2) {
					flag = 0;
					break;
				}
			}
			if (flag == 1) {
				cout << pos + 14 << endl; //Part2
				break;
			}

		}
	}
	infile.close();
	return 0;
}