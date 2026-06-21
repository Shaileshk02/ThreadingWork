#include <iostream>
#include <thread>
#include "JoinAttach.h"

using namespace std;

void JoinAttachClass::runThread(int count)
{
	for (size_t i = 0; i < count; i++)
	{
		cout << "Attach Running thread: " << i << endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}
