#include "rectifier.h"
#include "ltf_nd_filter.h"
#include "sampler.h"

SC_MODULE(bask_demod)
{
	sca_tdf::sca_in<double> in;
	sca_tdf::sca_out<bool> out;

	sca_util::sca_trace_file* atf;
	
	rectifier rc;
	ltf_nd_filter lp;
	sampler sp;
	
	bask_demod(sc_module_name _name, sca_util::sca_trace_file* _atf)
	: sc_module(_name), in("in"), out("out"), rc("rc"), lp("lp", 3.3e6), sp("sp"), rc_out("rc_out"), lp_out("lp_out"), atf(_atf)
	{
		rc.in(in);
		rc.out(rc_out);

		sca_util::sca_trace( atf, rc_out, "rc_out");
		
		lp.in(rc_out);
		lp.out(lp_out);

		sca_util::sca_trace( atf, lp_out, "lp_out");
		
		sp.in(lp_out);
		sp.out(out);
	}
	
private:
	sca_tdf::sca_signal<double> rc_out, lp_out;
};
