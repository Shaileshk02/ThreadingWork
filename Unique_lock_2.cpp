// Unique_lock_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//std::adopt_lock means :
//"I promise this mutex is already locked. Please take ownership of it and unlock it automatically later."

// Without adopt_lock

//std::mutex mtx;
//
//void func()
//{
//    mtx.lock();
//
//    // critical section
//
//    mtx.unlock();
//}

//Problem:

//Easy to forget unlock()
//Exceptions can leave mutex locked

//With adopt_lock

//#include <iostream>
//#include <mutex>
//
//std::mutex mtx;
//
//void func()
//{
//    mtx.lock();  // already locked
//
//    std::lock_guard<std::mutex> lock(mtx, std::adopt_lock);
//
//    std::cout << "Critical section\n";
//
//} // lock_guard automatically unlocks
//Output:
//
//Critical section

//Why do we need it ?
//
//Suppose you've already locked multiple mutexes safely:
// std::lock(m1, m2);
//Now both mutexes are locked.
//You want RAII(automatic unlocking), so create lock objects :
//std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
//std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
//Without adopt_lock, this would be wrong :
//std::lock_guard<std::mutex> lg1(m1);
//because lock_guard would try to lock m1 again, causing problems.

//| Tag                | Meaning                              |
//| ------------------ | ------------------------------------ |
//| `std::defer_lock`  | Don't lock yet                       |
//| `std::try_to_lock` | Try locking, don't block             |
//| `std::adopt_lock`  | Mutex already locked, take ownership |
//|___________________________________________________________|
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file



#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
std::mutex m2;

int buffer(0);

void worker(const char* threadName)
{
    // Lock both mutexes safely (deadlock-free)
    std::lock(m1, m2);
    std::cout << threadName << std::endl;
    // Take ownership of already locked mutexes
    std::unique_lock<std::mutex> lock1(m1, std::adopt_lock);
    std::unique_lock<std::mutex> lock2(m2, std::adopt_lock);

    std::cout << "Both mutexes acquired\n";

    for (size_t i = 0; i < 2000; i++)
    {
        buffer++;
        if (buffer % 100 == 0)
            std::cout << threadName << " ";
    }

    // Critical section

} // lock1 and lock2 automatically unlock m1 and m2

int main()
{
    std::thread t1(worker, "T1");
    std::thread t2(worker, "T2");
    t1.join();
    t2.join();
}