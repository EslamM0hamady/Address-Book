#include <iostream>
#include <vector>
using namespace std;
class Node {
public:
	pair<int, vector<string>> data;
	int height;
	Node *left, *right;

	Node(int key) {
		left = right = nullptr;
		data.first = key;
		height = 1;
	}
	Node(int key, string name, string phone, string email) {
		left = right = nullptr;
		data.first = key;
		data.second.push_back(name);
		data.second.push_back(phone);
		data.second.push_back(email);
		height = 1;
	}
};

class AddressBook {
private:
	Node *root;

	int height(Node* node) {
		return node ? node->height : 0;
	}

	int getBalance(Node* node) {
		return node ? height(node->left) - height(node->right) : 0;
	}

	Node* findMin(Node* node) {
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	void updateHeight(Node* node) {
		node->height = 1 + max(height(node->left), height(node->right));
	}

	Node* rightRotate(Node* y) {
		Node* x = y->left;
		Node* T2 = x->right;
		x->right = y;
		y->left = T2;
		updateHeight(y);
		updateHeight(x);
		return x;
	}

	Node* leftRotate(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;
		y->left = x;
		x->right = T2;
		updateHeight(x);
		updateHeight(y);
		return y;
	}

	Node* balance(Node* node) {
		updateHeight(node);
		int balanceFactor = getBalance(node);
		if (balanceFactor > 1) {
			if (getBalance(node->left) >= 0) {
				return rightRotate(node);
			} else {
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
		}
		if (balanceFactor < -1) {
			if (getBalance(node->right) <= 0) {
				return leftRotate(node);
			} else {
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
		}
		return node;
	}

	Node* insert(Node* node, int key, string name, string phone, string email) {
		if (node == nullptr) {
			return new Node(key, name, phone, email);
		}
		if (key < node->data.first) {
			node->left = insert(node->left, key,name, phone, email);
		} else if (key > node->data.first) {
			node->right = insert(node->right, key,name, phone, email);
		} else {
			return node;
		}
		return balance(node);
	}

	Node* search(Node* node, int key) {
		while (node != nullptr && node->data.first != key) {
			if (key < node->data.first) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return node;
	}

	Node* remove(Node* node, int key) {
		if (node == nullptr) {
			return node;
		}
		if (key < node->data.first) {
			node->left = remove(node->left, key);
		} else if (key > node->data.first) {
			node->right = remove(node->right, key);
		} else {
			if (node->left == nullptr || node->right == nullptr) {
				Node* temp = node->left ? node->left : node->right;
				delete node;
				return temp;
			} else {
				Node* succ = findMin(node->right);
				node->data.first = succ->data.first;
				node->right = remove(node->right, succ->data.first);
			}
		}
		return balance(node);
	}

	void inOrder(Node* node) {
		if (node == nullptr) {
			return;
		}
		inOrder(node->left);
		cout << "ID: " << node->data.first << "\n";
		cout << "Name: " << node->data.second[0] << "\n";
		cout << "Phone: " << node->data.second[1] << "\n";
		cout << "Email: " << node->data.second[2] << "\n";
		inOrder(node->right);
	}

public:
	AddressBook() {
		root = nullptr;
	}

	void insert(int key, string name, string phone, string email) {
		root = insert(root, key, name, phone, email);
	}

	Node* search(int key) {
		return search(root, key);
	}

	void remove(int key) {
		root = remove(root, key);
	}

	void printInOrder() {
		inOrder(root);
		cout << "\n";
	}
};


int main() {

}
