#include "AVL.h"
#include "FTokenizer.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

struct Word
{
	Word(const std::string& data, size_t freq = 1) :
		data(data), frequency(freq)
	{

	}

	Word& operator+=(const Word& other)
	{
		frequency += 1;

		return *this;
	}

	bool operator==(const Word& other) const
	{
		return data == other.data;
	}

	bool operator<(const Word& other) const
	{
		return frequency < other.frequency;
	}

	bool operator>(const Word& other) const
	{
		return frequency > other.frequency;
	}

	friend std::ostream& operator<<(std::ostream& outs, const Word& rhs)
	{
		outs << "(" << rhs.data << ", " << rhs.frequency << ")" << std::endl;

		return outs;
	}

	std::string data;
	size_t frequency;
};

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
			avl.insert(word);
		}
	}

	std::cout << std::endl;

	avl.print_top_n(20);

	return 0;
}