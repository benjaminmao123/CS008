/*
 * Author: Benjamin Mao
 * Project: Recursive Functions
 * Purpose: Driver class
 *
 * Notes: None.
 */

#include <iostream>
#include <string>

using namespace std;

void R1_levels(int current, int max);
void R2_box(const string& prefix, unsigned int levels);
void R3_first_second(string first, string second);
unsigned int R4_boxes(string label);
double R5_sumover(unsigned int n);
void R16_guess(unsigned int low, unsigned int high);

int main()
{
	R1_levels(1, 4);
	cout << endl;
	R2_box("BOX:", 3);
	cout << endl;
	R3_first_second("CAT", "MAN");
	cout << endl;
	cout << "Total boxes: " << R4_boxes("") << endl << endl;
	cout << R5_sumover(3) << endl << endl;
	R16_guess(1, 1000000);

	return 0;
}

void R1_levels(int current, int max)
{
	cout << "This was written by call number " << current << endl;

	if (current >= max)
	{
		cout << "This was ALSO written by call number " << current << endl;
		return;
	}

	R1_levels(current + 1, max);

	cout << "This was ALSO written by call number " << current << endl;
}

void R2_box(const string& prefix, unsigned int levels)
{
	if (!levels)
	{
		cout << prefix << endl;
		return;
	}

	for (int i = 1; i <= 9; ++i)
	{
		string dot;
		levels == 1 ? dot = "" : dot = ".";
		string s = prefix + std::to_string(i) + dot;

		R2_box(s, levels - 1);
	}
}

void R3_first_second(string first, string second)
{
	if (first.empty())
	{
		cout << second << endl;
		return;
	}

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		R3_first_second(first.substr(1), first[0] + second);
		rotate(first.begin(), first.begin() + 1, first.end());
	}
}

unsigned int R4_boxes(string label)
{
	static unsigned int numBoxes = 0;
	unsigned int input;

	if (!label.empty())
		cout << "You are in box: " << label << endl;

	cout << "How many boxes do you see?: ";
	cin >> input;
	cout << endl;

	numBoxes += input;

	label += label.empty() ? "" : ".";

	for (unsigned int i = 1; i <= input; ++i)
		R4_boxes(label + to_string(i));

	return numBoxes;
}

double R5_sumover(unsigned int n)
{
	if (!n)
		return 0.0;

	return (double)1 / n + R5_sumover(n - 1);
}

void R16_guess(unsigned int low, unsigned int high)
{
	string input;

	if (high >= low)
	{
		unsigned int mid = low + (high - low) / 2;

		while (input != "y" && input != "n")
		{
			cout << "Is your number " << mid << "? (y/n): ";
			cin >> input;
		}

		if (input == "y")
			return;

		while (input != "l" && input != "h")
		{
			cout << "Is your number lower or higher than " << mid << "? (l/h): ";
			cin >> input;
		}

		if (input == "l")
			R16_guess(low, mid - 1);
		else
			R16_guess(mid + 1, high);
	}
	else
		cout << "You're a big fat liar." << endl;
}
