#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"
 
 
#define TRSH 2.0 //seuil de divergence
#define ITER 1024ull // Nbr max d'itérations
 
#define SIZEX 1500 //Largeur de l'image
#define SIZEY 1500 //Hauteur de l'image
 
 //Fct pour calculer la partie réelle d'un nbr complexe à partir de la coordonnée x dans l'image
double cx( int x )
{
    /* -2 ---> 1 */
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 +  x * qx;
}
 //Fct pour calculer la partie réelle d'un nbr complexe à partir de la coordonnée y dans l'image
double cy( int y )
{
    /* -1 ---> 1 */
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}
		
struct col
{
    int r;
    int g;
    int b;
};
 
struct col getcol( int val , int max )
{
    double q = (double)val/(double)max;
 
    struct col c = { 0, 0, 0 };
 
    if( q < 0.25 )
    {
            c.r = ( q * 4.0 ) * 255.0;
            c.b = 255;
        }
    else if( q < 0.5 )
    {
            c.b = 255;
            c.g = 255;
            c.r = (q-0.25)*4.0*255.0;
 
        }
    else if( q < 0.75 )
    {
            c.b = 255;
            c.r = 255;
            c.g = 255.0 - (q-0.5)*4.0*255.0;
        }
    else
    {
            c.b = 255-(q-0.75)*4.0*255.0;
            c.g = 0;
            c.r = 255;
        }
 
    return c;
}

int main(int argc, char *argv[]) {
  struct ppm_image im;
  ppm_image_init(&im, SIZEX, SIZEY); //Initialise l'image avec les dimensions spécifiées

  int i, j;
  int colref = log(ITER); //Calcul de la référence de couleur basée sur le logarithme du nbr max d'itérations
  
  double trsh = TRSH; // TRSH => 2
  
  if(argc !=2){
	 printf("Using default thresHold :%f", trsh); 
	 }else{
		 trsh = atoi(argv[1]);
		 printf("using value %f",trsh);
		 }

for (i = 0; i < SIZEX; ++i) {
        for (j = 0; j < SIZEY; ++j) {
 
            unsigned long int iter = 0;
 
            double complex c =  cx(i) + cy(j) * I;//Définition d'un nbr complexe c en fct des coordonnées i et j
            double complex z = 0;
 
            while(iter < ITER)
            {
                double mod = cabs(z); //Calcul du module de z
				//Vérifie si le module de z dépasse le seuil de divergence
                if( trsh < mod )
                {
                    break;
                }
 
                z = z*z + c; //Mise à jour de z selon la formule du fractal de Mandelbrot
 
                iter++;
            }
 
            struct col cc = getcol( log(iter), colref );
            ppm_image_setpixel(&im, i,j, cc.r, cc.g , cc.b );
        }
    }

  ppm_image_dump(&im, "m.ppm"); //sauvegarde de l'image dans un fichier PPM
  ppm_image_release(&im); //Libération de la mémoire allouée pour l'image

  return 0;
}
