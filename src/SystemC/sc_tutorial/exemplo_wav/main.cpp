#include "systemc.h"
#include "maior.h"
#include "estimulos.h"

int sc_main(int argc, char* argv[])
{
	sc_signal <unsigned int> sinalA, sinalB, sinalC;
	sc_clock clock(" Clock", 10, SC_NS,0.5, 1, SC_NS);
	
	Estimulos est("Estimulos");
	Maior m("Maior");
	
	est.A(sinalA);
	est.B(sinalB);
	est.Clk(clock);
	
	m.A(sinalA);
	m.B(sinalB);
	m.C(sinalC);
	
	sc_trace_file* Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace (Tf,sinalA,"A");
	sc_trace (Tf,sinalB,"B");
	sc_trace (Tf,sinalC,"C");
	sc_trace (Tf,clock,"Clk");
	
	sc_start();
	
	sc_close_vcd_trace_file(Tf);
	
	return 0;
}
