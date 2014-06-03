//
//  fileio.c
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "utilities.h"
#include "global.h"


xcmd_object_t *io_read_input(const char *filepath)
{
    FILE *fp = NULL;
    if ((fp = fopen(filepath, "r")) == NULL) {
        return NULL;
    }
    
    xcmd_object_t *object = NULL;
    
    char buf[1024];
    char key[64];
    char val[256];
    float tx = 0.0;
    float ty = 0.0;
    float tz = 0.0;
    char atom[2];
    int k = 0;
    float temp = 0.0;
    int nsteps = 0;
    float steptime = 0.0;
    
    // First pass to get all the options.
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (buf[0] == '&' && sscanf(&buf[1], "%s %s", key, val) == 2) {
            if (strcmp(key, "ATOM_NUMBER") == 0) {
                object = xcmd_init_object(string_to_int(val, 10));
            } else if (strcmp(key, "TEMPERATURE") == 0) {
                temp = string_to_float(val);
            } else if (strcmp(key, "MD_STEPS") == 0) {
                nsteps = string_to_int(val, 10);
            } else if (strcmp(key, "MD_STEPTIME") == 0) {
                steptime = string_to_float(val);
            }
        }
    }
    rewind(fp);
    
    // Check
    if (object == NULL) {
        fprintf(xcmdout, "Error: the ATOM_NUMBER can not be found!\n");
        abort();
    }
    
    // Set the options for the MD simulation
    object->temp = temp;
    object->timestep = steptime;
    object->nsteps = nsteps;
    
    // Second pass to get the initial coordinates.
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (sscanf(buf, "%s %f %f %f", atom, &tx, &ty, &tz) == 4) {
            if (object == NULL) {
                fprintf(xcmdout, "");
            }
            object->px[k] = tx;
            object->py[k] = ty;
            object->pz[k] = tz;
            k ++;
        }
    }
    
    fclose(fp);
    return object;
}