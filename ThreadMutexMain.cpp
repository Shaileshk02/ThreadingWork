// ThreadMutexMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>

//MUtex is Mutual exclusion, it is used to protect shared data from being simultaneously accessed by multiple threads.
// It is introduced in c++11. There is race condition when two or more thread can access shared data and they try to 
// change it at the same time. If they are not synchronized, then the thread scheduling algorithm can swap between the
// thread at any time and the result of the change can be dependent on the thread scheduling algo. // it can cause data 
// corruption and inconsistency. Mutex is used to lock the shared data when a thread is accessing it, so that other 
// threads cannot access it until the first thread is done.

int money = 0;
void addMoney(int moneyAmt)
{
    money = moneyAmt;

    std::mutex mtx;
	mtx.lock();
    money++;
    mtx.unlock();
}

int main()
{
    std::thread t1(addMoney, 100);
    std::thread t2(addMoney, 200);

	t1.join();
    t2.join();
    
	std::cout << "Money: " << money << std::endl;
    std::cout << "Hello World!\n";
}

