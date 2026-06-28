// Thread_deadlock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m1;
std::mutex m2;

void thread1()
{
    m1.lock();
    //std::this_thread::sleep_for(std::chrono::seconds(3));// add this line to see deadlock
    m2.lock();

    cout << "Critical section of therad 1" << endl;

    m1.unlock();
    m2.unlock();

    return;
}

void theread2()
{
    m2.lock();
    m1.lock();

    cout << "critical section of thread 2" << endl;

    m2.unlock();
    m1.unlock();


}





int main()
{

    thread t1(thread1);
    thread t2(theread2);
    t1.join();
    t2.join();

    std::cout << "Hello World!\n";
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
