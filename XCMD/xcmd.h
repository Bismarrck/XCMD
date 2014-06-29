//
//  xcmd.h
//  XCMD
//
//  Created by Bismarrck on 6/29/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_H__
#define __XCMD_H__

#include "datatype.h"

/**
 * @function xcmd_main
 * The main function of XCMD.
 *
 * @param input     the path to the input file.
 * @param output    the path to the output file.
 */
int xcmd_main(const char *input, const char *output);

/**
 * @function xcmd_energy_update
 * Update the current total energy.
 */
void xcmd_energy_update(xcmd_object_t *md);

/**
 * @function xcmd_sample_averages
 * Do the sampling on the current configuration.
 */
void xcmd_sample_averages(xcmd_object_t *md, int step);


#endif
