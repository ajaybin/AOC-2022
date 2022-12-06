#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream infile("Input.txt");
	string line;
	int limit[4];
	int total1 = 0, total2 = 0;
	while (getline(infile, line)) {
		std::size_t prevpos = 0, pos;
		int i = 0;
		while ((pos = line.find_first_of("-,", prevpos)) != std::string::npos)
		{
			limit[i++] = stoi(line.substr(prevpos, pos - prevpos));
			prevpos = pos + 1;
		}
		limit[i] = stoi(line.substr(prevpos, std::string::npos));

		// PUZZLE1
		if ((limit[0] <= limit[2] && limit[1] >= limit[3]) || (limit[2] <= limit[0] && limit[3] >= limit[1]))
			total1 += 1;

		//PUZZLE2
		if ((limit[2] >= limit[0] && limit[2] <= limit[1]) || (limit[0] >= limit[2] && limit[0] <= limit[3]))
			total2 += 1;
	}
	cout << total1 << endl << total2;
	infile.close();
	return 0;
}