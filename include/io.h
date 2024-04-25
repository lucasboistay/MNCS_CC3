#ifndef IO_H
#define IO_H
//#include <Eigen/Dense>
#include <Eigen/Dense>
#include <fstream>

void ecrit_pot1(const std::string filename, const Eigen::VectorXf &pot, const int nl, const int nc, const float pas_in);
void ecrit_pot2(const std::string filename, const Eigen::VectorXf &pot, const int nl, const int nc, const float pas_in,
                    const int iligext, const int icol0ext, const int icol1ext, const float pas_out);
void ecrit_data(std::ofstream &my_file, const Eigen::VectorXf &pot, const int nl, const int nc);
void ecrit_champ(const std::string filename, const int nl, const int nc, 
              const Eigen::VectorXf &ex, const Eigen::VectorXf &ey);
#endif