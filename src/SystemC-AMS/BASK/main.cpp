#include "bit_src.h"
#include "bask_mod.h"
#include "bask_demod.h"

int sc_main(int argc, char* argv[])
{
	sca_util::sca_trace_file* atf = sca_util::sca_create_vcd_trace_file("tr.vcd");

	sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);
	sca_tdf::sca_signal<bool> in_bits, out_bits;
	sca_tdf::sca_signal<double> wave;
	
	bit_src bs("bs");			// random bit source
		bs.out(in_bits);
	
	bask_mod mod("mod");		// modulator
		mod.in(in_bits);
		mod.out(wave);
	
	bask_demod demod("demod", atf);	// demodulator
		demod.in(wave);
		demod.out(out_bits);
	
	
	
	sca_util::sca_trace( atf, in_bits, "in_bits");
	sca_util::sca_trace( atf, wave, "wave");
	sca_util::sca_trace( atf, out_bits, "out_bits");
	
	sc_core::sc_start(1, sc_core::SC_US);
	
	sca_util::sca_close_vcd_trace_file(atf);
	
	return 0;
}
