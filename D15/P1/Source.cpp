#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef pair<int, int> pos_t;
typedef pair<int, int> range_t;



int distance(pos_t pos1, pos_t pos2) {
	return std::abs(pos1.first - pos2.first) + std::abs(pos1.second - pos2.second);
}

bool compare(range_t a, range_t b) {
	return a.first < b.first;
}

int main() {
	ifstream infile("Input.txt");
	string line;
	bool init_done = false;
	int left, rite;


	vector<pos_t> sensors;
	map<pos_t, bool> beacons;
	map<pos_t, int> radius;
	map<pos_t, bool> check_sensor;
	vector<range_t> blocked;

	while (getline(infile, line)) {
		smatch sm;
		regex_match(line, sm, regex("Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)"));
		pos_t sense = { stoi(string(sm[1])), stoi(string(sm[2])) };
		pos_t beaco = { stoi(string(sm[3])), stoi(string(sm[4])) };
		sensors.push_back(sense);
		beacons[beaco] = true;
		radius[sense] = distance(sense, beaco);
	}

	int check = 2000000;
	int count = 0;

	size_t size = sensors.size();
	for (size_t i = 0; i < size; i++) {
		pos_t sensor = sensors[i];
		if (sensor.second + radius[sensor] >= check && sensor.second - radius[sensor] <= check) {
			//sensor inter
			check_sensor[sensor] = true;
		}
		else {
			check_sensor[sensor] = false;
		}
	}

	for (auto it = check_sensor.begin(); it != check_sensor.end(); it++) {
		if (it->second == true) {
			int dx = 0;
			int dy = 0;
			dy = std::abs(check - it->first.second);
			dx = radius[it->first] - dy;
			range_t range = {it->first.first - dx, it->first.first + dx };
			blocked.push_back(range);
		}
	}

	std::sort(blocked.begin(), blocked.end(), compare);

	size = blocked.size();
	range_t range = blocked[0];
	vector<range_t> newblocked;
	for (size_t i = 1; i < size; i++) {
		if (range.first <= blocked[i].second && blocked[i].first <= range.second) {
			//overlap
			range = {range.first, std::max(range.second, blocked[i].second)};
		}
		else {
			newblocked.push_back(range);
			range = blocked[i];
		}
	}
	newblocked.push_back(range);
	size = newblocked.size();
	for (size_t i = 0; i < size; i++) {
		count += (newblocked[i].second - newblocked[i].first + 1);
	}

	for (auto it = beacons.begin(); it != beacons.end(); it++) {
		if (it->first.second == check) {
			count--;
		}
	}

	cout << count;
	infile.close();
	return 0;
}
