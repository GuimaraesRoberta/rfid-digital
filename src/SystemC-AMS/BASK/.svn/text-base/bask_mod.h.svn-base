#include "sin_src.h"
#include "mixer.h"

SC_MODULE(bask_mod)
{
	sca_tdf::sca_in<bool> in;
	sca_tdf::sca_out<double> out;
	
	sin_src sine;
	mixer mix;
	
	SC_CTOR(bask_mod)
	: in("in"), out("out"), sine("sine", 1.0, 1.0e7, sca_core::sca_time(5.0, sc_core::SC_NS)), mix("mix")
	{
		sine.out(carrier);
		mix.in_wav(carrier);
		mix.in_bin(in);
		mix.out(out);
	}

private:
	sca_tdf::sca_signal<double> carrier;
};
