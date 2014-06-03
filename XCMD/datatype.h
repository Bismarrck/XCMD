//
//  datatype.h
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_DATATYPE_H__
#define __XCMD_DATATYPE_H__


typedef struct __xcmd_object
{
    float *px;      /* the position coordinates on X. */
    float *py;      /* the position coordinates on Y. */
    float *pz;      /* the position coordinates on Z. */
    float *fx;      /* the forces on X */
    float *fy;      /* the forces on Y */
    float *fz;      /* the forces on Z */
    float *vx;      /* the velocities on X. */
    float *vy;      /* the velocities on Y. */
    float *vz;      /* the velocities on Z. */
    int nparticle;  /* the number of particles in this molecular. */
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
