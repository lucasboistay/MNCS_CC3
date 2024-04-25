#include <iostream>
#include <fstream>
#include <iomanip>

//en-t�tes personnels
#include "../include/condlim.h"

#include <Eigen/Dense>

using namespace std;

Eigen::VectorXf sm_condensateur(const int nl, const int nc, const int ilig, const int icol0, const int icol1, const float V_0){

    Eigen::VectorXf B;
    B = Eigen::VectorXf::Zero(nl*nc);

    for (int i=nc*ilig+icol0; i<nc*ilig+icol1+1; i++){
        B(i) = V_0;
    }

    return B;
}


