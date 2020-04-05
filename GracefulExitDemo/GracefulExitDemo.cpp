// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include <fstream>
#include <sstream>

using namespace std;

bool run_flag{ true };
void log_2_file(const string& txt)
{
	ofstream ofs("test.txt", ofstream::app);
	ofs << txt << endl;
	ofs.close();
}

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
	// handle CTRL_CLOSE_EVENT
	if (CTRL_CLOSE_EVENT == dwCtrlType)
	{
		cout << "CTRL_CLOSE_EVENT == dwCtrlType\n";

		// Set flag to indicate all 
		run_flag = false;
		log_2_file("Inside ConsoleHandlerRoutine, setting the global run_flag to false");

		cout << "Sleeping for 10 seconds before program terminates\n";
		this_thread::sleep_for(chrono::seconds(10));
		return TRUE;
	}

	return FALSE;
}

class A
{
public:
	A()
	{
		cout << "A()\n";
		log_2_file("A()\n");
	}
	~A()
	{
		cout << "~A()\n";
		log_2_file("~A()\n");
	}
};


int main()
{
	// Register the console handler which will handle CTRL_CLOSE_EVENT
	if (FALSE == SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE)) {
		// Cannot register your handler? Check GetLastError()
		log_2_file("Can not register handler\n");
	}

	log_2_file("main()!\n");

	// Testing if ~A() is called
	A a;



	while (run_flag)
	{
		static auto start_t = chrono::steady_clock::now();
		this_thread::sleep_for(chrono::milliseconds(1000));

		cout << "[" << chrono::duration_cast<chrono::milliseconds>
			(chrono::steady_clock::now() - start_t).count() <<
			"] milliseconds passed since program start\n";
	}


	log_2_file("Exited while loop");


	log_2_file("Exiting from main()");
	this_thread::sleep_for(chrono::seconds(2));
	A a2;
	return 0;
}

