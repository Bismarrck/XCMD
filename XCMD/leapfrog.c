//
//  leapfrog.c
//  XCMD
//
//  Created by Bismarrck on 6/3/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "motion.h"

/**
 * @function motion_leapfrog
 * Solve the equation of motion using leap frog algorithm.
 */
void motion_leapfrog(xcmd_object_t *md)
{
    float vv2 = 0.0;
    float pvx = 0.0;
    float pvy = 0.0;
    float pvz = 0.0;
    for (int i = 0; i < md->nparticle; i ++) {
        pvx = md->vx[i];
        pvy = md->vy[i];
        pvz = md->vz[i];
        md->vx[i] += md->timestep * md->fx[i];
        md->vy[i] += md->timestep * md->fy[i];
        md->vz[i] += md->timestep * md->fz[i];
        md->px[i] += md->timestep * md->vx[i];
        md->py[i] += md->timestep * md->vy[i];
        md->pz[i] += md->timestep * md->vz[i];
        vv2 += powf(md->vx[i] + pvx, 2) + powf(md->vy[i] + pvy, 2);
        vv2 += powf(md->vz[i] + pvz, 2);
        vv2 *= 0.25;
    }
    md->ekin = vv2 * 0.5;
}