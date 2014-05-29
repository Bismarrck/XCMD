//
//  ewald.c
//  XCMD
//
//  Created by Bismarrck on 5/20/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "ewald.h"


float ewald_kval(float kx, float ky, float kz, float rijx, float rijy,
                 float rijz, float qiqj, float alpha2i)
{
    float k2 = kx * kx + ky * ky + kz * kz;
    float ikr = kx * rijx + ky * rijy + kz * rijz;
    return exp(-k2 * alpha2i) / k2 * qiqj * cos(ikr);
}


float ewald(float *X, float *Y, float *Z, int nparticles, float *q, float alpha,
            float L, float rcut, int kcut)
{
    float Ur = 0.0, Uk = 0.0, Uself = 0.0;
    float qiqj, rij, rijx, rijy, rijz, rijn, rijnx, rijny, rijnz;
    float dx2, dy2, dz2;
    float tpi = M_PI * 2.0;
    float a2i = 1.0 / alpha / alpha;
    float kx, ky, kz, kE;
    
    int nmax = 0;
    if (rcut > L * 0.5) {
        nmax = (int)(rcut / L);
    }
    
    for (int i = 0; i < nparticles; i ++) {
        for (int j = 0; j < nparticles; j ++) {
            rijx = X[i] - X[j];
            rijy = Y[i] - Y[j];
            rijz = Z[i] - Z[j];
            rij = sqrt(rijx * rijx + rijy * rijy + rijz * rijz);
            qiqj = q[i] * q[j];
            
            // Compute the reciprocal space energy
            for (int knx = -kcut; knx < kcut + 1; knx ++) {
                for (int kny = -kcut; kny < kcut + 1; kny ++) {
                    for (int knz = -kcut; knz < kcut + 1; knz ++) {
                        kx = knx * tpi;
                        ky = kny * tpi;
                        kz = knz * tpi;
                        if (knx == 0 && kny == 0 && knz == 0) {
                            continue;
                        }
                        kE = ewald_kval(kx, ky, kz, rijx, rijy, rijz, qiqj,a2i);
                        Uk += kE;
                    }
                }
            }
            
            // Compute the real space energy. The self-self term should not be
            // included, but the self-self_image terms should not be forgot.
            if (nmax == 0 && i != j) {
                Ur += qiqj * erfc(alpha * rij) / rij;
            } else {
                for (int nx = -nmax; nx < nmax + 1; nx ++) {
                    for (int ny = -nmax; ny < nmax + 1; ny ++) {
                        for (int nz = -nmax; nz < nmax + 1; nz ++) {
                            if (nx == 0 && ny == 0 && nz == 0 && i == j) {
                                continue;
                            }
                            rijnx = rijx + nx * L;
                            dx2 = rijnx * rijnx;
                            rijny = rijy + ny * L;
                            dy2 = rijny * rijny;
                            rijnz = rijz + nz * L;
                            dz2 = rijnz * rijnz;
                            rijn = sqrt(dx2 + dy2 + dz2);
                            Ur += qiqj * erfc(alpha * rijn) / rijn;
                        }
                    }
                }
            }
        }
        
        // Compute the self-interaction energy
        Uself += q[i] * q[i];
    }
    
    Ur *= 0.5;
    Uk *= 2.0 * M_PI * 1.0 / L / L / L;
    Uself *= -alpha / sqrt(M_PI);
    
#if DEBUG
    printf("Real space energy:  %12.8f\n", Ur);
    printf("Reciprocal space E: %12.8f\n", Uk);
    printf("Self interaction E: %12.8f\n", Uself);
    printf("Total energy :      %12.8f\n", Ur + Uk + Uself);
#endif
    
    return Ur + Uk + Uself;
}


