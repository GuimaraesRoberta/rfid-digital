#include "systemc.h"

SC_MODULE(Maior)
{
	sc_in <unsigned int> A, B;
	sc_out <unsigned int> C;
	
	void do_Maior()
	{
		C.write(A.read() > B.read() ? A.read(): B.read());
	}
	
	SC_CTOR(Maior)
	{
		SC_METHOD(do_Maior);
		sensitive << A << B;
	}
};
