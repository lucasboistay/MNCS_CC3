#include <iostream>
#include "../include/io.h"

using namespace std;
using namespace Eigen;

void ecrit_pot1(const string filename, const VectorXf &pot, const int nl, const int nc, const float pas_in) {

  ofstream my_file;

  my_file.open(filename);
  // Verification de la connexion du fichier au flot my_file
  if (! my_file) {
    cerr << "erreur ouverture du fichier " << filename;
    exit(EXIT_FAILURE);
  }

  // entete d'une ligne  : nb de lignes et de colonnes (bords compris) et pas
  my_file << "# 1 " << nl+2 << " " << nc+2 << " " << pas_in << endl;

  ecrit_data(my_file, pot, nl, nc);
            
  my_file.close();
}

void ecrit_pot2(const string filename, const VectorXf &pot, const int nl, const int nc, const float pas_in,
              const int iligext, const int icol0ext, const int icol1ext, const float pas_out) {

  ofstream my_file;

  my_file.open(filename);
  // Verification de la connexion du fichier au flot my_file
  if (! my_file) {
    cerr << "erreur ouverture du fichier " << filename;
    exit(EXIT_FAILURE);
  }

  // entete de 2 ligne  : 
  // - nb de lignes et de colonnes (bords compris) et pas domaine interne
  // - indice de ligne, col0, col1 et pas du domaine externe
  my_file << "# 2 " << nl+2 << " " << nc+2 << " " << pas_in << endl;
  my_file << "# " << iligext << " " << icol0ext << " " << " " << icol1ext << " " << pas_out << endl;

  ecrit_data(my_file, pot, nl, nc);
            
  my_file.close();
}

void ecrit_data(ofstream &my_file, const VectorXf &pot, const int nl, const int nc) {


  // bord du haut
  my_file << VectorXf::Zero(nc+2).transpose() << endl;

  // lignes 1 a nl
  for (int i=0; i<nl; i++) {
    my_file << 0 << " ";
    my_file << pot.segment(i*nc, nc).transpose() << " ";
    my_file << 0 << endl;
  }

  // bord du bas (Sud)
  my_file << VectorXf::Zero(nc+2).transpose() << endl;
}

void ecrit_champ(const string filename, const int nl, const int nc, const VectorXf &ex, const VectorXf &ey) {
  ofstream my_file;

  my_file.open(filename);

  // Verification de la connexion du fichier au flot my_file
  if (! my_file) {
    cerr << "erreur ouverture du fichier " << filename;
    exit(EXIT_FAILURE);
  }
  // ex
  for (int i=0; i<nl; i++) {
    my_file << ex.segment(i*nc, nc).transpose() << endl;
  }
  // ey
  for (int i=0; i<nl; i++) {
    my_file << ey.segment(i*nc, nc).transpose() << endl;
  }

}
