#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Quad {
	int _key;
	string _name;
	string _phone;
	string _email;
};

class Node {
public:
	Quad data;
	int height;
	Node *left, *right;

	Node(int key) {
		left = right = nullptr;
		data._key = key;
		height = 1;
	}

	Node(int key, string name, string phone, string email) {
		left = right = nullptr;
		data._key = key;
		data._name = name;
		data._phone = phone;
		data._email = email;
		height = 1;
	}
};

class AddressBook {
private:
	Node *root;

	int height(Node *node) {
		return node ? node->height : 0;
	}

	int getBalance(Node *node) {
		return node ? height(node->left) - height(node->right) : 0;
	}

	Node *findMin(Node *node) {
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	void updateHeight(Node *node) {
		node->height = 1 + max(height(node->left), height(node->right));
	}

	Node *rightRotate(Node *y) {
		Node *x = y->left;
		Node *T2 = x->right;
		x->right = y;
		y->left = T2;
		updateHeight(y);
		updateHeight(x);
		return x;
	}

	Node *leftRotate(Node *x) {
		Node *y = x->right;
		Node *T2 = y->left;
		y->left = x;
		x->right = T2;
		updateHeight(x);
		updateHeight(y);
		return y;
	}

	Node *balance(Node *node) {
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

	Node *insert(Node *node, int key, string name, string phone, string email) {
		if (node == nullptr) {
			return new Node(key, name, phone, email);
		}
		if (key < node->data._key) {
			node->left = insert(node->left, key, name, phone, email);
		} else if (key > node->data._key) {
			node->right = insert(node->right, key, name, phone, email);
		} else {
			return node;
		}
		return balance(node);
	}

	Node *search(Node *node, int key) {
		while (node != nullptr && node->data._key != key) {
			if (key < node->data._key) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return node;
	}

	Node *remove(Node *node, int key) {
		if (node == nullptr) {
			return node;
		}
		if (key < node->data._key) {
			node->left = remove(node->left, key);
		} else if (key > node->data._key) {
			node->right = remove(node->right, key);
		} else {
			if (node->left == nullptr || node->right == nullptr) {
				Node *temp = node->left ? node->left : node->right;
				delete node;
				return temp;
			} else {
				Node *succ = findMin(node->right);
				node->data._key = succ->data._key;
				node->right = remove(node->right, succ->data._key);
			}
		}
		return balance(node);
	}

	void inOrder(Node *node) {
		if (node == nullptr) {
			return;
		}
		inOrder(node->left);
		cout << "ID: " << node->data._key << "\n";
		cout << "Name: " << node->data._name << "\n";
		cout << "Phone: " << node->data._phone << "\n";
		cout << "Email: " << node->data._email << "\n";
		inOrder(node->right);
	}

	void printPretty(Node *root) {
		int totalNodes = pow(2, height(root)) - 1;
		vector<Node *> nodes;
		nodes.push_back(root);
		for (int i = 0; i < totalNodes / 2; ++i) {
			nodes.push_back(nodes[i] && nodes[i]->left ? nodes[i]->left : nullptr);
			nodes.push_back(nodes[i] && nodes[i]->right ? nodes[i]->right : nullptr);
		}
		int initialSpacing = (totalNodes + 1);
		for (int i = 0; i < initialSpacing; ++i) {
			cout << " ";
		}
		int spacing = initialSpacing / 2;
		int endOfLevel = 0;
		int nextLevelStart = 1;
		int spaceAfterPair = totalNodes;
		int levelWidth = 2;
		cout << nodes.front()->data._key << "\n";
		for (int i = 0; i < totalNodes / 2; ++i) {
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			if ((left - 1) / 2 == nextLevelStart || left == 1) {
				for (int t = 0; t < spacing; ++t) {
					cout << " ";
				}
				if (left != 1) {
					nextLevelStart = nextLevelStart * 2 + 1;
				}
			}
			if (nodes[i] && nodes[i]->left) {
				cout << nodes[i]->left->data._key;
			} else {
				cout << " ";
			}
			for (int j = 0; j < spacing * 2 - 1; ++j) {
				cout << " ";
			}
			if (nodes[i] && nodes[i]->right) {
				cout << nodes[i]->right->data._key;
			} else {
				cout << " ";
			}
			for (int k = 0; k < spaceAfterPair; ++k) {
				cout << " ";
			}
			if ((right - 1) / 2 == endOfLevel) {
				cout << "\n";
				endOfLevel += levelWidth;
				levelWidth *= 2;
				spaceAfterPair /= 2;
				spacing /= 2;
			}
		}
	}

public:
	AddressBook() {
		root = nullptr;
	}

	void displayAsTree() {
		printPretty(root);
	}

	void insert(int key, string name, string phone, string email) {
		root = insert(root, key, name, phone, email);
	}

	Node *search(int key) {
		return search(root, key);
	}

	void remove(int key) {
		root = remove(root, key);
	}

	void printInOrder() {
		inOrder(root);
		cout << "\n";
	}

	void printNode(int key) {
		Node *node = search(key);
		if (node != nullptr) {
			cout << "ID: " << node->data._key << "\n";
			cout << "Name: " << node->data._name << "\n";
			cout << "Phone: " << node->data._phone << "\n";
			cout << "Email: " << node->data._email << "\n";
		}
	}
};

class Menu {
public:
	static void firstMenu() {
		int choice;
		AddressBook ab;
		do {
			cout << "Address Book Application\n";
			cout << "------------------------\n";
			cout << "1. Add new contact\n";
			cout << "2. Search for contact\n";
			cout << "3. Delete contact\n";
			cout << "4. List all contacts\n";
			cout << "5. Display current tree Structure\n";
			cout << "0. Exit\n";
			cout << "------------------------\n";
			cout << "Enter operation (1-5): ";
			cin >> choice;
			if (choice == 1) {
				int id;
				string name, phone, email;
				cout << "Enter unique ID: ";
				cin >> id;
				cin.ignore();
				cout << "Enter name: ";
				getline(cin, name);
				cout << "Enter phone: ";
				getline(cin, phone);
				cout << "Enter email: ";
				getline(cin, email);
				if (ab.search(id) == nullptr) {
					ab.insert(id, name, phone, email);
					cout << "Contact added successfully.\n";
				} else {
					cout << "Contact with ID " << id << " already exists.\n";
				}
			} else if (choice == 2) {
				int id;
				cout << "Enter ID to search: ";
				cin >> id;
				if (ab.search(id) != nullptr) {
					cout << "Contact found: \n";
					ab.printNode(id);
				} else {
					cout << "Contact not found.\n";
				}
			} else if (choice == 3) {
				int id;
				cout << "Enter ID to delete: ";
				cin >> id;
				if (ab.search(id) != nullptr) {
					ab.remove(id);
					cout << "Contact deleted successfully.\n";
				} else {
					cout << "Contact not found.\n";
				}
			} else if (choice == 4) {
				ab.printInOrder();
			} else if (choice == 5) {
				ab.displayAsTree();
			} else if (choice == 0) {
				cout << "Program exited successfully. See you next time!\n";
				break;
			} else {
				cout << "Invalid choice. Please try again.\n";
			}
		} while (true);
	}
};

int main() {
	Menu::firstMenu();
}
