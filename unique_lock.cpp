// unique_lock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//3. unique_lock:
// unique_lock is mutex wrapper. 
// It can have different locking strategis. 
// It allows time constrained attempt at locking like try_lock_for or try_lock_until. 
// It allows recursive locking
// It allows transfer of lock ownership but not copy.
// It allows condition variable
// Locking strategies are : 
// defer_lock - do not acquire ownership of the mutex
// try_to_lock -  try to acquree ownership of the mutex without blocking.
// adopt_lock -  assume the calling thread already has ownership of the mutex


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


//int buffer(0);
//mutex m1;
//void taskNormal(const char* threadName, int loopFor)
//{
//    std::unique_lock <mutex> lock(m1); //It locks and unlock theread normally
//
//    for (size_t i = 0; i < loopFor; i++)
//    {
//        buffer++;
//        cout << threadName << ": " << buffer << endl; 
//    }
//
//
//    return;
//}
//
//int main()
//{
//    
//    thread t1(taskNormal, "T1", 5);
//    thread t2(taskNormal, "T2", 2);
//
//    t1.join();
//    t2.join();
//
//    std::cout << "Hello World!\n";
//
//    return 0;
//}



// === == Unique lock with defer below == ===

//std::defer_lock constructs a unique_lock without locking the mutex.This is useful when multiple
// mutexes need to be locked together using std::lock(), which acquires them in a deadlock - free manner.
//
//Example:
//
//std::unique_lock<std::mutex> l1(m1, std::defer_lock);
//std::unique_lock<std::mutex> l2(m2, std::defer_lock);
//
//std::lock(l1, l2);
//
//This is the classic multithreading interview example for preventing deadlocks when multiple mutexes are involved.

//What happens without defer_lock
//
//Imagine two mutexes :
//
//std::mutex m1;
//std::mutex m2;
//
//Thread 1:
//
//m1.lock();
//m2.lock();
//
//Thread 2:
//
//m2.lock();
//m1.lock();
//What can happen ?
//
//Thread 1 locks m1.
//
//Thread 2 locks m2.
//
//Now :
//
//	Thread 1 waiting for m2
//	Thread 2 waiting for m1
//
//	Both wait forever.
//
//	This is called a deadlock.
//
//	Solution: std::lock
//
//	C++ provides :
//
//	std::lock(m1, m2);
//
//which locks both mutexes safely without deadlock.
//
//But std::lock expects mutexes or lock objects that are not already locked.
//
//Using unique_lock + defer_lock
//std::unique_lock<std::mutex> lock1(m1, std::defer_lock);
//std::unique_lock<std::mutex> lock2(m2, std::defer_lock);
//
//At this point:
//
//lock1 owns m1 ? No
//lock2 owns m2 ? No
//
//Nothing is locked yet.
//
//Now :
//
//	std::lock(lock1, lock2);
//
//C++ locks both mutexes in a deadlock - safe manner.
//
//After this:
//
//lock1 owns m1
//lock2 owns m2
//Complete Example
//#include <iostream>
//#include <mutex>
//
//std::mutex m1;
//std::mutex m2;
//
//void work()
//{
//	std::unique_lock<std::mutex> lock1(m1, std::defer_lock);
//	std::unique_lock<std::mutex> lock2(m2, std::defer_lock);
//
//	std::lock(lock1, lock2);
//
//	std::cout << "Both mutexes locked safely\n";
//}
//
//int main()
//{
//	work();
//}
//Why Not Use lock_guard ?
//
//This won't work:
//
//std::lock_guard<std::mutex> g1(m1);
//std::lock_guard<std::mutex> g2(m2);
//
//because:
//
//They lock immediately.
//You cannot pass them to std::lock.
//No deferred locking support.
//
//That's why unique_lock exists.

mutex m1;
void printNumbers(const char* ch)
{
	std::unique_lock<mutex> lock(m1, std::defer_lock);
	cout << " do work befor lock " << ch << endl;

	lock.lock(); // Notice here you ve to explicitly lock

	for (size_t i = 0; i < 10; i++)
	{
		cout << i << endl;
	}
	//std::cout << "critical section" << endl;

	//lock.unlock(); // not needed.

	cout << "after lock " << endl;


	return;
}

int main()
{
	thread t1(printNumbers, "T1");
	thread t2(printNumbers, "T2");

	t1.join();
	t2.join();

	return 0;
}