
// Thread_Sync.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Thread or process synchronize to access critical section.
// Critical section is one or collection of prog statements which should be executed by 
// only 1 thread or process at at time.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
long long bankBalance = 0;
mutex m1;

void addMOney(long long val) {
    m1.lock();
    bankBalance += val;
    m1.unlock();
}

int main()
{
    thread t1(addMOney, 200);
    thread t2(addMOney, 5000000000);

    t1.join();
    t2.join();

    cout << bankBalance << endl;

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
