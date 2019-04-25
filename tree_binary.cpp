#include <iostream>

class Tree
{
private:
	class Node;

public:
	Tree() : m_root(nullptr) {};
	~Tree()
	{
		if (!m_root) {
			delete m_root;
		}
	}

	void insert(const int& t_key, const int& t_value);
	void find(const int& t_key);
	void deleteNode(const int& t_key);
	void inorder(const Node* t_node);
	void printInOrder();

private:
	class Node {
	public:
		Node(const int& t_key, const int& t_value) 
		 : key(t_key), value(t_value), leftChild(nullptr), rightChild(nullptr)
		{}

		~Node() 
		{
			if (leftChild) {
				delete leftChild;
			}

			if (rightChild) {
				delete rightChild;
			}
		}

		int key;
		int value;
		Node *leftChild;
		Node *rightChild;
	};

	Node *findNode(const int& t_key);
	
	Node *m_root;
};

void Tree::find(const int& t_key)
{
	Node *foundNode = findNode(t_key);

	if (!foundNode) {
		std::cout << "Node with key \"" << t_key << "\" wasn\'t found." << std::endl;
	} else {
		std::cout << "Key: " << foundNode->key << " Value: " << foundNode->value << std::endl;
	}
}

Tree::Node* Tree::findNode(const int& t_key)
{
	if (!m_root) {
		return nullptr;
	} else {
		Node *current = m_root;

		while (current->key != t_key) {
			if (t_key < current->key) {
				current = current->leftChild;
			} else {
				current = current->rightChild;
			}

			if (!current) {
				return nullptr;
			}
		}

		return current;
	}
}

void Tree::insert(const int& t_key, const int& t_value)
{
	Node *newNode = new Node(t_key, t_value);

	if (!m_root) {
		m_root = newNode;
		return;
	} else {
		Node *current = m_root;
		Node *parent = nullptr;

		while (true) {
			parent = current;

			if (t_key < current->key) {
				current = current->leftChild;

				if (!current) {
					parent->leftChild = newNode;
					return;
				}
			} else {
				current = current->rightChild;

				if (!current) {
					parent->rightChild = newNode;
					return;
				}
			}
		}
	}
}

void Tree::deleteNode(const int& t_key)
{
	if (!m_root) {
		std::cout << "Tree is empty." << std::endl;
	} else {
		Node *nodeToDelete = m_root;
		Node *parent = nullptr;
		bool isLeftChild = false;

		while (nodeToDelete->key != t_key) {
			parent = nodeToDelete;

			if (t_key < nodeToDelete->key) {
				nodeToDelete = nodeToDelete->leftChild;
				isLeftChild = true;
			} else {
				nodeToDelete = nodeToDelete->rightChild;
				isLeftChild = false;
			}

			if (!nodeToDelete) {
				std::cout << "No node with key \"" << t_key << "\" to delete." << std::endl;
				return; 
			}
		}

		if (!nodeToDelete->leftChild && !nodeToDelete->rightChild) {
			if (isLeftChild) {
				parent->leftChild = nullptr;
			} else {
				parent->rightChild = nullptr;
			}
		} else if (nodeToDelete->leftChild) {
			if (isLeftChild) {
				parent->leftChild = nodeToDelete->leftChild;
			} else {
				parent->rightChild = nodeToDelete->leftChild;
			}
		} else if (nodeToDelete->rightChild) {
			if (isLeftChild) {
				parent->leftChild = nodeToDelete->rightChild;
			} else {
				parent->rightChild = nodeToDelete->rightChild;
			}
		} else {
			Node *successorParent = nodeToDelete;
			Node *successor = nodeToDelete;
			Node *current = nodeToDelete->rightChild;

			while (current->leftChild) {
				successorParent = successor;
				successor = current;
				current = current->leftChild;
			}

			if (successor != nodeToDelete->rightChild) {
				successorParent->leftChild = successor->rightChild;
				successor->rightChild = nodeToDelete->rightChild;
			}

			if (isLeftChild) {
				parent->leftChild = successor;
			} else {
				parent->rightChild = successor;
			}

			successor->leftChild = nodeToDelete->leftChild;
		}

		delete nodeToDelete;
	}
}

void Tree::inorder(const Node* t_node)
{
	if (!t_node) {
		return;
	} else {
		inorder(t_node->leftChild);
		std::cout << t_node->key << std::endl;
		inorder(t_node->rightChild);
	}
}

void Tree::printInOrder() {
	inorder(m_root);
}


int main()
{
	Tree tree;

	tree.insert(20, 20);
	tree.insert(10, 10);
	tree.insert(5, 5);
	tree.insert(15, 15);
    tree.insert(25, 25);
    tree.insert(22, 22);
    tree.insert(30, 30);
    tree.insert(35, 35);
    tree.insert(33, 33);
    tree.insert(34, 34);
    tree.insert(37, 37);

	tree.find(20);
	tree.find(10);
	tree.find(5);
	tree.find(15);
    tree.find(25);
    tree.find(22);
    tree.find(30);
    tree.find(35);
    tree.find(33);
    tree.find(34);
    tree.find(37);
	tree.find(0);

	tree.deleteNode(30);

	tree.find(20);
	tree.find(10);
	tree.find(5);
	tree.find(15);
    tree.find(25);
    tree.find(22);
    tree.find(30);
    tree.find(35);
    tree.find(33);
    tree.find(34);
    tree.find(37);
	tree.find(0);

	tree.printInOrder();

	return 0;
}