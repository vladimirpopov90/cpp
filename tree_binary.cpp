#include <iostream>
#include <vector>

class Tree
{
private:
    class Node;

public:
    Tree() : m_root(nullptr) {};
    ~Tree()
    {
        if (!m_root) {
            deleteTree(m_root);
        }
    }

    void insert(const int& t_key, const int& t_value);
    void find(const int& t_key);
    void deleteNode(const int& t_key);
    void inorder(const Node* t_node);
    void deleteTree(const Node* t_node);
    void printInOrder();
    void displayTree();

private:
    class Node {
    public:
        Node(const int& t_key, const int& t_value) 
         : key(t_key), value(t_value), leftChild(nullptr), rightChild(nullptr)
        {}

        ~Node() {}

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
        Node *parent = m_root;
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
        	if (nodeToDelete == m_root) {
        		delete nodeToDelete;
        		m_root = nullptr;
        		return;
        	}

            if (isLeftChild) {
                parent->leftChild = nullptr;
            } else {
                parent->rightChild = nullptr;
            }
        } else if (!nodeToDelete->leftChild) {
        	if (nodeToDelete == m_root) {
        		m_root = nodeToDelete->leftChild;
        		return;
        	}

            if (isLeftChild) {
                parent->leftChild = nodeToDelete->leftChild;
            } else {
                parent->rightChild = nodeToDelete->leftChild;
            }
        } else if (!nodeToDelete->rightChild) {
        	if (nodeToDelete == m_root) {
        		m_root = nodeToDelete->rightChild;
        		return;
        	}

            if (isLeftChild) {
                parent->leftChild = nodeToDelete->rightChild;
            } else {
                parent->rightChild = nodeToDelete->rightChild;
            }
        } else {
        	if (nodeToDelete == m_root) {
        		deleteTree(m_root);
        		return;
        	}

            Node *successorParent = nodeToDelete;
            Node *successor = nodeToDelete;
            Node *current = nodeToDelete->rightChild;

            while (current) {
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

void Tree::deleteTree(const Node* t_node)
{
    if (!t_node) {
        return;
    } else {
        deleteTree(t_node->leftChild);
        Node *rightChild = t_node->rightChild;
        delete t_node;
        deleteTree(rightChild);
    }
}


void Tree::printInOrder() {
    inorder(m_root);
}

void Tree::displayTree()
{
    std::vector<Node *> globalStackNodes;
    globalStackNodes.push_back(m_root);
    int numberOfBlanks = 32;
    bool isRowEmpty = false;

    while (!isRowEmpty) {
        std::vector<Node *> localStackNodes;
        isRowEmpty = true;

        for (int i = 0; i < numberOfBlanks; ++i) {
            std::cout << ' ';
        }

        while (!globalStackNodes.empty()) {
            Node *temp = globalStackNodes.back();
            globalStackNodes.pop_back();

            if (temp) {
            	std::cout << temp->key;
            	localStackNodes.push_back(temp->leftChild);
            	localStackNodes.push_back(temp->rightChild);

            	if (temp->leftChild || temp->rightChild) {
                    isRowEmpty = false;
            	}
            } else {
            	std::cout << "--";
            	localStackNodes.push_back(nullptr);
            	localStackNodes.push_back(nullptr);
            }

            for (int i = 0; i < numberOfBlanks*2-2; ++i) {
	            std::cout << ' ';
	        }
        }  

        std::cout << std::endl;
	    numberOfBlanks /= 2;

	    while (!localStackNodes.empty()) {
	      	globalStackNodes.push_back(localStackNodes.back());
	       	localStackNodes.pop_back();
	    }      
    }
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
    tree.insert(27, 27);
    tree.insert(35, 35);
    tree.insert(33, 33);
    tree.insert(34, 34);
    tree.insert(37, 37);

    tree.displayTree();

    tree.deleteNode(30);

    tree.displayTree();

    return 0;
}