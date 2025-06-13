#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) 
  {
    helloWorld();
  }
  if ( strncmp( configuration.command, "dimension", 9 ) == 0 ) {
    /* dimension() function is defined in feature.h and implemented in feature.c */
    dimension(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "first_pixel", 11 ) == 0 ) 
  {
    first_pixel(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "tenth_pixel", 11 ) == 0 ) 
  {
    tenth_pixel(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "second_line", 11 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    second_line(configuration.filenames[0]);
  }

  if ( strncmp( configuration.command, "color_red", 9 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    color_red(configuration.filenames[0]);
  }

    if ( strncmp( configuration.command, "color_green", 11 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    color_green(configuration.filenames[0]);
  }

    if ( strncmp( configuration.command, "color_blue", 10 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    color_blue(configuration.filenames[0]);
  }

    if ( strncmp( configuration.command, "color_gray", 10 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    color_gray(configuration.filenames[0]);
  }

     if ( strncmp( configuration.command, "color_invert", 12 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    color_invert(configuration.filenames[0]);
  }

  if ( strncmp( configuration.command, "color_gray_lumi", 15 ) == 0 ) {
    /* second_line() function is defined in feature.h and implemented in feature.c */
    color_gray_lumi(configuration.filenames[0]);
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
}
