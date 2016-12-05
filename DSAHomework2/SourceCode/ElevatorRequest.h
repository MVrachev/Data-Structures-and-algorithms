#ifndef _ELEVATOR_REQUEST_HEADER

#define _ELEVATOR_REQUEST_HEADER

#include <iostream>
#include <fstream>
using namespace std;

enum DIRECTIONS
{
	DOWN = 0,
	UP
};

const int TIME_FOR_ONE_FLOOR = 5;

class ElevatorRequest
{
	bool m_direction;
	int m_floor;
	double m_time;
	double m_executionTime; // Time to execute from the beginning of the simulation 
public:

	ElevatorRequest() : m_direction(UP), m_floor(2), m_time(1){}

	ElevatorRequest(int newFloor, double newTime, bool newDirection = UP, bool typeRequest = true, double newExecutionTime = 0) :
		m_floor(newFloor), m_time(newTime), m_direction(newDirection), m_executionTime(newExecutionTime){}

	~ElevatorRequest(){}

	const double & getTime() { return m_time; }
	const int & getFloor() const { return m_floor; }
	const bool & getDir() { return m_direction; }
	const double & getExecutionTime() { return m_executionTime; }

	void setDir(bool newDir) { m_direction = newDir; }
	void setExecutionTime(double newExecutionTime){ m_executionTime = newExecutionTime; }
	void setFloor(int newFloor) { m_floor = newFloor; }
	void setTime(double newTime) { m_time = newTime; }

	friend ostream & operator<<(ostream &out, const ElevatorRequest & right)
	{
		out << right.m_executionTime << " " << right.m_floor << " ";
		if (right.m_direction == UP)
			out << "up\n";
		else if (right.m_direction == DOWN)
			out << "down\n";
		return out;
	}

};


#endif // !_ELEVATOR_REQUEST_HEADER
