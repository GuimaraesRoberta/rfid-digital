#include "systemc.h"

SC_MODULE(integ) {
   
   sc_in<double>  u;
   sc_out<double> y;
   
   double   TAU;     // time constant
   double   state;   // internal state
//   double   DDT;     // real valued time step
      
   void sig_proc() {
      sc_time DT(10, SC_US);
      double DDT = DT.to_seconds();
      cout << name() << ": t = " << sc_time_stamp()
                     << " TAU = " << TAU
                     << ": DDT = " << DDT
                     << " DT = " << DT << endl;
      while (true) {
         state = (state*TAU + u.read()*DDT)/(TAU + DDT);
         cout << name() << ": t = " << sc_time_stamp()
                        << " u = " << u.read()
                        << " state = " << state << endl;
         y.write(state);
         wait(DT);
      }   
   }
   
   SC_CTOR(integ) {
      
      // initializations
      TAU = 2.0e-4;
      state = 0.0;
      
      // signal processing behavior
      SC_THREAD(sig_proc);
   }         
}; // integ

SC_MODULE(stim) {
   
   sc_out<double> sout;
   
   void sig_proc() {
//      cout << name() << ": t = " << sc_time_stamp() << endl;
      sout.write(0.0);
      wait(0.1, SC_MS);
//      cout << name() << ": t = " << sc_time_stamp() << endl;
      sout.write(1.0);
   }   
   
   SC_CTOR(stim) {
      SC_THREAD(sig_proc);
   }   
   
}; // stim

SC_MODULE(trace)
{
   sc_in<double> sin;
   ofstream output;

   void do_trace() {
//      cout << name() << ": t = " << sc_time_stamp() << endl;
      output << simcontext()->time_stamp().to_seconds() << "\t "
             << sin.read() << endl;
   }

   SC_CTOR(trace) {
      output.open(name(), ios::out);
      SC_METHOD(do_trace);
         sensitive << sin;
   }
};

int sc_main(int argc, char* argv[])
{
   sc_signal<double> u, y;
   
   sc_set_time_resolution(1.0, SC_US);
   
   integ uut("integ");
      uut.u(u);
      uut.y(y);
      
   stim src("input");
      src.sout(u);
      
   trace tr_u("trace_u");
      tr_u.sin(u);

   trace tr_y("trace_y");
      tr_y.sin(y);

   sc_start(2.0, SC_MS);

   return 0;
}
