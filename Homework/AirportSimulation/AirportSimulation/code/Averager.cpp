/*
 * Author: Benjamin Mao
 * Project: Airport Simulation
 * Purpose: Class to keep track of averages.
 *
 * Notes: None.
 */


#include "Averager.h"

#include <iostream>

void Averager::AddNumber(double value)
{
	numbers.emplace_back(value);
}

double Averager::GetCurrentAverage() const
{
	if (numbers.empty())
		return 0.0;

	double total = 0.0;

	for (const auto& num : numbers)
		total += num;

	return total / numbers.size();
}

void Averager::Clear()
{
	numbers.clear();
}
