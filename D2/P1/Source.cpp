#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream infile("Text.txt");
	string in1, in2;
	int total = 0;
	while (infile >> in1 >> in2) {
		if (in1 == "A") {     //ROCK
			if (in2 == "X") { //LOSE : SCI
				total += 3 + 0;
			}
			else if (in2 == "Y") { // DRAW : ROCK
				total += 1 + 3;
			}
			else {  // WIN : PAPER
				total += 2 + 6;
			}
		}
		else if (in1 == "B") { // PAPER
			if (in2 == "X") { //LOSE : ROCK
				total += 1 + 0;
			}
			else if (in2 == "Y") { // DRAW : PAPER
				total += 2 + 3;
			}
			else {  // WIN :SCI
				total += 3 + 6;
			}
		}
		else { //SCI
			if (in2 == "X") { //LOSE : PAPER
				total += 2 + 0;
			}
			else if (in2 == "Y") { // DRAW :SCI
				total += 3 + 3;
			}
			else {  // WIN : ROCK
				total += 1 + 6;
			}
		}
	}
	cout << total;
	return 0;
}
