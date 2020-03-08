#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <queue>
#include <string>

struct TrieItem
{
	std::string word;
	uint32_t occurence;
	TrieItem(const char str[], uint32_t occ)
	{
		word = str;
		occurence = occ;
	}
	bool operator<(const TrieItem& other) const
	{
		return this->occurence < other.occurence;
	}
};

struct Node
{
	bool is_leaf;
	Node* children[27];
	uint32_t occurence;
};

class Trie
{
	private:
	std::priority_queue<TrieItem> pq;

	public:
	Node* root;
	Trie();
	~Trie();
	Node* addNode();
	void push(const std::string&);
	bool search(const std::string&) const;
	uint32_t wordCount(const Node*) const;
	void print(const Node*, char*, uint8_t) const;
	void topWords(const Node*, char*, uint8_t);
	void printTop(uint8_t);
};

// Start off with 27 children Nodes
Trie::Trie() { this->root = addNode(); }

Trie::~Trie()
{
	/* Node* curr = this->root; */
	/* while(!curr->is_leaf) */
	/* { */
	/* 	for(uint8_t i = 0U; i < 27U; ++i) */
	/* 	{ */
	/* 		if(curr->children[i]->is_leaf) delete curr->children[i++]; */
	/* 		else if(curr->children[i]) */
	/* 			curr = curr->children[i]; */
	/* 	} */
	/* } */
	delete this->root;
}

Node* Trie::addNode()
{
	Node* temp = new Node();
	for(int i = 0; i < 27; i++)
		temp->children[i] = nullptr;
	return temp;
}

void Trie::push(const std::string& str)
{
	if(str.empty())
		return;
	Node* curr = this->root;
	bool exists = false;
	for(unsigned int i = 0; i < str.length(); ++i)
	{
		size_t pos;
		pos = (str[i] == '\'') ? 26U : (str[i] - 'a');
		if(!curr->children[pos])
		{
			curr->children[pos] = addNode();
			exists = true;
		}
		curr = curr->children[pos];
	}
	curr->is_leaf = true;
	if(exists)
		curr->occurence = 1U;
	else
		++curr->occurence;
}

bool Trie::search(const std::string& str) const
{
	Node* curr = this->root;
	for(size_t i = 0; i < str.length(); ++i)
	{
		size_t pos = str[i] == '\'' ? 26U : (str[i] - 'a');
		if(!curr->children[pos])
			return false;
		curr = curr->children[pos];
	}
	return (curr && curr->is_leaf);
}

uint32_t Trie::wordCount(const Node* node) const
{
	uint32_t res = 0U;
	if(node->is_leaf)
		++res;
	for(unsigned int i = 0; i < 27U; i++)
		if(node->children[i])
			res += wordCount(node->children[i]);
	return res;
}

void Trie::print(const Node* node, char* str, uint8_t level) const
{
	if(node->is_leaf)
	{
		str[level] = '\0';
		// TODO setw() prettify
		std::cout << str << ":" << node->occurence << '\n';
	}
	for(int i = 0; i < 27; i++)
		if(node->children[i])
		{
			str[level] = (i == 26U) ? '\'' : (i + 'a');
			print(node->children[i], str, level + 1);
		}
}

void Trie::topWords(const Node* node, char* str, uint8_t level)
{
	if(node->is_leaf)
	{
		str[level] = '\0';
		if(node->occurence > 1024U)
		{
			// Make a system that clears the queue (last element basically) and
			// pushes those elements back
			TrieItem word(str, node->occurence);
			this->pq.push(word);
		}
	}
	for(uint8_t i = 0U; i < 27U; ++i)
		if(node->children[i])
		{
			str[level] = (i == 26U) ? '\'' : (i + 'a');
			topWords(node->children[i], str, level + 1);
		}
}

void Trie::printTop(uint8_t size)
{
	for(uint8_t i = 0; i < size; i++)
	{
		std::cout << this->pq.top().word << ':' << this->pq.top().occurence << std::endl;
		pq.pop();
	}
}

#endif

