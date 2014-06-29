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
#include "unit.h"


void xcmd_energy_update(xcmd_object_t *md)
{
    md->etot = md->ekin + md->epot;
}

void sample_averages(xcmd_object_t *md, int step)
{
    float temp = 2.0 * md->ekin / (3.0 * md->nparticle);
    float vol = md->box * md->box * md->box;
    float rho = md->nparticle / vol;
    float press = rho * temp + md->virial / (3.0 * vol);
    
    fprintf(xcmdout, "Sample averages on step %3d : \
            % 6.4f % 10.8f % 16.12f % 16.12f % 16.12f\n",
            step,
            reducedTemperatureToSI(temp),
            reducedPressToSI(press),
            reducedEnergyToSI(md->epot / md->nparticle),
            reducedEnergyToSI(md->ekin / md->nparticle),
            reducedEnergyToSI(md->etot / md->nparticle));
}

int main(int argc, const char * argv[])
{
    if (argc != 3) {
        printf("Error: the input file and output file should be specified!\n");
        abort();
    }
    
    // Init the global output stream.
    xcmd_global_init(argv[1]);
    
    // Read the input file.
    xcmd_object_t *md = io_read_input(argv[2]);
    
    // Set the initial velocities
    velocity_init_random(md);
    
    // Calculate the initial total energy of the system.
    potential_lenard_jones(md);
    velocity_kinetic_energy(md);
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
        
        // Rescale the velocity every 20 steps before equilibration
        if (time < md->tequil && md->scale && step % 20 == 0) {
            velocity_rescale(md);
        }
        
        // Sample averages for every step.
        sample_averages(md, step);
        
        // Output the coordinates, forces and velocities.
        if (step % md->outfreq == 0) {
            io_output_coordinate(md, step);
            io_output_force(md, step);
            io_output_velocity(md, step);
        }
    }
    
    // Calculate the final total energy of this system.
    potential_lenard_jones(md);
    velocity_kinetic_energy(md);
    xcmd_energy_update(md);
        
    // Release the main object.
    xcmd_global_finalize();
    xcmd_object_release(md);
    
    return 0;
}

