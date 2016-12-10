# Smart elevator simulation

This is consonle application which is my second homework from the university course "Data Structures and algorithms" in St. Kliment Ohridski university of Sofia. The data structures I used are Vector (or here Dynamic Array), Double linked list and Queue which is implemented by the Linked list. It is started on 24.11.2016 and finished by the date of 05.12.2016.

There is a building with N floors and in the building there's an elevator who is used through the building. The requests for the elevator (a request is a call outside the elevator or inside the elevator for certain floor) are executed in the order they are requested. The speed of the elevator is a constant and it's a 0.2 floors per second (or one floor for 5 seconds). The time the elevator stays is on certain floor is 0 seconds.

Your program should simulate the work of the elevator and execute all his requests and calls.

The input data will be in text file, the name of which you will recive as a command line arguments of your program. The first row if the input will have two whole positive numbers N and K. N stands for number of the floors in the building and K is for the number of requests which will be executed. Every request is on different row. There are two types of requests:

Call from certain floor (outside the elevator):
*call DIR FLOOR TIME*
- DIR: direction, one direction from up or down.
- FLOOR: floor, a whole number from the interval [1,N]
- TIME: time in seconds from the begining of the simulation when the request is given

A command, request from inside the elevator:
*go FLOOR TIME*
- FLOOR: floor, a whole number from the interval [1,N]
- TIME: time in seconds from the begining of the simulation when the request is given

Output of your program shoud be: TIME, FLOOR, DIR and for every stop on a floor of the elevator, where
- TIME: time in seconds from the begining of the simulation when the request is executed
- FLOOR: the floor on which the elevator has stopped.
- DIR: the direction from which the elevator had come on this floor.

**Note 1:**
The seconds of the requests doesn't have anything in common with the time of execution of your program. You can think of the requests as already completed events. In second 0 the elevator is on floor 1.

**Note 2:** 
The requests are executed sorted by the time they are given. The only exception of this rule is when the elevator can stop on certain floor without chaging the requests he is executing.
An example: if the elevator is moving from floor 1 towards floor 5 and a new request is given while he is on floor 2 the elevator will stop on floor 4 and then he will stop on floor 5.


