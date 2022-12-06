#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream infile("Input.txt");
	string line;
	int value, total;
	int highest[3] = {};
	total = 0;
	while (getline(infile, line)) {
		try
		{
			value = stoi(line);
			total += value;
		}
		catch (std::invalid_argument const& ex)
		{
			if (total > highest[0]) {
				highest[2] = highest[1];
				highest[1] = highest[0];
				highest[0] = total;
			}
			else if (total > highest[1]) {
				highest[2] = highest[1];
				highest[1] = total;
			}
			else if (total > highest[2]) {
				highest[2] = total;
			}
			total = 0;
		}
	}
	infile.close();
	cout << highest[0] << endl;                          //PART1
	cout << highest[2] + highest[1] + highest[0] << endl;//PART2
	return 0;
}