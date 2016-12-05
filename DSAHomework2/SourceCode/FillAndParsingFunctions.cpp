#include <iostream>
#include <fstream>
#include "ElevatorRequest.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "DynArray.h"

using namespace std;


// Parsing the whole file with requests.

void fileParcing(ifstream &requestFileInput, Queue<ElevatorRequest> & allrequestsContainer, int &numberRequests)
{
	char temp[16];
	int index = 1;
	bool dir;

	while (index <= numberRequests)
	{
		dir = UP;
		if (requestFileInput.bad())
		{
			cerr << "Problem reading the the file at line: " << index << endl;
			throw "Problem parsing the file";
		}
		requestFileInput >> temp;
		if (requestFileInput.fail())
		{
			requestFileInput.clear();
			requestFileInput >> temp;
		}
		if (!strcmp(temp, "call"))
		{
			char direction[16];
			requestFileInput >> direction;
			if (!strcmp(direction, "down"))
				dir = DOWN;
			else if (strcmp(direction, "up")) // if it's not "down""or "up" there's a problem
			{
				cerr << "\nCan't recognise direction of request number: " << index << endl;
				throw "Problem parsing the file!!!";
			}
		}
		else if (strcmp(temp, "go")) // if it's not "call""or "go" it's a problem
		{
			cout << "\nCan't recognised request number: " << index << endl;
			throw "Problem parsing the file!!!";
		}
		int requestFloor;
		double requestTime;
		requestFileInput >> requestFloor;
		requestFileInput >> requestTime;
		ElevatorRequest newRequest(requestFloor, requestTime, dir, true);
		allrequestsContainer.push(newRequest);
		++index;
	}
}

void fillFirstRequest(ElevatorRequest & firstRequest, double  & currentSimulationTime, int  & lastExecutedFloor)
{
	double waitingTime = 0;
	if (firstRequest.getTime() > currentSimulationTime)
		waitingTime = firstRequest.getTime() - currentSimulationTime;	// There can be a period when the elevator is not moving and
	// it's waiting requests
	double firstRequestExecutionTime = currentSimulationTime + waitingTime
		+ abs(lastExecutedFloor - firstRequest.getFloor())*TIME_FOR_ONE_FLOOR;

	bool dir = (firstRequest.getFloor() - lastExecutedFloor) > 0 ? dir = UP : dir = DOWN;

	firstRequest.setDir(dir);
	firstRequest.setExecutionTime(firstRequestExecutionTime);
	currentSimulationTime += waitingTime; // To be correct we shoud count the waiting time
}


void fillParticialContainer(Queue<ElevatorRequest> & allrequestsContainer, Queue<ElevatorRequest> & particialRequestsContainer,
	 int & lastExecutedFloor, double & currSimulationTime, bool firstTime = false)
{
	// The first request is the one that define which requests will be pushed in partial Request container
	ElevatorRequest firstRequest;
	if (firstTime == true || particialRequestsContainer.isEmpty())
	{
		firstRequest = allrequestsContainer.front();
		allrequestsContainer.pop();
		fillFirstRequest(firstRequest, currSimulationTime, lastExecutedFloor);
		particialRequestsContainer.push(firstRequest);
	}
	else
	{
		fillFirstRequest(particialRequestsContainer.front(), currSimulationTime, lastExecutedFloor);
		firstRequest = particialRequestsContainer.front();
	}

	while (!allrequestsContainer.isEmpty())
	{
		ElevatorRequest currentRequest = allrequestsContainer.front();
		if (firstRequest.getExecutionTime() >= currentRequest.getTime())
		{
			particialRequestsContainer.push(currentRequest);
			allrequestsContainer.pop();
		}
		else
			break;
	}

}

