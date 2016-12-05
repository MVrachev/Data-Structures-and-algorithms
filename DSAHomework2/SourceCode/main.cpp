#include<iostream>
#include <fstream>
#include "ElevatorRequest.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "DynArray.h"

using namespace std;


/**
*
* Solution to homework number 2
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Martin Vrachev
* @idnumber 45197
* @task 1
* @compiler Visual Studio 2013
*
*/


void fillParticialContainer(Queue<ElevatorRequest> & allrequestsContainer, Queue<ElevatorRequest> & particialRequestsContainer,
	 int & lastExecutedFloor, double & currSimulationTime, bool firstTime = false);

void fileParcing(ifstream &requestFileInput, Queue<ElevatorRequest> & allrequestsContainer, int &numberRequests);

void allRequestExecution(Queue<ElevatorRequest> & currentRequestsContainer, Queue<ElevatorRequest> & allrequestsContainer,
	double  & currentSimulationTime, int &lastExecutedFloor, bool  & firstPartFile, int & numberRequests);




int main(int argc, char * argv[])
{
	try
	{
		// Testing the DoublyLinkedList
		/*
		DoublyLinkedList<int> temp;
		temp.addAtEnd(5);
		//temp.print();
		temp.addAtEnd(10);
		temp.addAtEnd(14);
		temp.addAtEnd(20);
		temp.removeFirstElem();
		temp.removeFirstElem();
		temp.removeFirstElem();
		temp.print();
		DoublyLinkedList<int> temp2 = temp;
		//DoublyLinkedList<int> temp2(temp);
		temp2.print();
		temp2.addAtEnd(10);
		temp2.addAtEnd(14);
		temp2.print();

		DoublyLinkedList<int> temp;
		const int count = 1 << 15;
		//const int count = 1;
		for (int c = 0; c < count; ++c) {
		temp.addAtEnd(rand());
		}

		for (int c = 0; c < count; ++c) {
		temp.removeFirstElem();
		}

		DoublyLinkedList<int> temp;
		temp.addAtEnd(10);
		temp.addAtEnd(20);
		DoublyLinkedList<int>temp2(temp);
		temp.clear();
		temp2.print();
		*/

		// Testing the Queue
		/*
		Queue<int> temp;
		temp.push(10);
		temp.push(20);
		temp.push(30);
		temp.push(40);
		temp.print();
		temp.pop();
		temp.pop();
		temp.print();
		*/

	

		Queue<ElevatorRequest> allrequestsContainer;
		//Queue<ElevatorRequest> requestsFutureExecute;
		double currentSimulationTime = 0;
		int lastExecutedFloor = 1;
		ifstream requestFileInput(argv[1], ios::in);
		int numberFloors;
		int numberRequests;
		requestFileInput >> numberFloors;
		requestFileInput >> numberRequests;
		cout << numberRequests << " " << numberFloors << endl;
		Queue<ElevatorRequest>  particialRequestsContainer;



		bool firstPartFile = true;
		cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

		fileParcing(requestFileInput, allrequestsContainer, numberRequests);
		//allrequestsContainer.print();
		cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		particialRequestsContainer.print();
		cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		
		while (numberRequests !=0)
		{
			fillParticialContainer(allrequestsContainer, particialRequestsContainer,
			lastExecutedFloor, currentSimulationTime);

			allRequestExecution(particialRequestsContainer, allrequestsContainer, currentSimulationTime, lastExecutedFloor, firstPartFile, numberRequests);
			
		}

		requestFileInput.close();

	}
	catch (const char * problem)
	{
		cout << problem << endl;
	}
	catch (const bad_alloc & problem)
	{
		cout << problem.what() << endl;
	}


	return 0;
}
