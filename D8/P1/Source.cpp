#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main() {
	ifstream infile("Input.txt");
	string line;
	std::vector<std::vector<int>> matrix;

	int maxrow = 0, maxcol = 0;

	while (getline(infile, line)) {
		vector<int> v; 
		for (int i = 0; i < line.length(); i++) {
			v.push_back(line[i] - '0');
		}
		matrix.push_back(v);
		maxrow += 1;
	}
	maxcol = line.length();
	int visible = 0;


	for (int _elerow = 0; _elerow < maxrow; _elerow++) {
		if (_elerow == 0 || _elerow == maxrow - 1) {
			visible += maxcol;
			continue;
		}
		for (int _elecol = 0; _elecol < maxcol; _elecol++) {
			if (_elecol == 0 || _elecol == maxcol - 1) {
				visible += 1;
				continue;
			}
			// Left to right
			int left = 1;
			int visible_left = 1, visible_right = 1;
			for (int _itercol = 0; _itercol < maxcol; _itercol++) {
				if (_itercol == _elecol) {
					left = 0;
					continue;
				}
				if (matrix[_elerow][_itercol] >= matrix[_elerow][_elecol]) {
					if (left) {
						visible_left = 0;
					}
					else {
						visible_right = 0;
					}
				}
			}

			// Top to Bottom
			int top = 1;
			int visible_top = 1, visible_bottom = 1;
			for (int _iterrow = 0; _iterrow < maxrow; _iterrow++) {
				if (_iterrow == _elerow) {
					top = 0;
					continue;
				}
				if (matrix[_iterrow][_elecol] >= matrix[_elerow][_elecol]) {
					if (top) {
						visible_top = 0;
					}
					else {
						visible_bottom = 0;
					}
				}
			}

			if (visible_bottom || visible_top || visible_right || visible_left) {
				cout << "Row:" << _elerow << " Col:" << _elecol << " is visible" << endl;
				visible += 1;
			}
		}
	}
	cout << visible;
	infile.close();
	return 0;
}
