// MultiThreadExperiment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
// Read me:
// In this a thread is created using function pointer and the thread is 
// executed by calling the function in the thread. The main thread waits 
// for the worker thread to finish before exiting. Also parameter is passed
// to the thread function.
void threadFunction1() {
    
	for (size_t i = 0; i < 2000; i++)
	{
		std::cout << "999";
	}
	return;
}


void threadFunction2(char symbol) {

	for (size_t i = 0; i < 2000; i++)
	{
		std::cout << symbol;
	}
	return;
}


int main()
{
    std::cout << "Let's start multi-threading!\n";
	std::thread worker2(threadFunction2, '/');
	std::thread worker1(threadFunction1);
	
	
	worker1.join();  // Wait for the second thread to finish
	worker2.join();

	return 0;
}
