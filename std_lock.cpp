// std_lock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// it is used to lock multiple mutex at the same time.
// std::lock(m1,m2,m3); all arguments are locked via a seq of calls to lock() or try lock or unlock on each arg.
// order of lociking is not defined but it is locked no deadlock manner.
// it is a blocking call.
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

// below code will not deadlock due to std::lock()
mutex m1, m2;

void task_a()
{
    while (1)
    {
        std::lock(m1, m2);
        cout << " a " << endl;
        m1.unlock();
        m2.unlock();

    }
    return;

}

void task_b()
{
    while (1)
    {
        std::lock(m2, m1);
        cout << " b " << endl;
        m2.unlock();
        m1.unlock();
    }
    return;

}

int main()
{
    thread t1(task_a);
    thread t2(task_a);

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
