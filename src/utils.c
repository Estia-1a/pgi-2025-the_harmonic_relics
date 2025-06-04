#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <estia-image.h> // pour read_image_data et write_image_data
#include "utils.h"

/*
 * getPixel :
 *   - data          : tableau RAW (unsigned char*) retourné par read_image_data
 *   - width, height : dimensions de l’image
 *   - channel_count : nombre de canaux (3 = RGB, 4 = RGBA, …)
 *   - n             : indice linéaire du pixel [0 .. width*height - 1]
 * Retourne un pixelRGB (R,G,B) lu dans data.
 */
pixelRGB getPixel(const unsigned char *data,
                  unsigned int width,
                  unsigned int height,
                  unsigned int channel_count,
                  unsigned int n)
{
    pixelRGB px;
    /* Calcul de l’offset du pixel n :
       chaque pixel occupe channel_count octets dans data. */
    unsigned int base = n * channel_count;
    px.R = data[base + 0];
    px.G = data[base + 1];
    px.B = data[base + 2];
    return px;
}

/*
 * setPixel :
 *   - data          : tableau RAW (unsigned char*) retourné par read_image_data
 *   - width, height : dimensions de l’image
 *   - channel_count : nombre de canaux (3 = RGB, 4 = RGBA, …)
 *   - n             : indice linéaire du pixel [0 .. width*height - 1]
 *   - px            : struct pixelRGB (R,G,B) à écrire dans data
 */
void setPixel(unsigned char *data,
              unsigned int width,
              unsigned int height,
              unsigned int channel_count,
              unsigned int n,
              pixelRGB px)
{
    unsigned int base = n * channel_count;
    data[base + 0] = px.R;
    data[base + 1] = px.G;
    data[base + 2] = px.B;
    /* Si channel_count == 4 (RGBA), on ne touche pas au 4ᵉ canal (alpha). */
}

