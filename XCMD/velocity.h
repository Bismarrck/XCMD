//
//  velocity.h
//  XCMD
//
//  Created by Bismarrck on 6/3/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_VELOCITY_H__
#define __XCMD_VELOCITY_H__


#include "datatype.h"


/**
 * @function velocity_init_random
 * Init the velocities for each atom in the MD system with simple random 
 * distribution.
 */
void velocity_init_random(xcmd_object_t *object);


/**
 * @function velocity_init_boltzman
 * Init the velocities for each atom in the MD system with Maxwell-Boltzmann
 * distribution.
 *
 * @warning Not implemented yet!
 */
void velocity_init_boltzmann(xcmd_object_t *object);


#endif
