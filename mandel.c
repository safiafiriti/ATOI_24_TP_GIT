#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"
 
 
#define TRSH 2.0	//Seuil de divergence
#define ITER 1024ull	// Nbr max d'iterations
 
#define SIZEX 1500	//Largeur de l'image
#define SIZEY 1500	//hauteur de l'image
 
 //Fonction pour calculer la partie réelle dun nbr complexe à partir de la coordonnée x dans l'image
double cx( int x )
{
    /* -2 ---> 1 */
    static const double qx = 3.0 / (double)SIZEX;
    return 1.0 +  x * qx;
}

//Fonction pour calculer la partie imaginaire dun nbr complexe à partir de la coordonnée y dans l'image
double cy( int y )
{
    /* -1 ---> 1 */
    static const double qy = 2.0 / (double)SIZEY;
    return 1.0 + y * qy;
}
 
int main(int argc, char *argv[])
{
    struct ppm_image im;
    ppm_image_init( &im , SIZEX , SIZEY ); //Initialise l'image avec les dimensions spécifiées
 
    int i,j;
    double colref = 255.0/log(ITER); //calcul de la réference de couleur basée sur le logarithme du nbr max ditérations
	
	//Boucle pour parcourir chaque pixel de l'image
    for (i = 0; i < SIZEX; ++i) {
        for (j = 0; j < SIZEY; ++j) {
 
            unsigned long int iter = 0;
 
            double complex c =  cx(i) + cy(j) * I; //Définition d'un nbr complexe c en fct des coordonnées i et j
            double complex z = 0;
 
            while(iter < ITER)
            {
                double mod = cabs(z); //Calcul du module de z
				
				//vérifie si le module de z dépasse le seuil de divergence
                if( TRSH < mod )
                {
                    break;
                }
 
                z = z*z + c; //Mise à jour de z selon la formule du fractal de Mandelbrot
 
                iter++;
            }
 
            int grey = colref*log(iter); //Calcul de la couleur grise basée sur le nbr d'itérations
            ppm_image_setpixel(&im, i,j, grey, grey , grey ); //Définition de la couleur du pixel dans l'image
        }
    }
 
    ppm_image_dump( &im, "m.ppm"); //Sauvegarde de l'image dans un fichier PPM
    ppm_image_release( &im ); //Libération de la mémoire allouée pour l'image
 
 
    return 0;
}
