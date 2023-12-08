#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  //check travel direction (n,s,e,w)

  int eventType;
  int eventTime;

  if (travelDir == EAST_DIRECTION)
  {
    eventTime = currentTime + getPositiveNormal(eastArrivalMean, 
                                                eastArrivalStdDev);
    eventType = EVENT_ARRIVE_EAST;
  }
  else if (travelDir == WEST_DIRECTION)
  {
    eventTime = currentTime + getPositiveNormal(westArrivalMean, 
                                                westArrivalStdDev);
    eventType = EVENT_ARRIVE_WEST;
  }
  else if (travelDir == NORTH_DIRECTION)
  {
    eventTime = currentTime + getPositiveNormal(northArrivalMean, 
                                                northArrivalStdDev);
    eventType = EVENT_ARRIVE_NORTH;
  }
  else if (travelDir == SOUTH_DIRECTION)
  {
    eventTime = currentTime + getPositiveNormal(southArrivalMean, 
                                                southArrivalStdDev);
    eventType = EVENT_ARRIVE_SOUTH;
  }
  //wasn't one of valid directions?
  else
  {
    cout << "error detected: not valid direction" << endl;
  }

  //add event to the sortedlistclass

  EventClass arrivalEvent(eventTime, eventType);
  eventList.insertValue(arrivalEvent);
  cout << "Time: " << currentTime << " Scheduled ";
  cout << arrivalEvent << endl;
  //print?


}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
  int schedChangeTime;
  int schedChangeType;

  if (currentLight == LIGHT_GREEN_EW)
  {
    schedChangeTime = currentTime + eastWestGreenTime;
    schedChangeType = EVENT_CHANGE_YELLOW_EW;
  }
  else if (currentLight == LIGHT_YELLOW_EW)
  {
    schedChangeTime = currentTime + eastWestYellowTime;
    schedChangeType = EVENT_CHANGE_GREEN_NS;
  }
  else if (currentLight == LIGHT_GREEN_NS)
  {
    schedChangeTime = currentTime + northSouthGreenTime;
    schedChangeType = EVENT_CHANGE_YELLOW_NS;
  }
  else if (currentLight == LIGHT_YELLOW_NS)
  {
    schedChangeTime = currentTime + northSouthYellowTime;
    schedChangeType = EVENT_CHANGE_GREEN_EW;
  }

  EventClass lightChangeEvent(schedChangeTime, schedChangeType);
  eventList.insertValue(lightChangeEvent);
  //print?
  cout << "Time: " << currentTime << " Scheduled ";
  cout << lightChangeEvent << endl;

}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  EventClass eventToHandle;
  bool doHandleThisEvent = true;

  if (eventList.removeFront(eventToHandle))
  {
    //check that we haven't exceeded time yet

    if (eventToHandle.getTimeOccurs() <= this->timeToStopSim)
    {
      //print?
      cout << endl << "Handling ";
    }
    else
    {
      cout << endl << "Next event occurs AFTER the simulation end time ("
           << eventToHandle << ")!" << endl;
      doHandleThisEvent = false;
    }
  }
  else
  {
    cout << "error happened somehow, there were no events";
    doHandleThisEvent = false;
  }

  if (doHandleThisEvent)
  {
    cout << eventToHandle << endl;
    
    int handleType = eventToHandle.getType();
    this->currentTime = eventToHandle.getTimeOccurs();

    if (handleType == EVENT_ARRIVE_EAST)
    {
      CarClass newCar(EAST_DIRECTION, currentTime);
      eastQueue.enqueue(newCar);

      int queueLength = eastQueue.getNumElems();

      //check if it's the max queue length and update if so
      if (queueLength > maxEastQueueLength)
      {
        maxEastQueueLength = queueLength;
      }
      //print?
      cout << "Time: " << currentTime << " ";
      cout << newCar << " - queue length: " << queueLength << endl;
      scheduleArrival(EAST_DIRECTION);
    }

    else if (handleType == EVENT_ARRIVE_WEST)
    {
      CarClass newCar(WEST_DIRECTION, currentTime);
      westQueue.enqueue(newCar);

      int queueLength = westQueue.getNumElems();

      //check if it's the max queue length and update if so
      if (queueLength > maxWestQueueLength)
      {
        maxWestQueueLength = queueLength;
      }
      //print?
      cout << "Time: " << currentTime << " ";
      cout << newCar << " - queue length: " << queueLength << endl;
      scheduleArrival(WEST_DIRECTION);
    }

    else if (handleType == EVENT_ARRIVE_NORTH)
    {
      CarClass newCar(NORTH_DIRECTION, currentTime);
      northQueue.enqueue(newCar);

      int queueLength = northQueue.getNumElems();

      //check if it's the max queue length and update if so
      if (queueLength > maxNorthQueueLength)
      {
        maxNorthQueueLength = queueLength;
      }
      //print?
      cout << "Time: " << currentTime << " ";
      cout << newCar << " - queue length: " << queueLength << endl;
      scheduleArrival(NORTH_DIRECTION);
    }

    else if (handleType == EVENT_ARRIVE_SOUTH)
    {
      CarClass newCar(SOUTH_DIRECTION, currentTime);
      southQueue.enqueue(newCar);

      int queueLength = southQueue.getNumElems();

      //check if it's the max queue length and update if so
      if (queueLength > maxSouthQueueLength)
      {
        maxSouthQueueLength = queueLength;
      }
      //print?
      cout << "Time: " << currentTime << " ";
      cout << newCar << " - queue length: " << queueLength << endl;
      scheduleArrival(SOUTH_DIRECTION);
    }

    //light is changing

    else if (handleType == EVENT_CHANGE_GREEN_EW || 
             handleType == EVENT_CHANGE_GREEN_NS || 
             handleType == EVENT_CHANGE_YELLOW_EW || 
             handleType == EVENT_CHANGE_YELLOW_NS)
    {
      if (currentLight == LIGHT_GREEN_EW)
      {
        int totalCarsCouldPass = eastWestGreenTime;
        cout << "Advancing cars on east-west green" << endl;

        CarClass passingCar;
        
        int numCarsGoneEast = 0;
        while (numCarsGoneEast < totalCarsCouldPass && 
               eastQueue.dequeue(passingCar))
        {
          cout << "  Car #" << passingCar.getId() 
               << " advances east-bound" << endl;
          numCarsGoneEast++;
          numTotalAdvancedEast++;
        }
        //ALSO DO FOR GOING WEST!!
        int numCarsGoneWest = 0;
        while (numCarsGoneWest < totalCarsCouldPass && 
               westQueue.dequeue(passingCar))
        {
          cout << "  Car #" << passingCar.getId() 
               << " advances west-bound" << endl;
          numCarsGoneWest++;
          numTotalAdvancedWest++;
        }

        //print statements
        cout << "East-bound cars advanced on green: "
             << numCarsGoneEast 
             << " Remaining queue: " << eastQueue.getNumElems() << endl;
        cout << "West-bound cars advanced on green: "
             << numCarsGoneWest 
             << " Remaining queue: " << westQueue.getNumElems() << endl;
      }

      else if (currentLight == LIGHT_GREEN_NS)
      {
        int totalCarsCouldPass = northSouthGreenTime;
        cout << "Advancing cars on north-south green" << endl;

        CarClass passingCar;

        int numCarsGoneNorth = 0;
        while (numCarsGoneNorth < totalCarsCouldPass && 
               northQueue.dequeue(passingCar))
        {
          cout << "  Car #" << passingCar.getId() 
               << " advances north-bound" << endl;
          numCarsGoneNorth++;
          numTotalAdvancedNorth++;
        }
        //ALSO DO FOR GOING SOUTH!!
        int numCarsGoneSouth = 0;
        while (numCarsGoneSouth < totalCarsCouldPass && 
               southQueue.dequeue(passingCar))
        {
          cout << "  Car #" << passingCar.getId() 
               << " advances south-bound" << endl;
          numCarsGoneSouth++;
          numTotalAdvancedSouth++;
        }

        //print statements
        cout << "North-bound cars advanced on green: "
             << numCarsGoneNorth 
             << " Remaining queue: " << northQueue.getNumElems() << endl;
        cout << "South-bound cars advanced on green: "
             << numCarsGoneSouth 
             << " Remaining queue: " << southQueue.getNumElems() << endl;
      }


      //YELLOW LIGHTS
      else if (currentLight == LIGHT_YELLOW_NS)
      {
        cout << "Advancing cars on north-south yellow" << endl;

        int totalCarsCouldPass = northSouthYellowTime;

        bool keepAdvancing = true;
        bool doesNextAdvance;

        int numCarsGoneNorth = 0;
        int numCarsGoneSouth = 0;
        CarClass advancingCar;

        while (keepAdvancing)
        {
          if (numCarsGoneNorth < totalCarsCouldPass && 
              northQueue.getNumElems() > 0)
          {
            int random_chance = getUniform(1, 100);
            doesNextAdvance = random_chance < percentCarsAdvanceOnYellow;

            if (doesNextAdvance)
            {
              cout << "  Next north-bound cars will advance on yellow" << endl;
              northQueue.dequeue(advancingCar);
              cout << "  Car #" << advancingCar.getId() 
               << " advances north-bound" << endl;
              //print
              numCarsGoneNorth++;
              numTotalAdvancedNorth++;
            }
            else
            {
              cout << "  Next north-bound car will NOT advance on yellow" 
                   << endl;
              keepAdvancing = false;
            }
          }
          else
          {
            cout << "  No north-bound cars waiting to advance on yellow" 
                 << endl;
            keepAdvancing = false;
          }
        }

        keepAdvancing = true;
        while (keepAdvancing)
        {
          if (numCarsGoneSouth < totalCarsCouldPass && 
              southQueue.getNumElems() > 0)
          {
            int random_chance = getUniform(1, 100);
            doesNextAdvance = random_chance < percentCarsAdvanceOnYellow;
  
            if (doesNextAdvance)
            {
              cout << "  Next south-bound cars will advance on yellow" << endl;
              //print
              southQueue.dequeue(advancingCar);
              cout << "  Car #" << advancingCar.getId() 
               << " advances south-bound" << endl;
              numCarsGoneSouth++;
              numTotalAdvancedSouth++;
            }
            else
            {
              cout << "  Next south-bound car will NOT advance on yellow" 
                   << endl;
              keepAdvancing = false;
            }
          }
          else
          {
            cout << "  No south-bound cars waiting to advance on yellow" 
                 << endl;
            keepAdvancing = false;
          }
        }
          

        cout << "North-bound cars advanced on yellow: "
             << numCarsGoneNorth 
             << " Remaining queue: " << northQueue.getNumElems() << endl;
        cout << "South-bound cars advanced on yellow: "
             << numCarsGoneSouth 
             << " Remaining queue: " << southQueue.getNumElems() << endl;
      }

      else if (currentLight == LIGHT_YELLOW_EW)
      {
        cout << "Advancing cars on east-west yellow" << endl;

        int totalCarsCouldPass = eastWestYellowTime;

        bool keepAdvancing = true;
        bool doesNextAdvance;

        int numCarsGoneEast = 0;
        int numCarsGoneWest = 0;
        CarClass advancingCar;

        while (keepAdvancing)
        {
          if (numCarsGoneEast < totalCarsCouldPass && 
              eastQueue.getNumElems() > 0)
          {
            int random_chance = getUniform(1, 100);
            doesNextAdvance = random_chance < percentCarsAdvanceOnYellow;

            if (doesNextAdvance)
            {
              cout << "  Next east-bound cars will advance on yellow" << endl;
              //print
              eastQueue.dequeue(advancingCar);
              cout << "  Car #" << advancingCar.getId() 
               << " advances east-bound" << endl;
              numCarsGoneEast++;
              numTotalAdvancedEast++;
            }
            else
            {
              cout << "  Next east-bound car will NOT advance on yellow" 
                   << endl;
              keepAdvancing = false;
            }
          }
          else
          {
            cout << "  No east-bound cars waiting to advance on yellow" 
                 << endl;
            keepAdvancing = false;
          }
          
        }

        keepAdvancing = true;
        while (keepAdvancing)
        {
          if (numCarsGoneWest < totalCarsCouldPass && 
              westQueue.getNumElems() > 0)
          {
            int random_chance = getUniform(1, 100);
            doesNextAdvance = random_chance < percentCarsAdvanceOnYellow;

            if (doesNextAdvance)
            {
              cout << "  Next west-bound cars will advance on yellow" << endl;
              //print
              westQueue.dequeue(advancingCar);
              cout << "  Car #" << advancingCar.getId() 
               << " advances west-bound" << endl;
              numCarsGoneWest++;
              numTotalAdvancedWest++;
            }
            else
            {
              cout << "  Next west-bound car will NOT advance on yellow" 
                   << endl;
              keepAdvancing = false;
            }
          }
          else
          {
            cout << "  No west-bound cars waiting to advance on yellow" 
                 << endl;
            keepAdvancing = false;
          }
        }
        

        cout << "East-bound cars advanced on yellow: "
             << numCarsGoneEast 
             << " Remaining queue: " << eastQueue.getNumElems() << endl;
        cout << "West-bound cars advanced on yellow: "
             << numCarsGoneWest 
             << " Remaining queue: " << westQueue.getNumElems() << endl;
      }
      
      if (handleType == EVENT_CHANGE_GREEN_EW)
      {
        currentLight = LIGHT_GREEN_EW;
      }
      if (handleType == EVENT_CHANGE_GREEN_NS)
      {
        currentLight = LIGHT_GREEN_NS;
      }
      if (handleType == EVENT_CHANGE_YELLOW_EW)
      {
        currentLight = LIGHT_YELLOW_EW;
      }
      if (handleType == EVENT_CHANGE_YELLOW_NS)
      {
        currentLight = LIGHT_YELLOW_NS;
      }
      //etc....

      scheduleLightChange();
    }
  }
  return doHandleThisEvent;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
