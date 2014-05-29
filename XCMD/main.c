//
//  main.c
//  XCMD
//
//  Created by Bismarrck on 5/20/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "ewald.h"

int main(int argc, const char * argv[])
{
    char *filepath = "/Users/bismarrck/Desktop/ion.dat";
    
    int nparticles = 8;
    float x[nparticles];
    float y[nparticles];
    float z[nparticles];
    float q[nparticles];
    
    FILE *fp = fopen(filepath, "r");
    char buf[128];
    int k = 0;
    float xx, yy, zz, qq;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        int n = sscanf(buf, "%f %f %f %f", &qq, &xx, &yy, &zz);
        if (n == 4) {
            x[k] = xx;
            y[k] = yy;
            z[k] = zz;
            q[k] = qq;
            k ++;
        }
    }
    fclose(fp);
    ewald(x, y, z, nparticles, q, 0.35, 3.0, 0.0, 9.5, 1);
    return 0;
}

