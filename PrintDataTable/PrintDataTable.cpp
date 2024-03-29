// PrintDataTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Util.h"
#include <iostream>
#include <time.h>
#include <thread>
#include <windows.h>

using namespace std;

int fib_1000; //1000th FIB
int interval = -1;
clock_t start_time;
bool isPaused = false;
unordered_map<int, int> data_table; // number<->count

enum STATE
{
	STOPPED,
	RUNNING,
	PAUSED,
	INPUTTING, // inputting new entry
	QUITTED
};

STATE state = STATE::STOPPED;

void print_data(unordered_map<int, int> data)
{
	auto output = Util::convert_data(data);

	bool print_comma = false;
	for (auto it = output.begin(); it != output.end(); it++)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (print_comma)
			{
				cout << ", ";
			}
			print_comma = true;

			cout << *it2 << ":" << it->first;
		}
	}

	cout << endl;
}

void print_task()
{
	while (state != STATE::QUITTED)
	{
		Sleep(interval * CLOCKS_PER_SEC);

		auto more_sleep = interval * CLOCKS_PER_SEC - (clock() - start_time);
		if (!isPaused &&  more_sleep > 0) // ever paused during the above sleep
		{
			Sleep(more_sleep);
		}
		else if (isPaused) // still being paused
		{
			continue;
		}

		if (state == STATE::RUNNING)
		{
			print_data(data_table);
		}
	}
}

void print_instruction()
{
	cout << "---------------------------------------" << endl;
	cout << "P: The program enters the Paused state." << endl;
	cout << "R: The program enters the Run State."    << endl;
	cout << "N: The program prompts for a new entry." << endl;
	cout << "Q: The program quits."                   << endl;
	cout << "---------------------------------------" << endl;
}

// Updates state according to choice
void update_state(char choice)
{
	switch (choice)
	{
	case 'P':
	{
		isPaused = true;
		state = STATE::PAUSED;
		cout << "Timer is paused." << endl;
		break;
	}
	case 'R':
	{
		if (isPaused)
		{
			start_time = clock();
			isPaused = false;
		}
		state = STATE::RUNNING;
		cout << "Timer is running." << endl;
		break;
	}
	case 'N':
	{
		state = STATE::INPUTTING;
		if (isPaused)
		{
			start_time = clock();
			isPaused = false;
		}
		cout << "Please enter the new number:" << endl;
		int new_number;
		cin >> new_number;
		Util::add_number(data_table, new_number);

		if (Util::isFibonacci(new_number) && new_number <= fib_1000)
		{
			cout << "FIB!" << endl;
		}

		state = STATE::RUNNING;
		break;
	}
	case 'Q':
	{
		state = STATE::QUITTED;

		print_data(data_table);
		cout << "See you next time!" << endl;
		break;
	}
	}
}

// The task to process the choice
void state_machine_task()
{
	state = STATE::RUNNING;
	char choice;

	while (state != STATE::QUITTED)
	{
		cin >> choice;
		update_state(choice);
	}
}

int main()
{
	//1000th FIB
	fib_1000 = Util::fib(1000);

	int first_number;
	cout << "Please enter the output period (greater than 0, in second): " << endl;
	cin >> interval;
	// TODO: handle wrong inputs, same in other codes calling "cin"

	cout << "Please enter the first number (only integer supported): " << endl;
	cin >> first_number;
	Util::add_number(data_table, first_number);

	print_instruction();

	thread thread1(&print_task);
	thread thread2(&state_machine_task);

	thread1.join();
	thread2.join();

	return 0;
}