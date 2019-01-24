#include "PID.h"
#include <cmath>
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
     PID:: Kp = Kp;
     PID:: Ki = Ki;
     PID:: Kd = Kd;  
     p_error = 0;
     d_error = 0;
     i_error = 0 ;
     prev_error = 0; 
     p = {Kp,Ki,Kd};
     dp ={Kp*0.1,Ki*0.1,Kd*0.1};
     best_error = 9999.9;
     step = 1;
     twiddle_enable = true;
     adding = false;
     subing = false;
     index = 2;
     setstep = 2000;
 }

void PID::UpdateError(double cte) { 
     d_error = cte - prev_error;
     p_error = cte; 
     i_error += cte; 
     prev_error = cte;   
     if (step % setstep > 100){
         total_error += cte * cte;
       }
     if (twiddle_enable && step % setstep == 0){
         if (total_error < best_error){
              best_error = total_error;
               if (step != setstep){
                  dp[index] *= 1.1;    
                  }  
            index = (index + 1)%3;
            adding = false;
            subing =false;
           }
         if (!adding && !subing){             
              p[index] += dp[index];               
              adding = true;
            }
         else if (adding && !subing){
               p[index] -= 2*dp[index];                
               subing = true;
            }
         else {  
            p[index] += 0.9*dp[index]; 
            index = (index + 1) % 3;
            adding = false;
            subing = false;
            }  
      cout << "total_error" << total_error<< endl;
      total_error = 0;
      cout << "new parameters" << endl;
      cout << "Kp: " << p[0] << ", ki: " << p[1] << ", kd: " << p[2] << endl;   
     }
     step ++;
     cout << "step:" << step << endl;
  }
double PID::TotalError(){
     return p_error + i_error + d_error;  
 } 
double PID::TotalSteer() {  
     return - Kp * p_error - Kd * d_error - Ki * i_error;
}

    