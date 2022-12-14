#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

class element {
public:
	std::vector<element*> list;
	int value;
	bool empty = false;
	element() {}
	~element() {}
};

vector<string> convert_to_string_vec(string line) {
	size_t pos;
	size_t prevpos = 1;
	size_t searchpos = 1;
	vector<string> string_vec;
	while ((pos = line.find_first_of(",", searchpos)) != std::string::npos) {
		string element = line.substr(prevpos, pos - prevpos);
		searchpos = pos + 1;
		std::string::difference_type n1 = std::count(element.begin(), element.end(), '[');
		std::string::difference_type n2 = std::count(element.begin(), element.end(), ']');
		if (n1 != n2) continue;
		string_vec.push_back(element);
		prevpos = pos + 1;
	}
	string_vec.push_back(line.substr(prevpos, line.size() - prevpos - 1));
	return string_vec;
}

vector<element*> parse_line(string line) {
	vector<element*> list;
	vector<string> string_vec;

	string_vec = convert_to_string_vec(line);
	size_t size = string_vec.size();
	for (size_t i = 0; i < size; i++) {
		element *ele = new element;
		if (string_vec[i][0] == '[') {
			ele->list = parse_line(string_vec[i]);
		}
		else if (string_vec[i] == "") {
			ele->empty = true;
		}
		else {
			ele->value = stoi(string_vec[i]);
		}
		list.push_back(ele);
	}
	return list;
}

int compare_lists(vector<element*>, vector<element*>);
int compare_elements(element* ele1, element* ele2) {
	//order
	//-1 : continue
	// 0 : wrong order
	// 1 : right order
	int order = -1;
	if (ele1->empty == true && ele2->empty == false) {
		cout << "Left side ran out of items, so inputs are in the right order" << endl;
		return 1;
	}
	else if (ele1->empty == false && ele2->empty == true) {
		cout << "Right side ran out of items, so inputs are not in the right order" << endl;
		return 0;
	}
	else if (ele1->empty == true && ele2->empty == true) {
		return -1;
	}
	else if (ele1->list.size() == 0 && ele2->list.size() == 0) {
		//Both Ints
		cout << "Compare " << ele1->value << " vs " << ele2->value << endl;
		if (ele1->value < ele2->value) {
			cout << "Left side is smaller, so inputs are in the right order" << endl;
			return 1;
		}
		else if (ele1->value > ele2->value) {
			cout << "Right side is smaller, so inputs are not in the right order" << endl;
			return 0;
		}
		else {
			return -1;
		}
	}
	else if (ele1->list.size() != 0 && ele2->list.size() != 0) {
		//Both Lists
		return compare_lists(ele1->list, ele2->list);
	}
	else if (ele1->list.size() != 0 && ele2->list.size() == 0) {
		//List and Int
		element *tempele = new element;
		tempele->list.push_back(ele2);
		return compare_lists(ele1->list, tempele->list);
	}
	else if (ele1->list.size() == 0 && ele2->list.size() != 0) {
		//Int and List
		element *tempele = new element;
		tempele->list.push_back(ele1);
		return compare_lists(tempele->list, ele2->list);
	}
	return order; //SHOULD NOT HIT THIS
}

int compare_lists(vector<element*> list1, vector<element*> list2) {
	size_t size1 = list1.size();
	size_t size2 = list2.size();
	size_t size = std::max(size1, size2);
	int order = -1;

	for (size_t i = 0; i < size; i++) {
		if (i >= size1) {
			cout << "Left side ran out of items, so inputs are in the right order" << endl;
			return 1;
		}
		if (i >= size2) {
			cout << "Right side ran out of items, so inputs are not in the right order" << endl;
			return 0;
		}
		if ((order = compare_elements(list1.at(i), list2.at(i))) == -1) {
			continue;
		}
		return order;
	}
	return order;
}

bool compare_wrap(vector<element*> list1, vector<element*> list2) {
	int order = -1;

	order = compare_lists(list1, list2);
	if (order == 0) {
		//wrong order
		return false;
	}
	else if (order == 1) {
		//right order
		return true;
	}
}

int main() {
	ifstream infile("Input.txt");
	string line1, line2;
	vector<element*> list1;
	vector<element*> list2;
	vector<vector<element*>> vec;
	int product = 1;

	string div1 = "[[2]]";
	string div2 = "[[6]]";

	while (infile >> line1 >> line2) {
		list1 = parse_line(line1);
		list2 = parse_line(line2);
		vec.push_back(list1);
		vec.push_back(list2);
	}
	list1 = parse_line(div1);
	vec.push_back(list1);
	list2 = parse_line(div2);
	vec.push_back(list2);


	std::sort(vec.begin(), vec.end(), compare_wrap);

	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i] == list1 || vec[i] == list2) {
			product *= (i + 1);
		}
	}

	cout << product;
	infile.close();
	return 0;
}
