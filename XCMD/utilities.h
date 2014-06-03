//
//  utilities.h
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_UTILITIES_H__
#define __XCMD_UTILITIES_H__

/**
 * @function string_to_float
 * Convert the string to a double.
 */
extern float string_to_float(char *string);


/**
 * @function string_to_int
 * Convert the string to an integer.
 */
extern int string_to_int(char *string, int base);


/**
 * @function random_seed
 * Refresh the random generator seed.
 */
extern void random_seed(void);


/**
 * @function random_uniform
 * Generate a uniform-distributed random number in (0.0, 1.0).
 */
extern float random_uniform(void);


#endif
