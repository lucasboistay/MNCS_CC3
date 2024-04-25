import numpy as np
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import axes3d, Axes3D # pour la 3D
#
#------ PARAMETRES a EDITER -------------------------#
fichier = "data/laplace.dat" # nom du fichier de donnees (ayant 1 ligne d'en-tete)
niso    = 50            # nombre de courbes de niveaux a tracer
#
# Angles de vue du graphique 3D :
Altitud= 35            # elevation
Azimuth=-50            # rotation
#
# Table de couleurs : ( .jet .coolwarm .Spectral .CMRmap ...)
ColorMap = plt.cm.Spectral          # pour le plot 3D
#----------------------------------------------------#
#

# lecture de la ligne d'entete : nl+2 , nc+2 , pas_in, pas_out
try:
    fp=open(fichier,"r")
except:
    print( " Erreur d'ouverture du fichier '%s' ."%fichier)
    exit(1)
params = fp.readline().strip().replace("#","").split()

try:
    ndom = int(params[0])
    nlig = int(params[1])
    ncol = int(params[2])
    pas_in = float(params[3])
except:
    print (" ! La ligne d'en-tete n'est pas au format attendu (nl nc pas) : ",params)
    pas=None

nl = nlig - 2
nc = ncol -2

# cas de domaines imbriqués
if ndom == 2:
    ligne = fp.readline().strip().replace("#","").split()
    ilig = int(ligne[0])
    icol0 = int(ligne[1])
    icol1 = int(ligne[2])
    pas_out = float(ligne[3])
fp.close()

# lecture des donnees : apres la 1ere ligne
data = np.loadtxt(fichier)

# Commentaires
print (" Nl = %d, Nc = %d, pas (domaine interieur) = %g"%(nl,nc,pas_in))
if ndom == 2:
   print("Domaine imbrique en ligne/col0/col1/pas: %d/%d/%d/%g"%(ilig, icol0, icol1, pas_out))

# Creation des axes X et Y (bords inclus):
x = np.linspace(0, nl+1, nl+2)*pas_in
y = np.linspace(0, nc+1, nc+2)*pas_in

# cas des domaines imbriqués
if ndom ==2:
    x[0:ilig+2] = np.linspace(0, ilig+1, ilig+2)*pas_out
    x[ilig+2:] = np.linspace(x[ilig+1]+pas_in, x[ilig+1] + (nl-ilig)*pas_in, nl-ilig)
    y[0:icol0+2] = np.linspace(0, icol0+1, icol0+2)*pas_out
    y[icol0+2:icol1+2] = np.linspace(y[icol0+1]+pas_in, y[icol0+1] + (icol1-icol0)*pas_in, icol1-icol0)
    y[icol1+2:] = np.linspace(y[icol1+1]+pas_out, y[icol1+1] + (nc-icol1)*pas_out, nc-icol1)

# Symmétrie d'axe x = (nl+1)*pas
xsym = np.concatenate((x,2*x[-1]-x[-2::-1]))
datasym = np.zeros((2*(nl+2)-1, nc+2))
datasym[0:nl+2,:] = data
datasym[nl+2:2*(nl+2)-2,:] = -data[nl:0:-1,:]

# creation des matrices de X et Y en tous points :
Y, XSYM = np.meshgrid(y, xsym)

# Affichage en contours :
plt.figure( figsize=(11.69,8.27) ) # format A4 paysage
ax = plt.gca()
ax.invert_yaxis()
contours = plt.contour(Y, XSYM, datasym, niso, cmap= plt.cm.jet)
# libelles des isothermes (1 chiffre apres la virgule)
plt.clabel(contours, inline=1, fmt="%.1f", fontsize=10)
plt.xlabel("Y")
plt.ylabel("X")
plt.title("Potentiel %dx%d"%(nl,nc))

fig = plt.gcf()
if ndom == 1:
   fig.savefig("data/laplace_%dx%d.pdf"%(nl,nc), format="pdf")
   print(" Le graphique 'laplace_%dx%d.pdf' a ete cree."%(nl,nc))
if ndom == 2:
   fig.savefig("data/laplace_%dx%d-2.pdf"%(nl,nc), format="pdf")
   print(" Le graphique 'laplace_%dx%d-2.pdf' a ete cree."%(nl,nc))

# affichage 3D :
fig3D= plt.figure( figsize=(11.69,8.27) )
try:
    #ax3d = Axes3D( fig3D ) 
    ax3d = plt.axes(projection='3d')
except:
    print( " Erreur ouverture Graphique 3D" )
    print ("\n Fermer la figure pour terminer.\n")
else:
    ax3d.invert_yaxis()
    ax3d.view_init( Altitud, Azimuth )
    ax3d.plot_surface(Y, XSYM, datasym, cmap=ColorMap,
                      rstride=1,cstride=1,linewidth=0.2)
    ax3d.set_xlabel("Y")
    ax3d.set_ylabel("X")
    ax3d.set_zlabel("Potentiel")
    fig = plt.gcf()
    if ndom == 1:
       fig.savefig("data/laplace3D_%dx%d.pdf"%(nl,nc), format="pdf")
       print( " Le graphique 'laplace3D_%dx%d-2.pdf' a ete cree."%(nl,nc) )
    if ndom == 2:
       fig.savefig("data/laplace3D_%dx%d-2.pdf"%(nl,nc), format="pdf")
       print( " Le graphique 'laplace3D_%dx%d-2.pdf' a ete cree."%(nl,nc) )
    print ("\n Fermer les 2 figures pour terminer.\n")

#plt.pause(5)
plt.show()
