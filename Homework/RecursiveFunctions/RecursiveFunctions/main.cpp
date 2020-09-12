#include <iostream>
#include <string>

using namespace std;

void problem9_1(int current, int max);
void problem9_2(string prefix, unsigned int levels);
void problem9_3();
void problem9_4();
void problem9_5();
void problem9_16();

int main()
{
	//problem9_1(1, 4);
	problem9_2("BOX:", 2);

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

void problem9_2(string prefix, unsigned int levels)
{
	if (!levels)
		return;

	string s = prefix;

	for (int i = 1; i < 10; ++i)
	{

	}

	cout << s << endl;
}
