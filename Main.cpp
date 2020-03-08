#include "Trie.hpp"

#include <fstream>

void inline stripApos(std::string& str)
{
	if(str.front() == '\'')
		str.erase(str.begin());
	if(str[0] == '\'' && str[1] == '\'')
		str.erase(str.begin(), str.begin() + 2);

	if(str.back() == '\'')
		str.erase(str.end() - 1);
	if(str.back() == '\'' && *(str.end() - 1) == '\'')
		str.erase(str.end() - 2, str.end());
}

void rmSymbol(std::string& str)
{
	stripApos(str);
	for(std::string::iterator chr = str.begin(); chr != str.end(); ++chr)
		if(*chr == '\'' || (*chr >= 'a' && *chr <= 'z'))
			continue;
		else if(*chr >= 'A' && *chr <= 'Z')
			*chr += 32U;
		else
			str.erase(chr--);
	stripApos(str);
}

void loadStops(Trie& stop)
{
	std::ifstream file("./stop-words.txt");
	std::string line;
	while(file >> line)
	{
		rmSymbol(line);
		stop.push(line);
	}
	file.close();
}

void loadData(Trie& trie, const Trie& stop)
{
	std::ifstream tweet("./processed.csv");
	std::string word;
	while(tweet >> word)
	{
		rmSymbol(word);
		if(word.length() < 9 && !stop.search(word))
			trie.push(word);
	}
	tweet.close();
}

int main()
{
	Trie trie;
	{
		Trie stop;
		loadStops(stop);
		loadData(trie, stop);
		// TODO Make a recursive ~Trie so every child is murdered
	}

	std::cout << "Total Words Stored:\t" << trie.wordCount(trie.root) << std::endl;

	unsigned int level = 0;
	char str[16];
	trie.topWords(trie.root, str, level);
	std::cout << std::endl;
	trie.printTop(10U);

	return 0;
}

