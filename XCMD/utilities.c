//
//  utilities.c
//  XCMD
//
//  Created by Bismarrck on 6/2/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "utilities.h"


float string_to_float(char *string)
{
    char *end;
    float res = strtod(string, &end);
    return res;
}

int string_to_int(char *string, int base)
{
    char *end;
    int res = (int)strtol(string, &end, base);
    return res;
}

void random_seed(void)
{
    time_t seed;
    time(&seed);
    srandom((unsigned int) seed);
}

float random_uniform(void)
{
    return (random() + 1.0) / (RAND_MAX + 1.0);
}

int isFileExists(const char *filepath)
{
	struct stat buffer;
	return (stat(filepath, &buffer) == 0);
}
