// ConditionVariable1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// conditional variable works on perticular mutex. If condition is not met it waits, unlocks the thread and then
// other threads start working. Once they complete the work, the other thread notify that it is done the work
// after this first thread checks the condition again and completes the work if condition is met.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int balance = 0;
std::mutex m1;
std::condition_variable cv;

int addMoney(int money)
{
    
    std::lock_guard<mutex> lg(m1);
    cout << "inside add money" << endl;

    balance = balance + money;
    cout << "add money : balance is : " << balance << endl;
    cv.notify_one();
    return balance;
}

int withdrawMoney(int money)
{
    std::unique_lock<mutex> ul(m1);
    cout << "inside withdraw money" << endl;
    cv.wait(ul, [] {return (balance != 0) ? true : false; });
    if (balance < money)
    {
        cout << "Less balance" << endl;
    }
    else
    {
        balance -= money;
    }
    cout << "after withdraw balance is : " << balance << endl;
    return balance;
}


int main()
{
    thread t1(addMoney, 200);
    thread t2(withdrawMoney, 500);

    t1.join(); t2.join();
    
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
