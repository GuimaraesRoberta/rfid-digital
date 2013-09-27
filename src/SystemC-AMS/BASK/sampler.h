#include "systemc.h"
#include "systemc-ams.h"

SCA_TDF_MODULE(sampler)
{
	sca_tdf::sca_in<double> in;
	sca_tdf::sca_out<bool> out;
	
	SCA_CTOR(sampler): in("in"), out("out"), rate(40), threshold(0.2) {}
	
	void set_attributes()
	{
		in.set_rate(rate);
		sample_pos = (unsigned long)std::ceil(2.0 * (double)rate/3.0);
	}
	
	void processing()
	{
		if (in.read(sample_pos) > threshold)
			out.write(true);
		else
			out.write(false);
	}
	
private:
	unsigned long rate;
	double threshold;
	unsigned long sample_pos;
};
