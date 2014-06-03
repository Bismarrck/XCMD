//
//  datatype.h
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_DATATYPE_H__
#define __XCMD_DATATYPE_H__

/**
 * @class xcmd_object_t
 *
 * @param temp  T*kB where T is the simulation temperature and kB is the
 *              Boltzmann constants.
 */
typedef struct __xcmd_object
{
    float *px;      /* the position coordinates on X. */
    float *py;      /* the position coordinates on Y. */
    float *pz;      /* the position coordinates on Z. */
    float vxt;      /* the velocity centre of mass on X. */
    float vyt;      /* the velocity centre of mass on Y. */
    float vzt;      /* the velocity centre of mass on Z. */
    float *fx;      /* the forces on X */
    float *fy;      /* the forces on Y */
    float *fz;      /* the forces on Z */
    float *vx;      /* the velocities on X. */
    float *vy;      /* the velocities on Y. */
    float *vz;      /* the velocities on Z. */
    int nparticle;  /* the number of particles in this molecular. */
    float temp;     /* the desired temperature. */
    float timestep; /* the time between two simulations. */
    int nsteps;     /* the number of total simulation steps. */
    float ekin;     /* the kinetic energy of current step. */
    float etot;     /* the total energy of current step. */
    float epot;     /* the potential energy of current step. */
    float ecut;     /* the cutoff energy. */
    float sigma;    /* the parameter sigma in LJ potential. */
    float epsilon;  /* the parameter epsilon in LJ potential. */
    float box;      /* the simulation cubic box side length. */
    float rc2;      /* the square of cutoff radius. */
} xcmd_object_t;


/**
 * @function xcmd_init_object
 * Init a new molecular dynamics object given numbers of particles. 
 */
xcmd_object_t *xcmd_init_object(int nparticle);


/**
 * @function xcmd_object_release
 * Release the given object.
 */
void xcmd_object_release(xcmd_object_t *object);


#endif
