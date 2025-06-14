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
  if ( strncmp( configuration.command, "dimension", 10 ) == 0 ) 
  {
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
  if ( strncmp( configuration.command, "second_line", 11 ) == 0 ) 
  {
    first_pixel(configuration.filenames[0]);
  }

  return 0;
}
