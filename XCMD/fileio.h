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


#endif
