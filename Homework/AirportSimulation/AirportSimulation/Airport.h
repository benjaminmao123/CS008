#pragma once

#include "Queue.h"
#include "BooleanSource.h"
#include "Averager.h"

class Airport
{
public:
    Airport(unsigned int takeoffTime = 15,
            double takeoffProbability = 0.8, 
            unsigned int landingTime = 5, 
            double landingProbability = 0.1, 
            unsigned int fuelLimit = 20, 
            unsigned int totalTime = 1440);

	bool Run();

private:
    void Step();
    void ProcessQueries();
    bool IsBusy() const;
    bool ProcessLandings();
    bool ProcessTakeoffs();
    void ProcessCooldowns();
    void PrintResult() const;

    unsigned int takeoffTime;      //how long it takes for a take off once plane 
                                    //    is on the runway 
    double takeoffProbability;     //probability of arrival of a plane into the 
                                    //    take off line 
    unsigned int landingTime;      //how long it takes for a plane to land on the 
                                    //    runway in each second
    double landingProbability;     //probability of arrival of planes for landing 
                                    //     in each second
    unsigned int fuelLimit;        //maximum amount of time a plan can stay in 
                                    //      landing queue without crashing
    unsigned int totalTime;        //total time you will run the simulation.
    unsigned int currentTime;
    unsigned int totalCrashes;
    unsigned int totalLanded;
    unsigned int totalTakeoffs;
    unsigned int landingCooldown;
    unsigned int takeoffCooldown;

    queue<unsigned int> landingQueue;
    queue<unsigned int> takeoffQueue;
    
    Averager takeoffTimeAverager;
    Averager landingTimeAverager;

    BooleanSource source;
};