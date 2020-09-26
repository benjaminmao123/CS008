#include "AVL.h"
#include "FTokenizer.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

struct Word
{
	Word(const std::string& data) :
		data(data), frequency(1)
	{

	}

	bool operator==(const Word& other) const
	{
		return data == other.data;
	}

	bool operator<(const Word& other) const
	{
		return data < other.data;
	}

	bool operator>(const Word& other) const
	{
		return data > other.data;
	}

	friend std::ostream& operator<<(std::ostream& outs, const Word& rhs)
	{
		outs << "(" << rhs.data << ", " << rhs.frequency << ")";

		return outs;
	}

	std::string data;
	size_t frequency;
};

void PrintWordFrequencies(int n, AVL<Word>& words);

int main()
{
	FTokenizer ftk("solitude.txt");
	AVL<Word> avl;
	int count = 0;
	std::ofstream ofs("output.txt");

	while (ftk.more())
	{
		Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
		{
			ofs << std::setw(10) << count
				<< std::setw(3) << std::left << ":" << std::setw(25) << std::left << t.token_str()
				<< t.type_string() << std::endl;

			std::cout << std::setw(10) << count++
				<< std::setw(3) << std::left << ":" << std::setw(25) << std::left << t.token_str()
				<< t.type_string() << std::endl;

			Word word(t.token_str());
			tree_node<Word>* fptr;

			if (!avl.search(word, fptr))
				avl.insert(word);
			else
				++fptr->_item.frequency;
		}
	}

	std::cout << std::endl;

	PrintWordFrequencies(20, avl);

	return 0;
}

void PrintWordFrequencies(int n, AVL<Word>& words)
{
	std::vector<Word> wordList;

	for (const auto& i : words)
		wordList.emplace_back(i);

	std::sort(wordList.begin(), wordList.end(),
			  [](Word w1, Word w2)
			  {
				  return w1.frequency > w2.frequency;
			  });

	for (unsigned int i = 0; i < 20 && i < wordList.size(); ++i)
		std::cout << i + 1 << ". " << wordList[i] << std::endl;
}
