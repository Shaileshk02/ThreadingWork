// MutexWork2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//1. recursive_mutex.
///1. It is same as mutex, but, same thread can multiple times using recursive_mutex. It is used in recursive function calls.
// If thread T1 first call lock/try_lock on recursive_mutex m1, then m1 is locked by T1. Now as T1 is running in recursion, T1 can
//call lock/try_lock any number of times without issue.
//2. But if T1 have acquired 10 times lock/try_lock on m1 then thread T1 have to unlock it 10 times in else no other thread will be
// able to lock the mutex m1. Means, mutex has to remember how many times it is locked and needs to be unlocked same numbe of times.
//3. If we can avoid recursive mutex then it should because it adds overhead.
// Recursion works on stack.
//


//2. lock_guard : 
//It is light weight wrapper for owining mutex on scoped basis. // It aquires mutex lock the moment you create object of lock_guard.
//3. It automatically removs thje lock when goes out of scope. //4. You canot explicitly unlock the lock guard. it cannot be copied.



#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex m1;

void recursiveMutex(int recursionCount, int threadNumber)
{
    std::cout << "Lock the theread" << threadNumber << " resCount " << recursionCount << std::endl;
    if (recursionCount < 0)
        return;
    
    m1.lock();
    recursiveMutex(--recursionCount, threadNumber);
    
    m1.unlock();
    std::cout << "unlock the therad " << threadNumber << " resCount " << recursionCount << std::endl;

    return;
}
std::mutex m2;
int buffer = 0;
void task(const char* threadName, int loopFor)
{
    std::lock_guard<std::mutex> lock(m2);
    for (size_t i = 1; i <= loopFor; ++i)
    {
        buffer++;
        std::cout << threadName << ": " << buffer << std::endl;
    }

    return;
}

int main(){
    //recursive mutex
    //std::cout << "Enter the mutex program !!\n";
    //std::thread t1(recursiveMutex, 3, 1);
    //std::thread t2(recursiveMutex, 2, 2);

    //t1.join();
    //t2.join();
    
    // lockguard code
    std::thread t3(task, "T1", 5);
    std::thread t4(task, "T2", 4);
    t3.join();
    t4.join();
    
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
