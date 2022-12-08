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
	int scenic = 0;

	for (int _elerow = 0; _elerow < maxrow; _elerow++) {
		if (_elerow == 0 || _elerow == maxrow - 1) {
			continue;
		}
		for (int _elecol = 0; _elecol < maxcol; _elecol++) {
			int sl = 0, sr = 0, sb = 0, st = 0;
			if (_elecol == 0 || _elecol == maxcol - 1) {
				continue;
			}
			// Left
			for (int _itercol = _elecol - 1; _itercol >= 0; _itercol--) {
				sl++;
				if (matrix[_elerow][_itercol] >= matrix[_elerow][_elecol]) {
					break;
				}
			}
			// Right
			for (int _itercol = _elecol + 1; _itercol < maxcol; _itercol++) {
				sr++;
				if (matrix[_elerow][_itercol] >= matrix[_elerow][_elecol]) {
					break;
				}
			}
			// Top
			for (int _iterow = _elerow - 1; _iterow >= 0; _iterow--) {
				st++;
				if (matrix[_iterow][_elecol] >= matrix[_elerow][_elecol]) {
					break;
				}
			}
			// Bottom
			for (int _iterow = _elerow + 1; _iterow < maxrow; _iterow++) {
				sb++;
				if (matrix[_iterow][_elecol] >= matrix[_elerow][_elecol]) {
					break;
				}
			}
			if ((sr*sl*sb*st) > scenic) {
				scenic = (sr*sl*sb*st);
			}
		}
	}
	cout << scenic;
	infile.close();
	return 0;
}
