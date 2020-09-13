#include <iostream>
#include <string>

using namespace std;

void problem9_1(int current, int max);
void problem9_2(const string& prefix, unsigned int levels);
void problem9_3(string first, string second);
void problem9_4();
void problem9_5();
void problem9_16();

int main()
{
	//problem9_1(1, 4);
	//problem9_2("BOX:", 3);
	problem9_3("CAT", "MAN");

	return 0;
}

void problem9_1(int current, int max)
{
	cout << "This was written by call number " << current << endl;

	if (current >= max)
	{
		cout << "This was ALSO written by call number " << current << endl;
		return;
	}

	problem9_1(current + 1, max);

	cout << "This was ALSO written by call number " << current << endl;
}

void problem9_2(const string& prefix, unsigned int levels)
{
	if (!levels)
	{
		cout << prefix << endl;
		return;
	}

	for (int i = 1; i <= 9; ++i)
	{
		string dot;

		if (levels == 1) dot = "";
		else dot = ".";

		string s = prefix + std::to_string(i) + dot;

		problem9_2(s, levels - 1);
	}
}

void problem9_3(string first, string second)
{
	if (first.empty())
	{
		std::cout << second << std::endl;
		return;
	}

	
}
