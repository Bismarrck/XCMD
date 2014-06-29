//
//  xcmd.c
//  XCMD
//
//  Created by Bismarrck on 6/29/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include "xcmd.h"
#include "global.h"
#include "fileio.h"
#include "velocity.h"
#include "motion.h"
#include "potential.h"
#include "force.h"
#include "utilities.h"
#include "unit.h"


int xcmd_main(const char *input, const char *output)
{
    // Init the global output stream.
    xcmd_global_init(output);
    
    // Read the input file.
    xcmd_object_t *md = io_read_input(input);
    
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
        motion_anderson_thermostat_first(md);
        force_lenard_jones(md);
        motion_anderson_thermostat_second(md);
        xcmd_energy_update(md);
        step ++;
        time += md->timestep;
        
        // Rescale the velocity every 20 steps before equilibration
        if (time > md->tequil && md->scale && step % 20 == 0) {
            velocity_rescale(md);
        }
        
        // Sample averages for every step.
        xcmd_sample_averages(md, step);
        
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
    
    return 1;
}


void xcmd_energy_update(xcmd_object_t *md)
{
    md->etot = md->ekin + md->epot;
}


void xcmd_sample_averages(xcmd_object_t *md, int step)
{
    float temp = 2.0 * md->ekin / (3.0 * md->nparticle);
    float vol = md->box * md->box * md->box;
    float rho = md->nparticle / vol;
    float press = rho * temp + md->virial / (3.0 * vol);
    
    float T = reducedTemperatureToSI(temp);
    float P = reducedPressToSI(press);
    float potE = reducedEnergyToSI(md->epot / md->nparticle);
    float kinE = reducedEnergyToSI(md->ekin / md->nparticle);
    float avgE = reducedEnergyToSI(md->etot / md->nparticle);
    
    fprintf(xcmdout, "Sample averages on step %3d\n", step);
    fprintf(xcmdout, "\tTemperature %4.0f K   Pressure: %.6f MPa\n", T, P);
    fprintf(xcmdout, "\tEnergy(Pot, Kin, Total): % 16.12f % 16.12f % 16.12f\n",
            potE, kinE, avgE);
}


