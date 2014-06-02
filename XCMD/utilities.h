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

#endif
