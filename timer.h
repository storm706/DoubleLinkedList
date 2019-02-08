#pragma once
#include <iostream>
#include<thread>
using namespace std;

class timer
{
public:
	timer()
	{
		start = chrono::high_resolution_clock::now();
	}
	~timer()
	{
		stop = chrono::high_resolution_clock::now();
		chrono::duration<float> dur = stop - start;
		cout << "Duration :" << dur.count() << " sec" << endl<<endl;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> start, stop;
};
