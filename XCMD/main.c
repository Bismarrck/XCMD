//
//  main.c
//  XCMD
//
//  Created by Bismarrck on 5/20/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include "xcmd.h"

int main(int argc, const char * argv[])
{
    if (argc != 3) {
        printf("Error: the input file and output file should be specified!\n");
        return -1;
    }
    return xcmd_main(argv[1], argv[2]);
}

