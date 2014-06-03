//
//  global.c
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include "global.h"

// Declaration of xcmdout
FILE *xcmdout = NULL;


/**
 * @function xcmd_global_init
 * Init the globale variables and functions.
 */
void xcmd_global_init(const char *filepath)
{
    if (xcmdout == NULL) {
        xcmdout = fopen(filepath, "w+");
    } else {
        fprintf(xcmdout, "Error: the global outstream has been initialized!\n");
    }
}


/**
 * @function xcmd_global_finalize
 * Finalize all the global variables and functions.
 */
void xcmd_global_finalize(void)
{
    fflush(xcmdout);
    fclose(xcmdout);
}