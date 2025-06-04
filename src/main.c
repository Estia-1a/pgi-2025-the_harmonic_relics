#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
    /* ------------------ NE PAS MODIFIER CETTE PARTIE ------------------ */
    Config configuration;
    parse_arguments(argc, argv, &configuration);
    check_debug_mode(configuration);
    check_file();
    /* ------------------------------------------------------------------ */

    if (strncmp(configuration.command, "helloworld", 10) == 0) {
        helloWorld();
    }
    else if (strncmp(configuration.command, "dimension", 9) == 0) {
        dimension(configuration.filenames[0]);
    }
    else if (strncmp(configuration.command, "first_pixel", 11) == 0) {
        first_pixel(configuration.filenames[0]);
    }
    else if (strncmp(configuration.command, "tenth_pixel", 11) == 0) {
        tenth_pixel(configuration.filenames[0]);
    }
    /* ---- NOUVEAU : appel de color_desaturate si l’utilisateur a passé -c color_desaturate ---- */
    else if (strncmp(configuration.command, "color_desaturate", 15) == 0) {
        /* On suppose que le chemin de l’image est dans filenames[0] */
        color_desaturate(configuration.filenames[0]);
    }
    /* ------------------------------------------------------------------ */
    else {
        fprintf(stderr, "Commande inconnue : '%s'\n", configuration.command);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

