#include <estia-image.h>
#include <stdio.h>

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
    int pixel2;
    int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *nbChannels);
    int write_image_data(const char *filename, unsigned char *data, int width, int height);
    pixelRGB* pixel2 = getPixel(2, 0);

    printf("second_line: %d\n", pixel2);
}

