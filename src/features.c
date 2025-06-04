#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <estia-image.h>
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
















