#include <iostream>
#include <fstream>
#include <iomanip>
#include <Eigen/Dense>
#include <cmath>
#include <string>
#include <functional>
#include <chrono>

//en-t�tes personnels

#include "../include/matrices.h"
#include "../include/condlim.h"
#include "../include/io.h"

using namespace std::chrono;
using namespace std;


int main(){

    string filename = "data/laplace.dat";

    int nl;
    float alpha;
    int ilig;
    int icol0;
    int icol1;
    int iligext;
    int icol0ext;
    int icol1ext;

    cout << "Entrer la valeur de nl, iligext, icol0ext, icol1ext et alpha." << endl;
    cin >> nl >> iligext >> icol0ext>>icol1ext>>alpha;

    int nc = nl;
    float L = 6.;
    float pin = L/(nl+1);
    float pout = alpha*pin;


    Eigen::MatrixXf l2d;
    Eigen::VectorXf b;
    Eigen::VectorXf potential(nl*nc);

    ilig = 2*(nl+1)/3 - 1;
    icol0 = (nc+1)/3 - 1;
    icol1 = 2*(nc+1)/3 - 1;
    float V0 = 5;

    cout<< "pin :" << pin << ",ilig :" << ilig << ",icol0 :" << icol0 << ",icol1 :" << icol1 << endl;

    l2d = matl2d(nl, nc);

    insert_domaine_ext(l2d, nl, nc, iligext, icol0ext, icol1ext, alpha);
    insert_armature(l2d, nl, nc, ilig, icol0, icol1);
    //cout << l2d << endl;

    b = sm_condensateur(nl, nc, ilig, icol0, icol1, V0);
    //cout << b << endl;

    auto start = std::chrono::high_resolution_clock::now();
    potential = l2d.colPivHouseholderQr().solve(b);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    cout << duration.count() << " ms" << endl;
    ecrit_pot2(filename, potential, nl, nc, pin, iligext, icol0ext, icol1ext, pout);

    return 0;

}
