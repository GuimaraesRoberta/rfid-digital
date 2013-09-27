#include "systemc.h"

SC_MODULE(Estimulos)
{
	sc_out <unsigned int> A, B;
	sc_in <bool> Clk;
	
	void GeraEstimulos()
	{
		A.write(5);
		B.write(7);
		wait();
		
		A.write(7);
		B.write(5);
		wait();
		
		A.write(0);
		B.write(0);
		wait();
		
		sc_stop();
	}
	
	SC_CTOR(Estimulos)
	{
		SC_THREAD(GeraEstimulos);
		sensitive << Clk.pos();
	}
};
