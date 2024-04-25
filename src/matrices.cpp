#include "../include/matrices.h"
#include <iostream>

using namespace Eigen;
using namespace std;

MatrixXf mat_id(int n){
    return MatrixXf::Identity(n, n);
}

MatrixXf mat_diag(int n){
    MatrixXf mat = mat_id(n);
    mat = -4*mat;
    
    for (int i=1; i<n; i++){
        mat(i, i-1) = 1;
        mat(i-1, i) = 1;
    }

return mat;
}

MatrixXf matl2d(int nl, int nc){

MatrixXf mat2 = MatrixXf::Zero(nl*nc, nl*nc);
//cout << mat2;

for (int i=0; i<nl; i++){
    mat2.block(i*nc, i*nc, nc, nc) = mat_diag(nc);
    }
    
for (int i=0; i<nl-1; i++){

    mat2.block(i*nc, (i+1)*nc, nc, nc) = mat_id(nc);
    mat2.block((i+1)*nc, i*nc, nc, nc) = mat_id(nc);
    }
    
return mat2;

}

void insert_armature(MatrixXf &l2d, const int nl, const int nc, const int ilig, const int icol0, const int icol1) {
    // Modification de la matrice du laplacien pour prendre en compte l'armature du condensateur

    for (int i = ilig*nc + icol0; i <= ilig*nc + icol1; i++) {
        l2d.row(i) = VectorXf::Zero(nl*nc);
        l2d(i, i) = 1;
    }
}

void insert_domaine_ext(Eigen::MatrixXf &l2d, const int nl, const int nc, const int iligext, const int icol0ext, const int icol1ext, const float alpha) {
    // Mdification de la matrice du laplacien pour insérer un domaine extérieur avec un pas de alpha*p

    // Les lignes du haut
    for (int i=0; i < iligext; i++) {
        // au centre
        for (int j = icol0ext+1; j < icol1ext; j++) {
            l2d(i*nc + j, i*nc + j) = -2*(pow(alpha,2) + 1);
            l2d(i*nc + j, i*nc + j + 1) = pow(alpha,2);
            l2d(i*nc + j, i*nc + j - 1) = pow(alpha,2);
            l2d(i*nc + j, i*(nc-1) + j) = 1;
            l2d(i*nc + j, i*(nc+1) + j) = 1;

        }
        // a gauche
        l2d(i*nc + icol0ext, i*nc + icol0ext + 1) = alpha;
        l2d(i*nc + icol0ext, i*nc + icol0ext) = -2 - (alpha+1);
        // a droite
        l2d(i*nc + icol1ext, i*nc + icol1ext - 1) = alpha;
        l2d(i*nc + icol1ext, i*nc + icol1ext) = -2 - (alpha+1);
    }

    // la ligne iligext
    for (int j = 0; j < icol0ext; j++) {
        l2d(iligext*nc + j, iligext*nc + j + nc) = alpha;
        l2d(iligext*nc + j, iligext*nc + j) = -2 - (alpha+1);
    }
    for (int j = icol0ext+1; j < icol1ext; j++) {
        l2d(iligext*nc + j, iligext*nc + j + 1) = alpha * (alpha+1) / 2.;
        l2d(iligext*nc + j, iligext*nc + j - 1) = alpha * (alpha+1) / 2.;
        l2d(iligext*nc + j, iligext*nc + j + nc) = alpha;
        l2d(iligext*nc + j, iligext*nc + j) = -pow(alpha+1, 2);
    }
    for (int j = icol1ext+1; j < nc; j++) {
        l2d(iligext*nc + j, iligext*nc + j + nc) = alpha;
        l2d(iligext*nc + j, iligext*nc + j) = -2 - (alpha+1);
    }
    // et les coins
    // PARTIE A EXPLIQUER
    l2d(iligext*nc+icol0ext, iligext*nc+icol0ext+nc) = alpha;
    l2d(iligext*nc+icol0ext, iligext*nc+icol0ext+1)  = alpha;
    l2d(iligext*nc+icol0ext, iligext*nc+icol0ext) = -2*(alpha+1);
    // FIN DE LA PARTIE A EXPLIQUER
    l2d(iligext*nc+icol1ext, iligext*nc+icol1ext+nc) = alpha;
    l2d(iligext*nc+icol1ext, iligext*nc+icol1ext-1)  = alpha;
    l2d(iligext*nc+icol1ext, iligext*nc+icol1ext) = -2*(alpha+1);

    // Les cotes en bas
    for (int i=iligext+1; i < nl-1; i++) {
        // a gauche
        for (int j = 0; j < icol0ext; j++) {
            l2d(i*nc + j, i*nc + j + nc) = pow(alpha,2);
            l2d(i*nc + j, i*nc + j - nc) = pow(alpha,2);
            l2d(i*nc + j, i*nc + j) = -2 * (pow(alpha,2)+1);
        }
        // et le bord gauche
        l2d(i*nc + icol0ext, i*nc + icol0ext + nc) = alpha * (alpha+1) / 2.;
        l2d(i*nc + icol0ext, i*nc + icol0ext - nc) = alpha * (alpha+1) / 2.;
        l2d(i*nc + icol0ext, i*nc + icol0ext + 1) = alpha;
        l2d(i*nc + icol0ext, i*nc + icol0ext) = -pow(alpha+1, 2);
        // et le bord droit
        l2d(i*nc + icol1ext, i*nc + icol1ext + nc) = alpha * (alpha+1) / 2.;
        l2d(i*nc + icol1ext, i*nc + icol1ext - nc) = alpha * (alpha+1) / 2.;
        l2d(i*nc + icol1ext, i*nc + icol1ext - 1) = alpha;
        l2d(i*nc + icol1ext, i*nc + icol1ext) = -pow(alpha+1, 2);
        // a droite
        for (int j = icol1ext + 1; j < nc; j++) {
            l2d(i*nc + j, i*nc + j + nc) = pow(alpha,2);
            l2d(i*nc + j, i*nc + j - nc) = pow(alpha,2);
            l2d(i*nc + j, i*nc + j) = -2 * (pow(alpha,2)+1);
        }
    }

    // la ligne du bas
    // a gauche
    for (int j = 0; j < icol0ext; j++) {
        l2d((nl-1)*nc + j, (nl-1)*nc + j - nc) = pow(alpha,2);
        l2d((nl-1)*nc + j, (nl-1)*nc + j) = -2 * (pow(alpha,2)+1);
    }
    // et le bord gauche
    l2d((nl-1)*nc + icol0ext, (nl-1)*nc + icol0ext - nc) = alpha * (alpha+1) / 2.;
    l2d((nl-1)*nc + icol0ext, (nl-1)*nc + icol0ext + 1) = alpha;
    l2d((nl-1)*nc + icol0ext, (nl-1)*nc + icol0ext) = -pow(alpha+1, 2);
    // et le bord droit
    l2d((nl-1)*nc + icol1ext, (nl-1)*nc + icol1ext - nc) = alpha * (alpha+1) / 2.;
    l2d((nl-1)*nc + icol1ext, (nl-1)*nc + icol1ext - 1) = alpha;
    l2d((nl-1)*nc + icol1ext, (nl-1)*nc + icol1ext) = -pow(alpha+1, 2);
    // a droite
    for (int j = icol1ext + 1; j < nc; j++) {
        l2d((nl-1)*nc + j, (nl-1)*nc + j - nc) = pow(alpha,2);
        l2d((nl-1)*nc + j, (nl-1)*nc + j) = -2 * (pow(alpha,2)+1);
    }
}


