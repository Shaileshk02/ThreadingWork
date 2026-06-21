#pragma once

#include <thread>
#include <iostream>

class JoinAttachClass {

public:
	JoinAttachClass() = default;
	static void runThread(int count);
};
