#pragma once

#include <vector>

class Averager
{
public:
	void AddNumber(double value);
	double GetCurrentAverage() const;
	void Clear();

private:
	std::vector<double> numbers;
};