#include <iostream>
#include <vector>

class Node {
public:
	int val;
	std::vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = std::vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = std::vector<Node*>();
	}
	Node(int _val, std::vector<Node*> _neighbors;
};

Node* cloneGraph(Node* node);


int main() {
	unordered_map<Node*, Node*> visited;
	Node* node;
    std::cout << cloneGraph(node) << std::endl;
    return 0;
}

Node* cloneGraph(Node* node) {
	if (node == nullptr) return nullptr;
	if (visited.find(node) != visited.end()) return visited[node];
	Node* cloneNode = new Node(node->val);
	visited[node] = cloneNode;
	for (auto& neighbor : node->neighbors)
		cloneNode->neighbors.emplace_back(cloneGraph(neighbor));
	return cloneNode;
}
