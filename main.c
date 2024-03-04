#include "ppm.h"
 
 
int main(int argc, char *argv[])
{
    struct ppm_image im;
 
    ppm_image_init( &im, 1024, 1024 ); //Initialise l'image avec une résolution de 1024*1024 pixels
 
    int i,j;
 
    for (i = 0; i < 1024; ++i) {
        for (j = 0; j < 1024; ++j) {
			//Définition la couleur du pixel en fct de ses coordonnées et de valeurs module
            ppm_image_setpixel( &im, i, j, i%255, j%255, (i+j)%255);
        }
    }
	
    for (i = 0; i < 1024; ++i) {
        ppm_image_setpixel( &im, i, i, 255, 0, 0 ); //Définition des pixels sur la diagonale en rouge
    }
	
	//sauvegarde l'image dans un fichier nommé "test.ppm"
    ppm_image_dump( &im , "test.ppm");
 
	//Libération de la mémoire allouée pour l'image
    ppm_image_release( &im );
 
 
    return 0;
}
