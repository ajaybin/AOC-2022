#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	ifstream instrunctions("Input.txt");
	ifstream config("StartingConfig.txt");
	string line;
	std::vector<std::deque<string>> matrix(100);
	std::vector<int> index;
	string dud, amount, fromstack, tostack;

	while (getline(config, line)) {
		std::size_t prevpos = 0, pos;
		while ((pos = line.find_first_of("[", prevpos)) != std::string::npos)
		{
			matrix[pos + 1].push_back(line.substr(pos + 1, 1));
			index.push_back(pos + 1);
			prevpos = pos + 1;
		}
	}
	std::sort(index.begin(), index.end());
	index.erase(unique(index.begin(), index.end()), index.end());
	config.close();

	while (instrunctions >> dud >> amount >> dud >> fromstack >> dud >> tostack) {
		int fs, ts, amt;
		std::deque<string> temp;
		fs = stoi(fromstack) - 1;
		ts = stoi(tostack) - 1;
		amt = stoi(amount);
		for (int i = 0; i < amt; i++) {
			temp.push_front(matrix[index[fs]][0]);
			matrix[index[fs]].pop_front();
		}
		for (int i = 0; i < amt; i++) {
			matrix[index[ts]].push_front(temp[0]);
			temp.pop_front();
		}
	}
	instrunctions.close();
	for (int i = 0; i < index.size(); i++) {
		cout << matrix[index[i]][0];
	}
	return 0;
}