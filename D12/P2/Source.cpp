#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

vector<vector<int>> matrix;
typedef int row_t;
typedef int col_t;
class node;
class edge;
vector<node*> nodes;
vector<edge*> edges;
constexpr auto MAX_INT = 100000;

class node {
public:
	pair <row_t, col_t> position;
	int distance_from_start;
	int height;
	node* previous;
	node(pair <row_t, col_t> position, int height) {
		this->position = position;
		this->distance_from_start = MAX_INT;
		this->height = height;
		this->previous = NULL;
		nodes.push_back(this);
	}
};

class edge {
public:
	node* fromnode;
	node* tonode;
	int distance;

	edge(node* node1, node* node2, int distance_between_nodes = 1) {
		this->fromnode = node1;
		this->tonode = node2;
		distance = distance_between_nodes;
		edges.push_back(this);
	}

	bool connects(node* node1, node* node2) {
		return ((this->fromnode == node1 && this->tonode == node2));
	}
};

bool contains_node(node* node) {
	const size_t size = nodes.size();
	for (size_t i = 0; i < size; i++) {
		if (node == nodes.at(i)) {
			return true;
		}
	}
	return false;
}

bool contains_node(pair<row_t, col_t> position) {
	const size_t size = nodes.size();
	for (size_t i = 0; i < size; i++) {
		if (position == nodes[i]->position) {
			return true;
		}
	}
	return false;
}

node* get_node_at_position(pair<row_t, col_t> position) {
	const size_t size = nodes.size();
	for (size_t i = 0; i < size; i++) {
		if (position == nodes[i]->position) {
			return nodes[i];
		}
	}
	return NULL;
}

int distance_between_nodes(node* node1, node* node2) {
	const size_t size = edges.size();
	for (size_t i = 0; i < size; i++) {
		if (edges[i]->connects(node1, node2)) {
			return edges[i]->distance;
		}
	}
	return MAX_INT;
}

vector<node*> get_adjacent_nodes(node* n) {
	vector<node*> adjacent_nodes;
	const size_t size = edges.size();
	for (size_t i = 0; i < size; i++) {
		edge* myedge = edges.at(i);
		node* adjacent = NULL;
		if (myedge->fromnode == n) {
			adjacent = myedge->tonode;
		}
		if (adjacent != NULL && contains_node(adjacent)) {
			adjacent_nodes.push_back(adjacent);
		}
	}
	return adjacent_nodes;
}

node* get_smallest_node() {
	const size_t size = nodes.size();
	if (size == 0) {
		return NULL;
	}
	node* smallest = nodes.at(0);
	int index = 0;
	for (int i = 1; i < size; i++) {
		node* current = nodes.at(i);
		if (current->distance_from_start < smallest->distance_from_start) {
			smallest = current;
			index = i;
		}
	}
	nodes.erase(nodes.begin() + index);
	return smallest;
}

void dijkstras() {
	while (nodes.size() > 0) {
		node* smallest = get_smallest_node();
		vector<node*> adjacentNodes =
			get_adjacent_nodes(smallest);

		const size_t size = adjacentNodes.size();
		for (size_t i = 0; i < size; i++) {
			node* adjacent = adjacentNodes[i];
			int distance = distance_between_nodes(smallest, adjacent) +
				smallest->distance_from_start;

			if (distance < adjacent->distance_from_start) {
				adjacent->distance_from_start = distance;
				adjacent->previous = smallest;
			}
		}
	}
}

int get_steps_to(node* destination) {
	int steps = 0;
	node* previous = destination;
	cout << "Starting at:" << previous->position.first << " " << previous->position.second << endl;
	while (previous) {
		cout << "Moving to:" << previous->position.first << " " << previous->position.second << endl;
		previous = previous->previous;
		steps++;
	}
	cout << steps - 1 << endl;
	return steps - 1;
}

int main() {
	ifstream infile("Input.txt");
	string line;
	pair <row_t, col_t> start, end, current;
	vector<pair<row_t, col_t>> possible_starts;

	while (getline(infile, line)) {
		vector<int> lineval;
		for (size_t i = 0; i < line.size(); i++) {
			char linechar = line[i];
			if (linechar == 'S') {
				linechar = 'a';
				start = { matrix.size(),i };
				current = start;
				possible_starts.push_back(start);
			}
			else if (linechar == 'E') {
				linechar = 'z';
				end = { matrix.size(),i };
			}
			lineval.push_back(linechar - 'a');
			if (linechar == 'a') {
				possible_starts.push_back({ matrix.size(), i });
			}
		}
		matrix.push_back(lineval);
	}
	infile.close();

	size_t num_rows = matrix.size();
	size_t num_cols = matrix[0].size();
	for (size_t _row = 0; _row < num_rows; _row++) {
		for (size_t _col = 0; _col < num_cols; _col++) {
			pair<row_t, col_t> position = { _row,_col };
			node* mynode = new node(position, matrix[position.first][position.second]);
		}
	}
	for (size_t _row = 0; _row < num_rows; _row++) {
		for (size_t _col = 0; _col < num_cols; _col++) {
			pair<row_t, col_t> position = { _row,_col };
			node* mynode = get_node_at_position({ position.first    , position.second });
			node* upsy = get_node_at_position({ position.first - 1, position.second });
			node* down = get_node_at_position({ position.first + 1, position.second });
			node* left = get_node_at_position({ position.first    , position.second - 1 });
			node* rite = get_node_at_position({ position.first    , position.second + 1 });
			if (upsy != NULL && (mynode->height  <= upsy->height + 1)) {
				edge* myedge = new edge(mynode, upsy);
			}
			if (down != NULL && (mynode->height  <= down->height + 1)) {
				edge* myedge = new edge(mynode, down);
			}
			if (left != NULL && (mynode->height  <= left->height + 1)) {
				edge* myedge = new edge(mynode, left);
			}
			if (rite != NULL && (mynode->height  <= rite->height + 1)) {
				edge* myedge = new edge(mynode, rite);
			}
		}
	}
	node* start_node = get_node_at_position(end);
	vector<node*> end_nodes;
	for (int i = 0; i < possible_starts.size(); i++) {
		end_nodes.push_back(get_node_at_position(possible_starts[i]));
	}
	start_node->distance_from_start = 0;
	dijkstras();
	
	int lowest = 10000;
	for (int i = 0; i < end_nodes.size(); i++) {
		int steps = get_steps_to(end_nodes[i]);
		if (steps < lowest && steps) {
			lowest = steps;
		}
	}
	cout << lowest;
}
