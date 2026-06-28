// ThreadMutexMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
//1
//MUtex is Mutual exclusion, it is used to protect shared data from being simultaneously accessed by multiple threads.
// It is introduced in c++11. There is race condition when two or more thread can access shared data and they try to 
// change it at the same time. If they are not synchronized, then the thread scheduling algorithm can swap between the
// thread at any time and the result of the change can be dependent on the thread scheduling algo. // it can cause data 
// corruption and inconsistency. Mutex is used to lock the shared data when a thread is accessing it, so that other 
// threads cannot access it until the first thread is done.

//2
//mutex try_lock() - It is used to try to lock the mutex. If the mutex is already locked by another thread, it will return false.
//if try_lock is not able to lock mutex, then it doesn't get blocked. So it is non-blocking. 
// double try_lock is not allowed. If a thread tries to lock a mutex that it has already locked, it will result in undefined behavior.

//3
//There is also std::try_lock() function which can be used to lock multiple mutexes at once.
// It will try to lock all the mutexes and if it is not able to lock any of the mutex, it will unlock all the mutexes that 
// it has already locked and return false. If it is able to lock all the mutexes, it will return true.

//4
//Timed mutex is blocked till timeout. It is used to lock the mutex for specific time. It is introduced in C++14. It is used to 
// lock the mutex for specific time. try_lock_for() - It is used to try to lock the mutex for specific time. If the mutex is 
// already locked by another thread, it will return false after timeout.

int money = 0;
int counter(0);

void addMoney(int moneyAmt)
{
    money = moneyAmt;

    std::mutex mtx;
	mtx.lock();
    money++;
    mtx.unlock();
}

void increaseTheCounterFor100000Times()
{
	std::mutex mtx;
    for (int i = 0; i < 100000; i++)
    {
        if (mtx.try_lock())
        {
            counter++;
            mtx.unlock();
		}
    }
    return;
}


int X = 0, Y = 0;
std::mutex m1, m2;

void doSomeWorkForSeconds(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


void incrementXY(int& XorY, std::mutex& m, const char* desc)
{
    for (int i = 0; i < 5; ++i)
    {
		m.lock();
        ++XorY;
		std::cout << desc << " = " << XorY << std::endl;
        m.unlock();
        doSomeWorkForSeconds(1);
    }

    
    return;
}

void consumeXY()
{
    int useCount = 5;
	int XplusY = 0;

    while (true)
    {
        int lockResult = std::try_lock(m1, m2);
        if (lockResult == -1) {
            if (X != 0 && Y != 0) {
                --useCount;
                XplusY += X + Y;
                std::cout << "X + Y = " << XplusY << std::endl;
                X = 0;
                Y = 0;
            }
			m1.unlock();
            m2.unlock();
            if (useCount == 0)break;

        }
    }
}
//timed mutex code below
int iAmount = 2;
std::timed_mutex mtxTimed;

void increment(int ii)
{
	std::cout << "Thread " << ii << " is trying to acquire lock" << std::endl;
    if(mtxTimed.try_lock_for(std::chrono::seconds(2)))
    { 
        ++iAmount;
        std::this_thread::sleep_for(std::chrono::seconds(4));
		std::cout << "thread: " << ii << "amount " << iAmount << std::endl;
        mtxTimed.unlock();
    }
     else
    {
		std::cout << "thread " <<ii << " Could not acquire lock, iAmount: " << iAmount << std::endl;
    
    }


    return;
}

int main()
{
	// code for mutex lock and unlock
 /*   std::thread t1(addMoney, 100);
    std::thread t2(addMoney, 200);

	t1.join();
    t2.join();
    std::cout << "Money: " << money << std::endl;*/


	// code for mutex try_lock
	/*std::thread t3(increaseTheCounterFor100000Times);
	std::thread t4(increaseTheCounterFor100000Times);
	t3.join();
	t4.join();

    std::cout << "Counter : " << counter << std::endl;*/


	//code for std::try_lock()
    /*std::thread t5(incrementXY, std::ref(X), std::ref(m1), "X ");
    std::thread t6(incrementXY, std::ref(Y), std::ref(m2), "Y ");
	std::thread t7(consumeXY);*/

	//code for timed mutex
	std::thread t8(increment, 1);
	std::thread t9(increment, 2);
    
	t8.join();
	t9.join();

    //std::cout << "Hello World!\n";
    

}

