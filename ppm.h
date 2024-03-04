#ifndef PPM_H
#define PPM_H

struct ppm_pixel {
  unsigned char r; //composant rouge du pixel
  unsigned char g;//composant vert du pixel
  unsigned char b;//composant bleu du pixel
};
//definition des valeurs RGB d'un pixel
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}
//structure dune image en pixel
struct ppm_image {
  unsigned int width; //la largeur de l'image en pixel
  unsigned int height; //la hauteur de l'image en pixel
  struct ppm_pixel *px; //pointeur vers un tableau et pixel dune image
};
//initialisation de l'mage avec les valeurs de sa largeur et hauteur
int ppm_image_init(struct ppm_image *im, int w, int h); 
//liberer la memoire reservée pour l'image
int ppm_image_release(struct ppm_image *im);

//definition des coordonnées d'un pixel dans une image
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

//sauvegarde le contenu de l'image
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */
