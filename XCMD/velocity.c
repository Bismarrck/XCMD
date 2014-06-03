//
//  velocity.c
//  XCMD
//
//  Created by Bismarrck on 6/3/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "velocity.h"
#include "utilities.h"

/**
 * @function velocity_init_random
 * Init the velocities for each atom in the MD system with simple random
 * distribution.
 *
 * @see Understanding Molecular Simulation, 4.1.1, 4.1.2, 4.2.1, 4.2.2
 */
void velocity_init_random(xcmd_object_t *md)
{
    float vx0 = 0.0;
    float vy0 = 0.0;
    float vz0 = 0.0;
    float vv2 = 0.0;
    float vxt = 0.0;
    float vyt = 0.0;
    float vzt = 0.0;
    float f = 0.0;
    float temp = md->temp;
    
    // Give each atom a random velocity
    for (int i = 0; i < md->nparticle; i ++) {
        md->vx[i] = random_uniform() - 0.5;
        md->vy[i] = random_uniform() - 0.5;
        md->vz[i] = random_uniform() - 0.5;
        vx0 += md->vx[i];
        vy0 += md->vy[i];
        vz0 += md->vz[i];
        vv2 += powf(md->vx[i], 2) + powf(md->vy[i], 2) + powf(md->vz[i], 2);
    }
    
    // Set centre of mass movement to zero
    vx0 /= md->nparticle;
    vy0 /= md->nparticle;
    vz0 /= md->nparticle;
    f = sqrtf(3.0 * md->nparticle * temp / vv2);
    vv2 = 0.0;
    for (int i = 0; i < md->nparticle; i ++) {
        md->vx[i] = (md->vx[i] - vx0) * f;
        md->vx[i] = (md->vy[i] - vy0) * f;
        md->vx[i] = (md->vz[i] - vz0) * f;
        vxt += md->vx[i];
        vyt += md->vy[i];
        vzt += md->vz[i];
        vv2 += powf(md->vx[i], 2) + powf(md->vy[i], 2) + powf(md->vz[i], 2);
    }
    vv2 /= (3.0 * md->nparticle);
    
    // Save the initial temperature.
    md->temp = vv2;
    
    // Save the velocity centre of mass.
    md->vxt = vxt / md->nparticle;
    md->vyt = vyt / md->nparticle;
    md->vzt = vzt / md->nparticle;
}


/**
 * @function velocity_init_boltzman
 * Init the velocities for each atom in the MD system with Maxwell-Boltzmann
 * distribution.
 *
 * @warning Not implemented yet!
 */
void velocity_init_boltzmann(xcmd_object_t *object)
{
    
}

