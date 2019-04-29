#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

class Tree {
public:
	class Node;

	Tree(const int &t_key, const int &t_data)
	{
		m_root = new Node(t_key, t_data);
	}

	~Tree()
	{
		if (m_root) {
			delete m_root;
		}
	}

		class Node {
	public:
		Node(const int &t_key, const int &t_data)
		 : key(t_key), data(t_data), leftChild(nullptr), rightChild(nullptr)
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
		int data;
		Node *leftChild;
		Node *rightChild;
	};

	Node *m_root;
};

class Compare {
public:
	bool operator() (const Tree *tree1, const Tree *tree2) const
	{
		return (tree1->m_root->key > tree2->m_root->key);
	}
};

Tree *buildTree(const std::string &text) {
	std::map<char, int> frequencyByCharacters;

	for (char character : text) {
		std::map<char,int>::iterator it = frequencyByCharacters.find(character);

		if (it != frequencyByCharacters.end()) {
			++it->second;
		} else {
			frequencyByCharacters.insert(std::pair<char, int>(character, 1));
		}
	}

	for (auto m : frequencyByCharacters) {
		std::cout << m.first << " - " << m.second << std::endl;
	}

	std::priority_queue<Tree *, std::vector<Tree *>, Compare> queue;

	for (auto m : frequencyByCharacters) {
		queue.push(new Tree(m.second, m.first));
	}

	while (!queue.empty()) {
		std::cout << queue.top()->m_root->key << std::endl;
		queue.pop();
	}

	return nullptr;
}

int main(int argc, char const *argv[])
{
	std::string text = "SUISIE SAYS IT IS EASY";

	buildTree(text);

	return 0;
}