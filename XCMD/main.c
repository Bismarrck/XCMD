//
//  main.c
//  XCMD
//
//  Created by Bismarrck on 5/20/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "fileio.h"
#include "force.h"
#include "potential.h"
#include "velocity.h"
#include "motion.h"


void xcmd_energy_update(xcmd_object_t *md)
{
    md->etot = md->ekin + md->epot;
}

void rdf_init(xcmd_object_t *md)
{
    md->ngr = 0;
    md->deltg = md->box / (2.0 * md->nbin);
    md->gr = calloc(sizeof(float), md->nbin);
}

void rdf_sample(xcmd_object_t *md)
{
    float xi = 0.0;
    float yi = 0.0;
    float zi = 0.0;
    float dx = 0.0;
    float dy = 0.0;
    float dz = 0.0;
    float r2 = 0.0;
    float box = md->box;
    float b2 = box * box;
    int ig = 0;
    
    md->ngr ++;
    for (int i = 0; i < md->nparticle - 1; i ++) {
        xi = md->px[i];
        yi = md->py[i];
        zi = md->pz[i];
        for (int j = i + 1; j < md->nparticle; j ++) {
            dx = xi - md->px[j];
            dy = yi - md->py[j];
            dz = zi - md->pz[j];
            dx -= box * floorf(dx / box);
            dy -= box * floorf(dy / box);
            dz -= box * floorf(dz / box);
            
            r2 = dx * dx + dy * dy + dz * dz;
            if (r2 < b2) {
                ig = (int)floor(sqrt(r2) / md->deltg);
                md->gr[ig] += 1.0;
            }
        }
    }
}

void rdf_determine(xcmd_object_t *md)
{
    float r = 0.0;
    float vb = 0.0;
    float nid = 0.0;
    float d3 = pow(md->deltg, 3);
    float c = 4.0 / 3.0;
    float rho = 0.0;
    for (int i = 0; i < md->nbin; i ++) {
        r = md->deltg * (i + 0.5);
        vb = (pow(i + 1, 3.0) - i * i * i) * d3;
        nid = c * M_PI * vb * rho;
        md->gr[i] /= (md->ngr * md->nparticle * nid);
    }
}

int main(int argc, const char * argv[])
{
    if (argc != 3) {
        printf("Error: the input file and output file should be specified!\n");
        abort();
    }
    
    // Init the global output stream.
    xcmd_global_init(argv[2]);
    
    // Read the input file.
    xcmd_object_t *md = io_read_input(argv[1]);
    
    // Set the initial velocities
    velocity_init_random(md);
    
    // Calculate the initial total energy of the system.
    potential_lenard_jones(md);
    xcmd_energy_update(md);
    
    // step : the number of simulation eclipsed.
    // tims : the simulation time eclipsed.
    int step = 0;
    float time = 0.0;
    
    // Main molecular simulation loop
    while (step < md->nsteps) {
        // Step forward
        force_lenard_jones(md);
        motion_leapfrog(md);
        xcmd_energy_update(md);
        step ++;
        time += md->timestep;
        
        if (time < md->tequil) {
            // Rescale the velocity every 20 steps before equilibration
            if (md->scale && step % 20 == 0) {
                velocity_rescale(md);
            }
        } else if (step % md->sampfreq == 0) {
            if (md->sampling) {
                
            }
            if (md->convdiff == false) {
                
            }
        }
        
        if (step % md->outfreq == 0) {
            
        }
    }
    
    potential_lenard_jones(md);
    if (md->sampling) {
        
    }
    if (md->convdiff == false) {
        
    }
    
    // write
    // store
    
    // Release the main object.
    xcmd_object_release(md);
    
    return 0;
}

