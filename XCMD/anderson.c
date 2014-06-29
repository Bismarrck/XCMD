//
//  anderson.c
//  XCMD
//
//  Created by Bismarrck on 6/29/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "motion.h"
#include "utilities.h"


/**
 * @function motion_anderson_thermostat_first
 * First update of equation of motion of anderson thermostat algorithm.
 */
void motion_anderson_thermostat_first(xcmd_object_t *md)
{
    float delt2 = md->timestep * md->timestep * 0.5;
    float delth = md->timestep * 0.5;
    for (int i = 0; i < md->nparticle; i ++) {
        md->px[i] += md->timestep * md->vx[i] + delt2 * md->fx[i];
        md->py[i] += md->timestep * md->vy[i] + delt2 * md->fy[i];
        md->pz[i] += md->timestep * md->vz[i] + delt2 * md->fz[i];
        md->vx[i] += delth * md->fx[i];
        md->vy[i] += delth * md->fy[i];
        md->vz[i] += delth * md->fz[i];
    }
}

/**
 * @function motion_anderson_thermostat_second
 * Second update of equation of motion of anderson thermostat algorithm.
 */
void motion_anderson_thermostat_second(xcmd_object_t *md)
{
    float delth = md->timestep * 0.5;
    float v2 = 0.0;
    for (int i = 0; i < md->nparticle; i ++) {
        md->vx[i] += delth * md->fx[i];
        md->vy[i] += delth * md->fy[i];
        md->vz[i] += delth * md->fz[i];
        v2 += pow(md->vx[i], 2.) + pow(md->vy[i], 2.) + pow(md->vz[i], 2.);
    }
    md->ekin = 0.5 * v2;
    float sigma = sqrt(md->temp);
    float thres = md->timestep * md->nu;
    for (int i = 0; i < md->nparticle; i ++) {
        if (random_uniform() < thres) {
            md->vx[i] = gauss(sigma);
            md->vy[i] = gauss(sigma);
            md->vz[i] = gauss(sigma);
        }
    }
}
