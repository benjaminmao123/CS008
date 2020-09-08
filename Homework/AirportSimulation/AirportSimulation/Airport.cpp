/*
 * Author: Benjamin Mao
 * Project: Airport Simulation
 * Purpose: Class to run the airport simulation.
 *
 * Notes: None.
 */

#include "Airport.h"

Airport::Airport(unsigned int takeoffTime,
				 double takeoffProbability,
				 unsigned int landingTime,
				 double landingProbability,
				 unsigned int fuelLimit,
				 unsigned int totalTime) :
	takeoffTime(takeoffTime),
	takeoffProbability(takeoffProbability),
	landingTime(landingTime),
	landingProbability(landingProbability),
	fuelLimit(fuelLimit),
	totalTime(totalTime),
	currentTime(1),
	totalCrashes(0),
	totalLanded(0),
	totalTakeoffs(0),
	landingCooldown(0),
	takeoffCooldown(0)
{
	if (landingProbability > 1 || landingProbability < 0 ||
		takeoffProbability > 1 || takeoffProbability < 0)
		throw std::invalid_argument("Probability must be 0 < x <= 1");
}

bool Airport::Run()
{
	while (currentTime <= totalTime)
		Step();

	PrintResult();

	return true;
}

void Airport::Step()
{
	ProcessQueries();

	if (!IsBusy())
	{
		if (!ProcessLandings())
			ProcessTakeoffs();
	}

	ProcessCooldowns();

	++currentTime;
}

void Airport::ProcessQueries()
{
	if (source.QueryLanding())
		landingQueue.push(currentTime);
	if (source.QueryTakeoff())
		takeoffQueue.push(currentTime);
}

bool Airport::IsBusy() const
{
	return (landingCooldown > 0 || takeoffCooldown > 0);
}

bool Airport::ProcessLandings()
{
	if (!landingQueue.empty())
	{
		unsigned int currentLandingTime = landingQueue.pop();

		if ((currentTime - currentLandingTime) > fuelLimit)
			++totalCrashes;
		else
		{
			landingTimeAverager.AddNumber((double)currentTime - currentLandingTime);
			landingCooldown = landingTime;
			++totalLanded;
		}

		return true;
	}

	return false;
}

bool Airport::ProcessTakeoffs()
{
	if (!takeoffQueue.empty())
	{
		unsigned int currentTakeoffTime = takeoffQueue.pop();

		takeoffTimeAverager.AddNumber((double)currentTime - currentTakeoffTime);
		takeoffCooldown = takeoffTime;
		++totalTakeoffs;

		return true;
	}

	return false;
}

void Airport::ProcessCooldowns()
{
	if (landingCooldown > 0)
		--landingCooldown;
	if (takeoffCooldown > 0)
		--takeoffCooldown;
}

void Airport::PrintResult() const
{
	std::cout << "Time to take off: " << takeoffTime << std::endl;
	std::cout << "Time to land: " << landingTime << std::endl;
	std::cout << "Probability of landing: " << landingProbability << std::endl;
	std::cout << "Probability of takeoff: " << takeoffProbability << std::endl;
	std::cout << "Time to crash: " << fuelLimit << std::endl;
	std::cout << "Total simulation time: " << totalTime << std::endl;

	std::cout << std::endl;

	std::cout << "Total landed: " << totalLanded << std::endl;
	std::cout << "Total takeoffs: " << totalTakeoffs << std::endl;
	std::cout << "Total crashes: " << totalCrashes << std::endl;
	std::cout << "Average waiting time to land: " << landingTimeAverager.GetCurrentAverage() << std::endl;
	std::cout << "Average waiting time to takeoff: " << takeoffTimeAverager.GetCurrentAverage() << std::endl;
	std::cout << "Planes in landing queue: " << landingQueue.size() << std::endl;
	std::cout << "Planes in takeoff queue: " << takeoffQueue.size() << std::endl;
}
