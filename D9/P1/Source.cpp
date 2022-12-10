#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <regex>
#include <cstdlib>

using namespace std;
pair<int, int> key(0, 0);
map<pair<int, int>, bool> mymap;
class position {
public:
	int x, y;

	position() {
		x = 0;
		y = 0;
	}
};

bool is_touching(position head, position tail) {
	bool touching = false;

	if (head.x == tail.x && head.y == tail.y) {
		//overlap
		touching = true;
	}
	else if (  (std::abs(head.x - tail.x) == 1 && head.y == tail.y) 
		    || (head.x == tail.x && std::abs(head.y - tail.y) == 1)) {
		//lateral adjacent
		touching = true;
	}
	else if (std::abs(head.x - tail.x) == 1 && std::abs(head.y - tail.y) == 1) {
		//diagonal
		touching = true;
	}

	return touching;
}

void movetail(position& head, position& tail) {
	if (is_touching(head, tail)) {
		return;
	}

	if ((head.x - tail.x == 2) && head.y == tail.y) {
		tail.x += 1;
	}
	else if ((head.x - tail.x == -2) && head.y == tail.y) {
		tail.x -= 1;
	}
	else if ((head.y - tail.y == 2) && head.x == tail.x) {
		tail.y += 1;
	}
	else if ((head.y - tail.y == -2) && head.x == tail.x) {
		tail.y -= 1;
	}
	else if ((head.x - tail.x == 2 && head.y > tail.y) || (head.y - tail.y == 2 && head.x > tail.x)) {
		tail.x += 1;
		tail.y += 1;
	}
	else if ((head.x - tail.x == -2 && head.y > tail.y) || (head.y - tail.y == 2 && head.x < tail.x)) {
		tail.x -= 1;
		tail.y += 1;
	}
	else if ((head.x - tail.x == 2 && head.y < tail.y) || (head.y - tail.y == -2 && head.x > tail.x)) {
		tail.x += 1;
		tail.y -= 1;
	}
	else if ((head.x - tail.x == -2 && head.y < tail.y) || (head.y - tail.y == -2 && head.x < tail.x)) {
		tail.x -= 1;
		tail.y -= 1;
	}

}

void do_move(position& head, position& tail) {
	movetail(head, tail);
	key = std::make_pair(tail.x, tail.y);
	mymap[key] = true;
}

int main() {
	ifstream infile("Input.txt");
	string line;

	position head, tail;
	mymap[key] = true;
	while (getline(infile, line)) {
		smatch sm;
		regex_match(line, sm, regex("([A-Z]) (\\d+)"));
		int movement = stoi(string(sm[2]));
		if (sm[1] == "U") {
			for (int i = 0; i < movement; i++) {
				head.y += 1;
				do_move(head, tail);
			}
		}
		else if (sm[1] == "D") {
			for (int i = 0; i < movement; i++) {
				head.y -= 1;
				do_move(head, tail);
			}
		}
		else if (sm[1] == "L") {
			for (int i = 0; i < movement; i++) {
				head.x -= 1;
				do_move(head, tail);
			}
		}
		else if (sm[1] == "R") {
			for (int i = 0; i < movement; i++) {
				head.x += 1;
				do_move(head, tail);
			}
		}
	}
	cout << mymap.size();
	infile.close();
	return 0;
}
