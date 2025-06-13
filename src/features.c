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


