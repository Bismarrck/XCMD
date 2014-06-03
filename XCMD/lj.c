//
//  lj.c
//  XCMD
//
//  Created by Bismarrck on 6/3/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "potential.h"
#include "force.h"


void potential_lenard_jones(xcmd_object_t *md)
{
    float epot = 0.0;
    float vir = 0.0;
    float xi = 0.0;
    float yi = 0.0;
    float zi = 0.0;
    float dx = 0.0;
    float dy = 0.0;
    float dz = 0.0;
    float r2 = 0.0;
    float r2i = 0.0;
    float r6i = 0.0;
    float box = md->box;
    float rc2 = md->rc2;
    float sigma = md->sigma;
    float epsilon = md->epsilon;
    float s6 = powf(sigma, 6);
    float s12 = s6 * s6;
    float ecut = md->ecut;
    
    for (int i = 0; i < md->nparticle; i ++) {
        xi = md->px[i];
        yi = md->py[i];
        zi = md->pz[i];
        for (int j = i + 1; j < md->nparticle; j ++) {
            dx = xi - md->px[j];
            dy = yi - md->py[j];
            dz = zi - md->pz[j];
            
            // Periodic Boundary Conditions
            dx -= box * floorf(dx / box);
            dy -= box * floorf(dy / box);
            dz -= box * floorf(dz / box);
            r2 = dx * dx + dy * dy + dz * dz;
            if (r2 < rc2) {
                r2i = 1.0 / r2;
                r6i = r2i * r2i * r2i;
                epot += 4.0 * epsilon * (s12 * r6i * r6i - s6 * r6i) - ecut;
                vir += 48.0 * epsilon * (s12 * r6i * r6i - 0.5 * s6 * r6i);
            }
        }
    }
    
    md->epot = epot;
    md->virial = vir;
}


void force_lenard_jones(xcmd_object_t *md)
{
    
}
