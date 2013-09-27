#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;

SC_MODULE(Monitor)
{
	sc_in <unsigned int> A, B, C;
	sc_in <bool> Clk;
	
	void monitor()
	{
		cout << setw(10) << "Tempo";
		cout << setw(2) << "A";
		cout << setw(2) << "B";
		cout << setw(2) << "C" << endl;
		
		while(true)
		{
			cout << setw(10) << sc_time_stamp();
			cout << setw(2) << A.read();
			cout << setw(2) << B.read();
			cout << setw(2) << C.read() << endl;
			wait();
		}
	}
	
	SC_CTOR(Monitor)
	{
		cout << "Construindo " << name() << endl;
		SC_THREAD(monitor);
		sensitive << Clk.pos();
	}
};
