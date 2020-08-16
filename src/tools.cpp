#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
    * Calculate the RMSE here.
  */

  VectorXd rmse(4);
  rmse << 0,0,0,0;

  // check the validity of the following inputs:
  //  * the estimation vector size should not be zero
  //  * the estimation vector size should equal ground truth vector size
  if(estimations.size() != ground_truth.size() || estimations.size() == 0){
    std::cout << "Invalid estimation or ground_truth data" << std::endl;
    return rmse;
	
  }

  //accumulate squared residuals
  for(unsigned int i=0; i < estimations.size(); ++i){

    VectorXd residual = estimations[i] - ground_truth[i];

//Error display
//std::cout<<"";
//std::cout<<i;
//std::cout<<"~Prediction Error (residual):"<<std::endl;
//std::cout<<residual<<std::endl;
//std::cout<<std::endl;

    //coefficient-wise multiplication
    residual = residual.array()*residual.array();
    rmse += residual;
  }

//calculate the mean
  rmse = rmse/estimations.size();

  //calculate the squared root
  rmse = rmse.array().sqrt();



  /*

// Standard Deviation of predicted value Estiamation
VectorXd sum(4);
sum << 0,0,0,0;
VectorXd mean(4);
mean << 0,0,0,0;
VectorXd stde(4);
stde << 0,0,0,0;

for(unsigned int j=0; j < estimations.size(); j++){

sum = sum + estimations[j];

}

//calculate the mean
mean = sum/estimations.size();

for(unsigned int k=0; k < estimations.size(); k++){

stde = estimations[k] - mean;

    //coefficient-wise multiplication
stde = stde.array()*stde.array();

}

  //calculate the mean
stde = stde/estimations.size();

  //calculate the squared root
stde = stde.array().sqrt();

// Display Std. Deviation
std::cout<<"Std.Deviation (predicted):"<<std::endl;
std::cout<<stde<<std::endl;
std::cout<<std::endl;

// Standard Deviation of ground truth value Estiamation
VectorXd sumg(4);
sumg << 0,0,0,0;
VectorXd meang(4);
meang << 0,0,0,0;
VectorXd stdeg(4);
stdeg << 0,0,0,0;

for(unsigned int j=0; j < estimations.size(); j++){

sumg = sumg + ground_truth[j];

}

//calculate the mean
meang = sumg/estimations.size();

for(unsigned int k=0; k < estimations.size(); k++){

stdeg = estimations[k] - meang;

    //coefficient-wise multiplication
stdeg = stdeg.array()*stdeg.array();

}

  //calculate the mean
stdeg = stdeg/estimations.size();

  //calculate the squared root
stdeg = stdeg.array().sqrt();

// Display Std. Deviation
std::cout<<"Std.Deviation (ground truth):"<<std::endl;
std::cout<<stdeg<<std::endl;
std::cout<<std::endl;
  
*/


//return the result of rmse
  return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
    * Calculate a Jacobian here.
  */
  MatrixXd Hj(3,4);
  Hj << 0,0,0,0,
        0,0,0,0,
        0,0,0,0;

  //recover state parameters
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);

  //pre-compute a set of terms to avoid repeated calculation
  float c1 = px*px+py*py;
  float c2 = sqrt(c1);
  float c3 = (c1*c2);

  //check division by zero
  if(fabs(c1) < 0.0001){
    std::cout << "Function CalculateJacobian() has Error: Division by Zero" << std::endl;
    return Hj;
  }

  //compute the Jacobian matrix
  Hj << (px/c2),                (py/c2),                0,      0,
        -(py/c1),               (px/c1),                0,      0, 
        py*(vx*py - vy*px)/c3,  px*(px*vy - py*vx)/c3,  px/c2,  py/c2;

  return Hj;

}
