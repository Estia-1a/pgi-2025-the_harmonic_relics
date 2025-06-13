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

