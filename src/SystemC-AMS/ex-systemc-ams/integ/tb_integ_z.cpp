#include "systemc.h"

SC_MODULE(integ_z) {
   
   sc_in<double>  u;
   sc_out<double> y;
   
   double   TAU;     // time constant
   double   FS;      // 
   double   NUM[2];  // numerator of z transfer function
   double   DEN[2];  // denominator of z transfer function
      
   void sig_proc() {
      double un = 0.0, un1 = 0.0, yn = 0.0, yn1 = 0.0;
      double DDT = 1/FS;
      sc_time DT(int(DDT*1e6), SC_US);
      cout << name() << ": TAU = " << TAU
                     << " DDT = " << DDT
                     << " DT = " << DT << endl;
      while (true) {
         un = u.read();
         yn = (NUM[0]*un + NUM[1]*un1 - DEN[1]*yn1)/DEN[0];
         y.write(yn);
         un1 = un;
         yn1 = yn;
         cout << name() << ": t = " << sc_time_stamp()
              << " un = " << un << " yn = " << yn
              << endl;
         wait(DT);
      }   
   }
   
   SC_CTOR(integ_z) {
      
      // initializations
      TAU = 2.0e-4;
      FS = 1.0e5;
      NUM[0] = 1.0;
      NUM[1] = 1.0;
      DEN[0] = 1.0 + 2.0*TAU*FS;
      DEN[1] = 1.0 - 2.0*TAU*FS;
      
      // signal processing behavior
      SC_THREAD(sig_proc);
   }         
}; // integ_z

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
   
   integ_z uut("integ_z");
      uut.u(u);
      uut.y(y);
      
   stim src("input");
      src.sout(u);
      
   trace tr_u("trace_u_z");
      tr_u.sin(u);

   trace tr_y("trace_y_z");
      tr_y.sin(y);

   sc_start(2.0, SC_MS);

   return 0;
}
