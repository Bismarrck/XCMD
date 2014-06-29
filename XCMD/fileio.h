//
//  fileio.h
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_FILEIO_H__
#define __XCMD_FILEIO_H__

#include "datatype.h"

/**
 * @function io_read_input
 * Read the input file.
 *
 * @param filepath  The path of the input file.
 */
xcmd_object_t *io_read_input(const char *filepath);

/**
 * @function io_output_velocity
 * Write the current velocities to vout.
 */
void io_output_velocity(xcmd_object_t *md, int step);

/**
 * @function io_output_force
 * Write the current forces to fout.
 */
void io_output_force(xcmd_object_t *md, int step);

/**
 * @function io_output_coordinate
 * Write the current coordinates to pout.
 */
void io_output_coordinate(xcmd_object_t *md, int step);


#endif
