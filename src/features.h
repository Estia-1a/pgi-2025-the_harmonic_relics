#ifndef FEATURES_H
#define FEATURES_H

/**
 * Affiche simplement "Hellooo World !!!"
 */
void helloWorld();

/**
 * Affiche la largeur et la hauteur de l’image source indiquée par source_path.
 */
void dimension(char *source_path);

/**
 * Affiche la valeur (R,G,B) du premier pixel (pixel index 0) de l’image source.
 */
void first_pixel(char *source_path);

/**
 * Affiche la valeur (R,G,B) du dixième pixel (pixel index 9, c’est-à-dire 
 * le 10ᵉ pixel) de l’image source.
 */
void tenth_pixel(char *source_path);

/**
 * @brief Désature chaque pixel de l’image source selon la formule (min(R,G,B) + max(R,G,B)) / 2,
 *        puis écrit le résultat en sortie dans un fichier "image_out.bmp" (bitmap 24 bits).
 * @param source_path Chemin vers le fichier image d’entrée (supporté par Estia-Image).
 */
void color_desaturate(char *source_path);

#endif /* FEATURES_H */
