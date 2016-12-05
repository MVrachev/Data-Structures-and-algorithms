#include<iostream>
#include <fstream>
#include "ElevatorRequest.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "DynArray.h"

using namespace std;

void fillParticialContainer(Queue<ElevatorRequest> & allrequestsContainer, Queue<ElevatorRequest> & particialRequestsContainer,
	 int & lastExecutedFloor, double & currSimulationTime, bool firstTime = false);

void fillFirstRequest(ElevatorRequest & firstRequest, double  & currentSimulationTime,  int  & lastExecutedFloor);


void bubleSort(DynArray<ElevatorRequest> & requestsToExecute)
{
	int size = requestsToExecute.getSize();
	bool sorted = true;
	for (int i = 0; i < size - 1; ++i)
	{
		sorted = true;
		for (int j = 0; j < size - 1; ++j)
		{
			ElevatorRequest temp = requestsToExecute[i];
			if (requestsToExecute[j].getExecutionTime() > requestsToExecute[j + 1].getExecutionTime())
			{
				ElevatorRequest temp = requestsToExecute[j];
				requestsToExecute[j] = requestsToExecute[j + 1];
				requestsToExecute[j + 1] = temp;
				sorted = false;
			}
		}
		if (sorted == true)
			break;
	}

}



double countExecutionTime(ElevatorRequest & firstRequest, ElevatorRequest & currRequest,
		double currentSimulationTime, int lastExecutedFloor, const bool & currentDir)
{
	double TimeWhenElevatorWillBeOnCurrentFloor = -1;
	if (firstRequest.getFloor() < currRequest.getFloor() && firstRequest.getDir() == DOWN && currentDir == DOWN
		|| firstRequest.getFloor() > currRequest.getFloor() && firstRequest.getDir() == UP && currentDir == UP)
	{
		TimeWhenElevatorWillBeOnCurrentFloor = currentSimulationTime + abs(lastExecutedFloor - currRequest.getFloor()) *TIME_FOR_ONE_FLOOR;
	}
	return TimeWhenElevatorWillBeOnCurrentFloor;
}

// Function that tests if our current request is already in execution stack

bool alreadyInExecutingStack(const DynArray<ElevatorRequest> & requestsToExecute, int currentFloor)
{
	bool inStack = false;
	int size = requestsToExecute.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (currentFloor == requestsToExecute[i].getFloor())
			inStack = true;
	}

	return inStack;
}


// Returns the queue for future execution
// In the new Queue I will push all others requests I can't execute while
// moving to the desired floor from the first request in currentRequestsContainer

Queue<ElevatorRequest> & partialRequestExecution(Queue<ElevatorRequest> & currentRequestsContainer,
	Queue<ElevatorRequest> & requestsFutureExecute, double  & currentSimulationTime, int  & lastExecutedFloor, int & numberRequests,
	bool firstTimeThisFunction = false)
{
	ElevatorRequest firstRequest = currentRequestsContainer.front(); // An important request. This is the request 
	currentRequestsContainer.pop();									// that defines which request will be executed now or in the future
	--numberRequests;
	bool dir;

	int indexToExecute = 0;
	DynArray<ElevatorRequest> requestsToExecute; 
	requestsToExecute.addAtEnd(firstRequest);
	double TimeWhenElevatorWillBeOnCurrentFloor;
	while (!currentRequestsContainer.isEmpty())
	{
		ElevatorRequest currRequest = currentRequestsContainer.front();
		currentRequestsContainer.pop();

		// I must check if there's is not other for executing request for the same floor
		// because if there is our elevator will executed. We want unique requests for our execution Stack
		if (firstRequest.getFloor() == currRequest.getFloor() &&
			firstRequest.getExecutionTime() >= currRequest.getExecutionTime()) 									
		{
			--numberRequests;
			continue;
		}

		bool currentDir = (currRequest.getFloor() - lastExecutedFloor) > 0 ? dir = UP : dir = DOWN;
		currRequest.setDir(currentDir);
		TimeWhenElevatorWillBeOnCurrentFloor = countExecutionTime(firstRequest, currRequest, currentSimulationTime, lastExecutedFloor, dir);

		if (TimeWhenElevatorWillBeOnCurrentFloor == -1)
		{
			requestsFutureExecute.push(currRequest);
			continue;
		}
		if (currRequest.getTime() < TimeWhenElevatorWillBeOnCurrentFloor) // that way we check if the elevator at the time of the request 
		{																 // has missed the desired floor

			// I will count the direction of the request when I will know it will be executed not before then
			bool dir = (firstRequest.getFloor() - currRequest.getFloor()) > 0 ? dir = UP : dir = DOWN;

			currRequest.setExecutionTime(TimeWhenElevatorWillBeOnCurrentFloor);
			currRequest.setDir(dir);

			//That insures that if the order in the execution stack is wrong it will be reordered
			// so the request will be executed correctly in the time;
			if (alreadyInExecutingStack(requestsToExecute, currRequest.getFloor()) == true)
			{
				--numberRequests;
				continue;
			}
			requestsToExecute.addAtEnd(currRequest);
			--numberRequests;
			
		}
		else
			requestsFutureExecute.push(currRequest);
	}

	// We need sort because in the end we don't know what is the request order by execution time in the executin array 
	bubleSort(requestsToExecute);

	requestsToExecute.print();
	lastExecutedFloor = firstRequest.getFloor(); // I need to remember the last executed floor
	currentRequestsContainer.clear();
	currentSimulationTime = firstRequest.getExecutionTime();
	return requestsFutureExecute;
}


// In this function I execute what I can execute while my elevator is on his way for the first request
// because there can be others not executed because they were not on the way of the first request I repeat the process

void allRequestExecution(Queue<ElevatorRequest> & currentRequestsContainer, Queue<ElevatorRequest> & allrequestsContainer,
	double  & currentSimulationTime, int &lastExecutedFloor, bool  & firstPartFile, int & numberRequests)
{
	Queue<ElevatorRequest> futureExecutions;

	// I must rotate the containers in order for my algorithm to work.
	bool firstRequestExecution = true;
	int rotate = 0;
	while (true)
	{

		if (rotate % 2 == 0)
		{
			futureExecutions = partialRequestExecution(currentRequestsContainer, futureExecutions,
				currentSimulationTime, lastExecutedFloor, numberRequests, firstRequestExecution);
			if (firstPartFile == true)
			{
				if (firstRequestExecution == true)
					firstRequestExecution = false;
			}
			if (futureExecutions.isEmpty())
				break;
			fillParticialContainer(allrequestsContainer, futureExecutions, lastExecutedFloor, currentSimulationTime);
			++rotate;
		}
		else if (rotate % 2 == 1)
		{
			currentRequestsContainer = partialRequestExecution(futureExecutions, currentRequestsContainer,
				currentSimulationTime, lastExecutedFloor, numberRequests);
			if (currentRequestsContainer.isEmpty())
				break;
			fillParticialContainer(allrequestsContainer, currentRequestsContainer, lastExecutedFloor, currentSimulationTime);
			++rotate;
		}
	}
}