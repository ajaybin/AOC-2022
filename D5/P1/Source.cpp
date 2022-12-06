#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
	ifstream instrunctions("Input.txt");
	ifstream config("StartingConfig.txt");
	string line;
	std::vector<std::deque<string>> matrix (100);
	std::vector<int> index;

	while (getline(config, line)) {
		std::size_t prevpos = 0, pos;
		while ((pos = line.find_first_of("[", prevpos)) != std::string::npos)
		{
			//cout << line.substr(pos+1, 1) << endl;
			matrix[pos+1].push_back(line.substr(pos + 1, 1));
			index.push_back(pos+1);
			prevpos = pos + 1;
		}
	}
	std::sort(index.begin(), index.end());
	index.erase(unique(index.begin(), index.end()), index.end());
	config.close();

	while (getline(instrunctions, line)) {
		istringstream iss(line);
		string dud, amount, fromstack, tostack;
		int fs, ts, amt;
		iss >> dud >> amount >> dud >> fromstack >> dud >> tostack;
		fs = stoi(fromstack)-1;
		ts = stoi(tostack)-1;
		amt = stoi(amount);
		for (int i = 0; i < amt; i++) {
			matrix[index[ts]].push_front(matrix[index[fs]][0]);
			matrix[index[fs]].pop_front();
		}
	}
	instrunctions.close();
	for (int i = 0; i < index.size(); i++) {
		cout << matrix[index[i]][0];
	}
	return 0;
}