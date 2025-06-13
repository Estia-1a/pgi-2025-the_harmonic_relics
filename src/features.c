#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>
#include "features.h"
#include "utils.h"

/* ----------------------------------------------------------------------
   Les fonctions hellowWorld, dimension, first_pixel et tenth_pixel que
   tu avais déjà, éventuellement avec l’ajout de free(data) pour éviter
   les fuites de mémoire. Je les remets ici pour que tu vois la cohérence.
   Tu peux coller exactement ce qui suit dans ton fichier features.c,
   en remplaçant tout ce qui existait auparavant.
   ---------------------------------------------------------------------- */

/**
 * Exemple trivial : affiche "Hellooo World !!!"
 */
void helloWorld() {
    printf("Hellooo World !!!\n");
}

/**
 * Lit l’image source, affiche width × height, puis libère la mémoire.
 */
void dimension(char *source_path) {
    int width, height, channel_count;
    unsigned char *data = NULL;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        fprintf(stderr, "Erreur: lecture impossible de '%s'\n", source_path);
        return;
    }

    printf("dimension: %d, %d\n", width, height);

    free(data);
}

/**
 * Lit l’image source, affiche le premier pixel (index 0), puis libère la mémoire.
 */
void first_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data = NULL;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        fprintf(stderr, "Erreur: lecture impossible de '%s'\n", source_path);
        return;
    }

    /* Le premier pixel commence à data[0..2] */
    int R = data[0];
    int G = data[1];
    int B = data[2];
    printf("first_pixel: %d, %d, %d\n", R, G, B);

    free(data);
}

/**
 * Lit l’image source, affiche le dixième pixel (index 9),
 * donc composantes R= data[9*channel_count + 0], etc., puis libère.
 */
void tenth_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data = NULL;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        fprintf(stderr, "Erreur: lecture impossible de '%s'\n", source_path);
        return;
    }

    /* Le dixième pixel (index 9) commence à data[9 * channel_count] */
    int base = 9 * channel_count;
    int R = data[base + 0];
    int G = data[base + 1];
    int B = data[base + 2];
    printf("tenth_pixel: %d, %d, %d\n", R, G, B);

    free(data);
}

/* ----------------------------------------------------------------------
   À PARTIR D’ICI, C’EST LA FONCTION color_desaturate À COPIER TELLE QUELLE
   ---------------------------------------------------------------------- */

/**
 * @brief Lit l’image source, désature chaque pixel (min+max)/2, puis écrit
 *        le résultat sous forme d’un BMP 24 bits nommé "image_out.bmp".
 */
void color_desaturate(char *source_path) {
    int width, height, channel_count;
    unsigned char *data = NULL;

    /* 1) Lecture de l’image source */
    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        fprintf(stderr, "Erreur : impossible de lire image '%s'\n", source_path);
        return;
    }

    /* 2) Nombre total de pixels = width * height */
    unsigned int total_pixels = (unsigned int)width * (unsigned int)height;

    /* 3) Parcourir chaque pixel en indice linéaire n [0 .. total_pixels-1] */
    for (unsigned int n = 0; n < total_pixels; ++n) {
        /* a) Récupérer le pixel n en RGB */
        pixelRGB px = getPixel(data,
                               (unsigned int)width,
                               (unsigned int)height,
                               (unsigned int)channel_count,
                               n);

        /* b) Calculer le minimum des trois composantes R,G,B */
        unsigned char mn = px.R;
        if (px.G < mn) mn = px.G;
        if (px.B < mn) mn = px.B;

        /* c) Calculer le maximum des trois composantes R,G,B */
        unsigned char mx = px.R;
        if (px.G > mx) mx = px.G;
        if (px.B > mx) mx = px.B;

        /* d) Nouvelle valeur en niveaux de gris = (mn + mx)/2 */
        unsigned char new_val = (unsigned char)(((unsigned int)mn + (unsigned int)mx) / 2);

        /* e) Affecter R=G=B=new_val */
        px.R = new_val;
        px.G = new_val;
        px.B = new_val;

        /* f) Écrire ce pixel modifié dans le tableau data */
        setPixel(data,
                 (unsigned int)width,
                 (unsigned int)height,
                 (unsigned int)channel_count,
                 n,
                 px);
    }

    /* 4) Écrire l’image désaturée dans un fichier "image_out.bmp" */
    const char *out_name = "image_out.bmp";
    if (write_image_data(out_name, data, width, height) == 0) {
        fprintf(stderr, "Erreur : impossible d'écrire '%s'\n", out_name);
        free(data);
        return;
    }

    printf("Désaturation terminée. Image écrite dans '%s'.\n", out_name);

    /* 5) Libérer la mémoire allouée par read_image_data */
    free(data);
}


void rotate_cw(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        printf("La lecture de l'image a echoue\n");
        return;
    }

    int new_width = height;
    int new_height = width;

    unsigned char *rotated = malloc(width * height * channel_count);
    if (!rotated) {
        printf("Erreur d'allocation mémoire\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_index = (y * width + x) * channel_count + c;
                int dst_index = (x * new_height + (new_height - 1 - y)) * channel_count + c;
                rotated[dst_index] = data[src_index];
            }
        }
    }

    if (write_image_data("image_out.bmp", rotated, new_width, new_height) == 0) {
        printf("Erreur lors de l’ecriture de l’image\n");
    } else {
        printf("Image tournee enregistree sous image_out.bmp\n");
    }

    free(data);
    free(rotated);
}

void rotate_acw(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) != 0) {
        printf("La lecture de l'image a échoué\n");
        return;
    }

    int new_width = height;
    int new_height = width;
    unsigned char *rotated = malloc(width * height * channel_count);
    if (!rotated) {
        printf("Erreur d'allocation mémoire\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_index = (y * width + x) * channel_count + c;
                int dst_index = ((width - 1 - x) * new_width + y) * channel_count + c;
                rotated[dst_index] = data[src_index];
            }
        }
    }

    if (write_image_data("image_out.bmp", rotated, new_width, new_height) != 0) {
        printf("Erreur lors de l’écriture de l’image\n");
    } else {
        printf("Image tournée anti-horaire enregistrée sous image_out.bmp\n");
    }

    free(data);
    free(rotated);
}

void mirror_total(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur : lecture de l'image échouee\n");
        return;
    }

    unsigned char *mirrored = malloc(width * height * channel_count);
    if (!mirrored) {
        printf("Erreur d'allocation memoire\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_index = (y * width + x) * channel_count + c;
                int dst_index = ((height - 1 - y) * width + (width - 1 - x)) * channel_count + c;
                mirrored[dst_index] = data[src_index];
            }
        }
    }

    if (write_image_data("image_out.bmp", mirrored, width, height) == 0) {
        printf("Erreur lors de l’ecriture de l’image miroir\n");
    } else {
        printf("Image miroir enregistree sous image_out.bmp\n");
    }

    free(data);
    free(mirrored);
}

void second_line(char *source_path){
    int R, G, B;
    int width,height,channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    R = data[3 * width];
    G = data[3 * width + 1];
    B = data[3 * width + 2];

    printf("second_line: %d, %d, %d\n", R, G, B);
}

void color_red(char *source_path){
    int width,height,channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    R=data[0];
    G=data[1];
    B=data[2];
    printf("first_pixel: %d, %d, %d\n", R, G, B);
}

void tenth_pixel (char *source_path){
    int R,G,B;
    int width,height,channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    R=data[27];
    G=data[28];
    B=data[29];
    printf("tenth_pixel: %d, %d, %d\n", R, G, B);

    free(data);
}

/* ----------------------------------------------------------------------
   À PARTIR D’ICI, C’EST LA FONCTION color_desaturate À COPIER TELLE QUELLE
   ---------------------------------------------------------------------- */

/**
 * @brief Lit l’image source, désature chaque pixel (min+max)/2, puis écrit
 *        le résultat sous forme d’un BMP 24 bits nommé "image_out.bmp".
 */
void color_desaturate(char *source_path) {
    int width, height, channel_count;
    unsigned char *data = NULL;

    /* 1) Lecture de l’image source */
    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        fprintf(stderr, "Erreur : impossible de lire image '%s'\n", source_path);
        return;
    }

    /* 2) Nombre total de pixels = width * height */
    unsigned int total_pixels = (unsigned int)width * (unsigned int)height;

    /* 3) Parcourir chaque pixel en indice linéaire n [0 .. total_pixels-1] */
    for (unsigned int n = 0; n < total_pixels; ++n) {
        /* a) Récupérer le pixel n en RGB */
        pixelRGB px = getPixel(data,
                               (unsigned int)width,
                               (unsigned int)height,
                               (unsigned int)channel_count,
                               n);

        /* b) Calculer le minimum des trois composantes R,G,B */
        unsigned char mn = px.R;
        if (px.G < mn) mn = px.G;
        if (px.B < mn) mn = px.B;

        /* c) Calculer le maximum des trois composantes R,G,B */
        unsigned char mx = px.R;
        if (px.G > mx) mx = px.G;
        if (px.B > mx) mx = px.B;

        /* d) Nouvelle valeur en niveaux de gris = (mn + mx)/2 */
        unsigned char new_val = (unsigned char)(((unsigned int)mn + (unsigned int)mx) / 2);

        /* e) Affecter R=G=B=new_val */
        px.R = new_val;
        px.G = new_val;
        px.B = new_val;

        /* f) Écrire ce pixel modifié dans le tableau data */
        setPixel(data,
                 (unsigned int)width,
                 (unsigned int)height,
                 (unsigned int)channel_count,
                 n,
                 px);
    }

    /* 4) Écrire l’image désaturée dans un fichier "image_out.bmp" */
    const char *out_name = "image_out.bmp";
    if (write_image_data(out_name, data, width, height) == 0) {
        fprintf(stderr, "Erreur : impossible d'écrire '%s'\n", out_name);
        free(data);
        return;
    }

    printf("Désaturation terminée. Image écrite dans '%s'.\n", out_name);

    /* 5) Libérer la mémoire allouée par read_image_data */
    free(data);
}


void rotate_cw(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        printf("La lecture de l'image a echoue\n");
        return;
    }

    int new_width = height;
    int new_height = width;

    unsigned char *rotated = malloc(width * height * channel_count);
    if (!rotated) {
        printf("Erreur d'allocation mémoire\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_index = (y * width + x) * channel_count + c;
                int dst_index = (x * new_height + (new_height - 1 - y)) * channel_count + c;
                rotated[dst_index] = data[src_index];
            }
        }
    }

    if (write_image_data("image_out.bmp", rotated, new_width, new_height) == 0) {
        printf("Erreur lors de l’ecriture de l’image\n");
    } else {
        printf("Image tournee enregistree sous image_out.bmp\n");
    }

    free(data);
    free(rotated);
}

void rotate_acw(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) != 0) {
        printf("La lecture de l'image a échoué\n");
        return;
    }

    int new_width = height;
    int new_height = width;
    unsigned char *rotated = malloc(width * height * channel_count);
    if (!rotated) {
        printf("Erreur d'allocation mémoire\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_index = (y * width + x) * channel_count + c;
                int dst_index = ((width - 1 - x) * new_width + y) * channel_count + c;
                rotated[dst_index] = data[src_index];
            }
        }
    }

    if (write_image_data("image_out.bmp", rotated, new_width, new_height) != 0) {
        printf("Erreur lors de l’écriture de l’image\n");
    } else {
        printf("Image tournée anti-horaire enregistrée sous image_out.bmp\n");
    }

    free(data);
    free(rotated);
}

void mirror_total(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur : lecture de l'image échouee\n");
        return;
    }

    unsigned char *mirrored = malloc(width * height * channel_count);
    if (!mirrored) {
        printf("Erreur d'allocation memoire\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_index = (y * width + x) * channel_count + c;
                int dst_index = ((height - 1 - y) * width + (width - 1 - x)) * channel_count + c;
                mirrored[dst_index] = data[src_index];
            }
        }
    }

    if (write_image_data("image_out.bmp", mirrored, width, height) == 0) {
        printf("Erreur lors de l’ecriture de l’image miroir\n");
    } else {
        printf("Image miroir enregistree sous image_out.bmp\n");
    }

    free(data);
    free(mirrored);
}

void second_line(char *source_path){
    int R, G, B;
    int width,height,channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    R = data[3 * width];
    G = data[3 * width + 1];
    B = data[3 * width + 2];

    printf("second_line: %d, %d, %d\n", R, G, B);
}

void color_red(char *source_path){
    int width,height,channel_count;
    unsigned char *data;

    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result == 0) {
        printf("Erreur lors de la lecture de l-image : %s\n", source_path);
        return;
    }
    int i, total_pixels = width * height;
    printf("nombre de pixel : %d\n", total_pixels);
    for (i = 0; i < total_pixels; i++) {
    
         data[i * 3 + 1] = 0;
         data[i * 3 + 2] = 0;
       
    }
    write_image_data("image_out.bmp", data, width, height);

    free(data);

}

void color_green (char *source_path){
    int width,height,channel_count;
    unsigned char *data;

    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result == 0) {
        printf("Erreur lors de la lecture de l-image : %s\n", source_path);
        return;
    }

    int i, total_pixels = width * height;
    for (i = 0; i < total_pixels; i++) {
    
         data[i * 3 ] = 0;
         data[i * 3 + 2] = 0;
       
    }

    write_image_data("image_out.bmp", data, width, height);

    free(data);

}

void color_blue (char *source_path){
    int width,height,channel_count;
    unsigned char *data;

    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result == 0) {
        printf("Erreur lors de la lecture de l-image : %s\n", source_path);
        return;
    }

    int i, total_pixels = width * height;
    for (i = 0; i < total_pixels; i++) {
    
         data[i * 3 ] = 0;
         data[i * 3 + 1] = 0;
       
    }

    write_image_data("image_out.bmp", data, width, height);

    free(data);

}

void color_gray (char *source_path){
    int width,height,channel_count,R,G,B;
    unsigned char *data;

    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result == 0) {
        printf("Erreur lors de la lecture de l-image : %s\n", source_path);
        return;
    }

    int i, total_pixels = width * height;
    for (i = 0; i < total_pixels; i++) {
    
         R = data[i * 3 ];
         G = data[i * 3 + 1];
         B = data[i * 3 + 2];

         data[i * 3 ] = (R + G + B) / 3 ;
         data[i * 3 + 1] = (R + G + B) / 3 ;
         data[i * 3 + 2] = (R + G + B) / 3 ;
       
    }

    write_image_data("image_out.bmp", data, width, height);

    free(data);

}

void color_invert (char *source_path){
    int width,height,channel_count,R,G,B;
    unsigned char *data;

    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result == 0) {
        printf("Erreur lors de la lecture de l-image : %s\n", source_path);
        return;
    }

    int i, total_pixels = width * height;
    for (i = 0; i < total_pixels; i++) {
    
         R = data[i * 3 ];
         G = data[i * 3 + 1];
         B = data[i * 3 + 2];

         data[i * 3 ] = 255 - R;
         data[i * 3 + 1] = 255 - G;
         data[i * 3 + 2] = 255 - B;
       
    }

    write_image_data("image_out.bmp", data, width, height);

    free(data);

}

void color_gray_lumi (char *source_path){
    int width,height,channel_count,R,G,B,moy;
    unsigned char *data;

    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result == 0) {
        printf("Erreur lors de la lecture de l-image : %s\n", source_path);
        return;
    }

    int i, total_pixels = width * height;
    for (i = 0; i < total_pixels; i++) {
    
         R = data[i * 3 ];
         G = data[i * 3 + 1];
         B = data[i * 3 + 2];

         moy = (R * 0.21 + G * 0.72 + B * 0.07);

        data[i * 3 ] = moy ;
        data[i * 3 + 1] = moy ;
        data[i * 3 + 2] =  moy ;
       
    }

    write_image_data("image_out.bmp", data, width, height);

    free(data);

}

/*void max_pixel(Image *img)
{
    int max_sum = -1;
    int max_x = 0, max_y = 0;

    for (int y = 0; y < img->height; y++) 
    {
        for (int x = 0; x < img->width; x++) 
        {
            pixelRGB px = img->pixels[y * img->width + x];
            int sum = px.r + px.g + px.b;

            if (sum > max_sum) 
            {
                max_sum = sum;
                max_x = x;
                max_y = y;
            }
        }
    }

    pixelRGB result = img->pixels[max_y * img->width + max_x];
    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, result.r, result.g, result.b);
}
void min_pixel(Image *img) {
    int min_sum = 256 * 3 + 1;
    int min_x = 0, min_y = 0;

    for (int y = 0; y < img->height; y++) 
    {
        for (int x = 0; x < img->width; x++) 
        {
            pixelRGB px = img->pixels[y * img->width + x];
            int sum = px.r + px.g + px.b;

            if (sum < min_sum) 
            {
                min_sum = sum;
                min_x = x;
                min_y = y;
            }
        }
    }

    pixelRGB result = img->pixels[min_y * img->width + min_x];
    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, result.r, result.g, result.b);
}

 int main(int argc, char *argv[]) 
  {
    if (argc < 2) 
    {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    Image img;

    if (read_image_data(filename, &img) != 0) 
    {
        fprintf(stderr, "Erreur de chargement de l'image\n");
        return 1;
    }

    max_pixel(&img);

if (strcmp(command, "min_pixel") == 0) 
{
    min_pixel(&img);
}

  return 0;
}*/


