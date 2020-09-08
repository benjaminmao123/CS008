#pragma once

#include <cstdlib>
#include <ctime>

class BooleanSource
{
public:
	BooleanSource(double takeoffProbability = 0.8,
				  double landingProbability = 0.1);

	bool QueryTakeoff();
	bool QueryLanding();

private:
	double takeoffProbability;
	double landingProbability;
};