#ifndef PID_H
#define PID_H
#include <vector>
class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double prev_error;
  
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

 // twiddle variables
  std::vector<double> p,dp;
  double total_error,best_error;
  int step,index,setstep;
  bool twiddle_enable,adding,subing;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  
  // steer_value
  double TotalSteer();
  
  // best_error
  double BestError();
};

#endif /* PID_H */
