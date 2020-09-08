/*
 * Author: Benjamin Mao
 * Project: Airport Simulation
 * Purpose: Class to query landings and takeoffs.
 *
 * Notes: None.
 */

#include "BooleanSource.h"

#include <iostream>

BooleanSource::BooleanSource(double takeoffProbability,
							 double landingProbability) :
	takeoffProbability(takeoffProbability),
	landingProbability(landingProbability)
{
	if (landingProbability > 1 || landingProbability < 0 ||
		takeoffProbability > 1 || takeoffProbability < 0)
		throw std::invalid_argument("Probability must be 0 < x <= 1");
}

bool BooleanSource::QueryTakeoff()
{
	return (rand() < takeoffProbability * RAND_MAX);
}

bool BooleanSource::QueryLanding()
{
	return (rand() < landingProbability * RAND_MAX);
}
