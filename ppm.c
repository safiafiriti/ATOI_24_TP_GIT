#include "ppm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////initialisation de l'image avec les valeurs de sa largeur et hauteur
int ppm_image_init(struct ppm_image *im, int w, int h) {
  memset(im, 0, sizeof(struct ppm_image)); //Initialise la structure de l'image à zéro

  im->width = w; //Initialisation la largeur de l'image
  im->height = h; //Initialisation de la hauteur de l'image
  
  //Allocation de la mémoire pour stocker les pixels de l'image
  im->px = malloc(w * h * sizeof(struct ppm_pixel));
  
  //Vérifie si l'allocation de mémoire a réussi
  if (!im->px) {
    perror("malloc");
    return 1;
  }

  return 0;
}

//Libereation de la memoire reservée pour l'image
int ppm_image_release(struct ppm_image *im) {
  if (im == NULL)
    return 1;

  free(im->px);
  im->px = NULL;

  im->width = 0;
  im->height = 0;

  return 0;
}

//Sauvegarde de l'image PPM dans un fichier
int ppm_image_dump(struct ppm_image *im, char *path) {
  FILE *out = fopen(path, "w");
  
  //Vérifie si l'ouverture du fichier a réussi
  if (!out) {
    perror("fopen");
    return 1;
  }

  fprintf(out, "P6\n"); //Ecrit l'en-tete du fichier PPM
  fprintf(out, "%d\n", im->width); //Ecrit la largeur de l'image
  fprintf(out, "%d\n", im->height); //Ecrit la hauteur de l'image
  fprintf(out, "255\n"); //Ecrit la valeur max de la couleur
  //Ecrit les pixels de l'image dqans le fichier
  fwrite(im->px, sizeof(struct ppm_pixel), im->width * im->height, out);

  fclose(out); //Ferme le fichier

  return 0;
}
