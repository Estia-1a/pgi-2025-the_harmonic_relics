#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

/**
 * @brief Structure pour représenter un pixel RGB (3 composantes 0..255).
 */
typedef struct _pixelRGB {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} pixelRGB;

/**
 * @brief Récupère le n-ième pixel (par index linéaire) dans le tableau `data` renvoyé par Estia-Image.
 *
 * @param data          Pointeur sur les données brutes (unsigned char*) de l’image (read_image_data).
 * @param width         Largeur de l’image (en pixels).
 * @param height        Hauteur de l’image (en pixels).
 * @param channel_count Nombre de canaux par pixel (3 = RGB, 4 = RGBA,…).
 * @param n             Indice du pixel (linéaire, de 0 à width*height − 1).
 * @return pixelRGB     Struct contenant les composantes {R,G,B} du pixel n.
 */
pixelRGB getPixel(const unsigned char *data,
                  unsigned int width,
                  unsigned int height,
                  unsigned int channel_count,
                  unsigned int n);

/**
 * @brief Écrit un pixel RGB dans le tableau `data` renvoyé par Estia-Image.
 *
 * @param data          Pointeur sur les données brutes (unsigned char*) de l’image (read_image_data).
 * @param width         Largeur de l’image (en pixels).
 * @param height        Hauteur de l’image (en pixels).
 * @param channel_count Nombre de canaux par pixel (3 = RGB, 4 = RGBA,…).
 * @param n             Indice du pixel (linéaire, de 0 à width*height − 1).
 * @param px            Struct pixelRGB contenant les nouvelles composantes {R,G,B}.
 */
void setPixel(unsigned char *data,
              unsigned int width,
              unsigned int height,
              unsigned int channel_count,
              unsigned int n,
              pixelRGB px);

#endif /* UTILS_H */
