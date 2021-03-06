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
#include <math.h>
#include "fileio.h"
#include "utilities.h"
#include "global.h"

/* Simulation Input Options */
static const char *MD_KEYS[] =
{
    "MD_ATOM_NUM",
    "MD_TEMPERATURE",
    "MD_MAX_STEPS",
    "MD_TIMESTEP",
    "MD_BOX",
    "MD_EQUIL_TIME",
    "MD_SIGMA",
    "MD_EPSILON",
    "MD_NU",
    "MD_CUTOFF",
    "MD_FOUT",
    "MD_VOUT",
    "MD_POUT"
};

#define MD_ATOM_NUM     0
#define TEMPERATURE     1
#define MD_MAX_STEPS    2
#define MD_TIMESTEP     3
#define MD_BOX          4
#define MD_EQUIL_TIME   5
#define MD_SIGMA        6
#define MD_EPSILON      7
#define MD_NU           8
#define MD_CUTOFF       9
#define MD_FOUT         10
#define MD_VOUT         11
#define MD_POUT         12



/**
 * @function _io_remove_file
 * @private Remove the file if it is existed.
 */
void _io_remove_file(char *filepath)
{
    if (isFileExists(filepath)) {
        remove(filepath);
    }
}


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
    float box = 0.0;
    float equiltime = 0.0;
    float sigma = 0.0;
    float epsilon = 0.0;
    float cutoff = 0.0;
    float nu = 0.0;
    char *fout = NULL;
    char *vout = NULL;
    char *pout = NULL;
    
    // First pass to get all the options.
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (buf[0] == '&' && sscanf(&buf[1], "%s %s", key, val) == 2) {
            if (strcmp(key, MD_KEYS[MD_ATOM_NUM]) == 0) {
                object = xcmd_init_object(string_to_int(val, 10));
            } else if (strcmp(key, MD_KEYS[TEMPERATURE]) == 0) {
                temp = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_MAX_STEPS]) == 0) {
                nsteps = string_to_int(val, 10);
            } else if (strcmp(key, MD_KEYS[MD_TIMESTEP]) == 0) {
                steptime = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_BOX]) == 0) {
                box = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_EQUIL_TIME]) == 0) {
                equiltime = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_SIGMA]) == 0) {
                sigma = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_EPSILON]) == 0) {
                epsilon = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_NU]) == 0) {
                nu = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_CUTOFF]) == 0) {
                cutoff = string_to_float(val);
            } else if (strcmp(key, MD_KEYS[MD_POUT]) == 0) {
                pout = strdup(val);
            } else if (strcmp(key, MD_KEYS[MD_VOUT]) == 0) {
                vout = strdup(val);
            } else if (strcmp(key, MD_KEYS[MD_FOUT]) == 0) {
                fout = strdup(val);
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
    object->epsilon = epsilon;
    object->box = box;
    object->sigma = sigma;
    object->tequil = equiltime;
    object->nu = nu;
    
    // Calculate the cutoff energy
    float hbox = 0.5 * box;
    float rc = hbox < cutoff ? hbox : cutoff;
    object->rc2 = rc * rc;
    object->ecut = 4.0 * epsilon * (pow(sigma/rc, 12.0) - pow(sigma/rc, 6.0));
    
    // Open the three output FILE streams.
    _io_remove_file(pout);
    object->pout = fopen(pout, "a+");
    if (object->pout == NULL) {
        fprintf(xcmdout, "Failed to create file %s.\n", pout);
        abort();
    }
    free(pout);
    
    _io_remove_file(fout);
    object->fout = fopen(fout, "a+");
    if (object->fout == NULL) {
        fprintf(xcmdout, "Failed to create file %s.\n", fout);
        abort();
    }
    free(fout);
    
    _io_remove_file(vout);
    object->vout = fopen(vout, "a+");
    if (object->vout == NULL) {
        fprintf(xcmdout, "Failed to create file %s.\n", vout);
        abort();
    }
    free(vout);
    
    // Second pass to get the initial coordinates.
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (sscanf(buf, "%s %f %f %f", atom, &tx, &ty, &tz) == 4) {
            object->px[k] = tx;
            object->py[k] = ty;
            object->pz[k] = tz;
            k ++;
        }
    }
    
    fclose(fp);
    return object;
}


/**
 * @function _io_output
 * Write the 3D vectors to the given file.
 *
 * @private This is a private function!
 *
 * @param f     the given file pointer.
 * @param step  the current step.
 * @param s     the associated string to be written to the file.
 * @param x     the x data.
 * @param y     the y data.
 * @param z     the z data.
 * @param N     the total number of atoms.
 */
void _io_output(FILE *f, int step, char *s, float *x, float *y, float *z, int N)
{
    fprintf(f, "Step = %3d\n", step);
    fprintf(f, "%s\n", s);
    for (int i = 0; i < N; i ++) {
        fprintf(f, "Ar % 12.6f    % 12.6f    % 12.6f\n", x[i], y[i], z[i]);
    }
}


/**
 * @function io_output_velocity
 * Write the current velocities to vout.
 */
void io_output_velocity(xcmd_object_t *md, int step)
{
    char *s = "Velocity";
    _io_output(md->vout, step, s, md->vx, md->vy, md->vz, md->nparticle);
}


/**
 * @function io_output_force
 * Write the current forces to fout.
 */
void io_output_force(xcmd_object_t *md, int step)
{
    char *s = "Force";
    _io_output(md->fout, step, s, md->fx, md->fy, md->fz, md->nparticle);
}


/**
 * @function io_output_coordinate
 * Write the current coordinates to pout.
 */
void io_output_coordinate(xcmd_object_t *md, int step)
{
    char *s = "Coordinates";
    _io_output(md->pout, step, s, md->px, md->py, md->pz, md->nparticle);
}

