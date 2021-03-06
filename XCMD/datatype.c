//
//  datatype.c
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "datatype.h"

xcmd_object_t *xcmd_init_object(int nparticles)
{
    xcmd_object_t *object = malloc(sizeof(xcmd_object_t));
    
    object->nparticle = nparticles;
    object->temp = 0.0;
    object->timestep = 1.0;
    object->nsteps = 10;
    object->ekin = 0.0;
    object->epot = 0.0;
    object->epsilon = 0.0;
    object->etot = 0.0;
    object->sigma = 0.0;
    object->rc2 = 0.0;
    object->box = 0.0;
    object->ecut = 0.0;
    object->virial = 0.0;
    object->fx = calloc(sizeof(float), nparticles);
    object->fy = calloc(sizeof(float), nparticles);
    object->fz = calloc(sizeof(float), nparticles);
    object->px = calloc(sizeof(float), nparticles);
    object->py = calloc(sizeof(float), nparticles);
    object->pz = calloc(sizeof(float), nparticles);
    object->vx = calloc(sizeof(float), nparticles);
    object->vy = calloc(sizeof(float), nparticles);
    object->vz = calloc(sizeof(float), nparticles);
    object->vout = NULL;
    object->fout = NULL;
    object->pout = NULL;
    object->outfreq = 5;
    object->scale = true;
    object->nu = 1.0;
    
    return object;
}


void xcmd_object_release(xcmd_object_t *object)
{
    if (object == NULL) {
        return;
    }
    
    if (object->fx) {
        free(object->fx);
    }
    
    if (object->fy) {
        free(object->fy);
    }
    
    if (object->fz) {
        free(object->fz);
    }
    
    if (object->px) {
        free(object->px);
    }
    
    if (object->py) {
        free(object->py);
    }
    
    if (object->pz) {
        free(object->pz);
    }
    
    if (object->vx) {
        free(object->vx);
    }
    
    if (object->vy) {
        free(object->vy);
    }
    
    if (object->vz) {
        free(object->vz);
    }
    
    if (object->pout) {
        fflush(object->pout);
        fclose(object->pout);
    }
    
    if (object->vout) {
        fflush(object->vout);
        fclose(object->vout);
    }
    
    if (object->fout) {
        fflush(object->fout);
        fclose(object->fout);
    }
        
    free(object);
}