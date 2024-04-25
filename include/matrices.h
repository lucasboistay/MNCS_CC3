#ifndef MATRICES_H
#include <Eigen/Dense>


Eigen::MatrixXf matl2d(int nl, int nc);
Eigen::MatrixXf mat_id(int n);
Eigen::MatrixXf mat_diag(int n);
void insert_armature(Eigen::MatrixXf &l2d, const int nl, const int nc, const int ilig, const int icol0, const int icol1);
void insert_domaine_ext(Eigen::MatrixXf &l2d, const int nl, const int nc, const int iligext, const int icol0ext, const int icol1ext, const float alpha);
#define MATRICES_H
#endif
