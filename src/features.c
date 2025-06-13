#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h> 
#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hellooo World !!!");
}

void dimension (char *source_path){
    int width,height,channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("dimension: %d, %d\n", width, height);
}

void first_pixel (char *source_path){
    int R,G,B;
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






