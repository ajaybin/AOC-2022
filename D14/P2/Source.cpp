#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>


using namespace std;
typedef pair<int, int> pos_t;

map<pos_t, bool> scan;
int deepest = 0; // no idea what this is

pair<int, int> get_pair(string pos) {
	pair<int, int> mypair;
	mypair.first = stoi(pos.substr(0, 3)); //HEAVY MAGIC NUMBER
	mypair.second = stoi(pos.substr(4));
	if (mypair.second > deepest) {
		deepest = mypair.second;
	}
	return mypair;
}

void draw(pos_t pos1, pos_t pos2) {
	if (pos1.first == pos2.first) {
		pos_t start = { pos1.first, std::min(pos1.second, pos2.second) };
		pos_t end = { pos1.first, std::max(pos1.second, pos2.second) };
		for (pos_t iter = start; iter.second <= end.second; iter.second++) {
			scan[iter] = true;
		}
	}
	else if (pos1.second == pos2.second) {
		pos_t start = { std::min(pos1.first, pos2.first), pos1.second };
		pos_t end = { std::max(pos1.first, pos2.first), pos1.second };
		for (pos_t iter = start; iter.first <= end.first; iter.first++) {
			scan[iter] = true;
		}
	}
}

bool is_blocked(pos_t pos) {
	if (scan[pos] == true || pos.second == deepest) {
		return true;
	}
	return false;
}

int is_at_rest(pos_t sand_pos) {
	int at_rest = -1;

	if (is_blocked({sand_pos.first, sand_pos.second + 1})
		&& is_blocked({sand_pos.first - 1, sand_pos.second + 1})
		&& is_blocked({sand_pos.first + 1, sand_pos.second + 1})) {
		return 1;
	}
	else {
		return 0;
	}
}

int move_sand(pos_t *sand_pos) {
	int at_rest;

	if (scan[{sand_pos->first, sand_pos->second + 1}] == false) {
		sand_pos->second = sand_pos->second + 1;
	}
	else if (scan[{sand_pos->first - 1, sand_pos->second + 1}] == false) {
		sand_pos->first = sand_pos->first - 1;
		sand_pos->second = sand_pos->second + 1;
	}
	else if (scan[{sand_pos->first + 1, sand_pos->second + 1}] == false) {
		sand_pos->first = sand_pos->first + 1;
		sand_pos->second = sand_pos->second + 1;
	}
	at_rest = is_at_rest(*sand_pos);
	if (at_rest == 1) {
		scan[*sand_pos] = true;
	}
	return at_rest;
}

int main() {
	ifstream infile("Input.txt");
	string line;
	string pos_str;

	vector<vector<pos_t>> rocks;

	while (getline(infile, line)) {
		size_t pos;
		size_t prevpos = 0;
		vector<pos_t> path;

		while ((pos = line.find_first_of("-", prevpos)) != std::string::npos) {
			pos_str = line.substr(prevpos, pos - prevpos - 1);
			prevpos = pos + 3;
			path.push_back(get_pair(pos_str));
		}
		pos_str = line.substr(prevpos, std::string::npos);
		path.push_back(get_pair(pos_str));
		rocks.push_back(path);
	}
	deepest = deepest + 2;
	size_t size = rocks.size();
	for (size_t i = 0; i < size; i++) {
		vector<pos_t> path = rocks[i];
		size_t path_size = path.size();
		for (size_t i = 0; i < path_size - 1; i++) {
			draw(path[i], path[i + 1]);
		}
	}

	int at_rest;
	int sand = 0;
	while (1) {
		pos_t sand_pos = { 500, 0 };
		//cout << endl << "sand starting at (" << sand_pos.first << "," << sand_pos.second << ")" << endl;
		sand++;
		at_rest = is_at_rest(sand_pos);
		if (at_rest == 1) {
			//cout << "Max Sand Reached" << endl;
			break;
		}
		while (1) {
			at_rest = move_sand(&sand_pos);
			//cout << "sand moved to (" << sand_pos.first << "," << sand_pos.second << ")" << endl;
			if (at_rest == 1) {
				//cout << "sand at rest" << endl;
				break;
			}
		}
	}
	cout << sand << endl;

	infile.close();
	return 0;
}
