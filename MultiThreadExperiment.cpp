// MultiThreadExperiment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "JoinAttach.h"
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


//=== Functor class to be used for creating a thread
class Functor {
public:
	void operator()(int count1) {
		for(size_t i = 0; i< count1; i++)
		{
			std::cout << "Functor thread: " << i << std::endl;
		}
	}
};

class foo {

public:
	void runThread(int count2) {
		for (size_t i = 0; i < count2; i++)
		{
			std::cout << "Non-static member function thread: " << i << std::endl;
		}
	}

	static void staticFunction(int count3) {
		
		for(size_t ii = 0; ii< count3; ii++)
		{
			std::cout << "Static member function thread: " << ii << std::endl;
		}
		
	}
};

int main()
{
    
	
	std::cout << "Let's start multi-threading!\n";
	
	//=== Method 1 : Create a thread using function pointer and pass parameter to the thread function
	//std::thread worker2(threadFunction2, '/');
	//std::thread worker1(threadFunction1);
	//
	//
	//worker1.join();  // Wait for the second thread to finish
	//worker2.join();

	//===

	//=== Method 2 : Create a thread using lambda function and pass parameter to the thread function
	std::thread t([](int count) {
		for (int i = 0; i < count; ++i) {
			std::cout << "Lambda thread: " << i << std::endl;
		}
		}, 10);

	t.join();  // Wait for the lambda thread to finish
	//===

	//=== Method 3 : Create a thread using functor object and pass parameter to the thread function
	Functor functorObj;
	std::thread t2(functorObj, 15);
	t2.join();  // Wait for the functor thread to finish
	//===

	//=== Method 4 : Create a thread using a non-static member function of a class
		foo fooObj;
		std::thread t3(&foo::runThread, &fooObj, 11);
		t3.join();  // Wait for the non-static member function thread to finish
	//===
	//=== Method 5 : Create a thread using a static member function of a class
		std::thread t4(&foo::staticFunction, 12);
		t4.join();  // Wait for the static member function thread to finish
	//===

	//=== Run Join tutorial
	std::cout << "Running Join tutorial\n";
	std::thread t5(&JoinAttachClass::runThread, 20);	
	if(t5.joinable())
		t5.join();
	 
	//if (t5.joinable())
	//	t5.detach(); // Detach the thread if it is still joinable (not joined yet)

		// Wait for the thread to finish
	std::cout << "Join tutorial completed\n";
	return 0;
}
