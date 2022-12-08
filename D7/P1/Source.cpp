#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

class dir {
public:
	string myname;
	string myparentdir;
	unsigned int mysize;
	dir(string name, string parentname = "NULL") {
		myname = name;
		mysize = 0;
		myparentdir = parentname;
	}
	dir() {

	}
};

int main() {
	ifstream infile("Input.txt");
	string line;

	std::map<std::string, dir> dirmap;

	string currentdir = "/";

	dirmap["/"] = dir("/");

	while (getline(infile, line)) {
		// cd "dir" ".." "/"
		// ls
		// <size> filename
		// dir <dirname>
		std::smatch sm;
		if (std::regex_match(line, sm, std::regex("\\$ cd (.*)"))) {
			string s = sm[1];
			if (s == "/") {
				currentdir = "/";
			}
			else  if (s != "..") {
				currentdir = currentdir + s;
			}
			else {
				currentdir = dirmap[currentdir].myparentdir;
			}
		}
		else if (std::regex_match(line, std::regex("\\$ ls"))) {
			//BLAH
		}
		else if (std::regex_match(line, sm, std::regex("dir (.*)"))) {
			string s = sm[1];
			if (!dirmap.count(currentdir + s)) {
				dirmap[currentdir + s] = dir(currentdir + s, currentdir);
			}
		}
		else if (std::regex_match(line, sm, std::regex("(\\d+).*"))) {
			string s = sm[1];
			string tempcurrentdir = currentdir;
			do {
				dirmap[tempcurrentdir].mysize += stoi(s);
			} while ((tempcurrentdir = dirmap[tempcurrentdir].myparentdir) != "NULL");
		}
		else {
			cout << "ERROR" << endl;
		}
	}

	int total = 0;
	for (std::map<string, dir>::iterator it = dirmap.begin(); it != dirmap.end(); ++it) {
		if (it->second.mysize <= 100000) {
			total += it->second.mysize;
		}
	}
	cout << total;
	infile.close();
	return 0;
}
