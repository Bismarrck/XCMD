//
//  global.h
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_GLOBAL_H__
#define __XCMD_GLOBAL_H__

#include <stdio.h>

/**
 * @var xcmdout
 * The standard and global output stream for XCMD.
 */
extern FILE *xcmdout;

/**
 * @function xcmd_global_init
 * Init the globale variables and functions.
 */
void xcmd_global_init(const char *filepath);


/**
 * @function xcmd_global_finalize
 * Finalize all the global variables and functions.
 */
void xcmd_global_finalize(void);

#endif
