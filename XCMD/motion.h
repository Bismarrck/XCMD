//
//  motion.h
//  XCMD
//
//  Created by Bismarrck on 6/3/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_MOTION_H__
#define __XCMD_MOTION_H__

#include "datatype.h"

/**
 * @function motion_leapfrog
 * Solve the equation of motion using leap frog algorithm.
 */
void motion_leapfrog(xcmd_object_t *md);


/**
 * @function motion_verlet
 * Solve the equation of motion using verlet algorithm.
 */
void motion_verlet(xcmd_object_t *md);


#endif
