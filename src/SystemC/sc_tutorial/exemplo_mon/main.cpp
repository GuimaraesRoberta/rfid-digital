#include "systemc.h"
#include "maior.h"
#include "estimulos.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal <unsigned int> sinalA, sinalB, sinalC;
	sc_clock clock(" Clock", 10, SC_NS,0.5, 1, SC_NS);
	
	Estimulos est("Estimulos");
	Maior m("Maior");
	Monitor mon("Monitor");
	
	est.A(sinalA);
	est.B(sinalB);
	est.Clk(clock);
	
	m.A(sinalA);
	m.B(sinalB);
	m.C(sinalC);
	
	mon.A(sinalA);
	mon.B(sinalB);
	mon.C(sinalC);
	mon.Clk(clock);
	
	sc_start();
	
	return 0;
}
