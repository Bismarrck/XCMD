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

#define ITMAX       100
#define EPS         3.0e-7
#define FPMIN       1.0e-30


void nrerror(char *text)
{
    
}

// Returns the value ln[gamma(xx)] for xx > 0
float gammln(float xx)
{
    double x, y, tmp, ser;
    static double cof[6] =
    {
         76.18009172947146,
        -86.50532032941677,
         24.01409824083091,
        -1.231739572450155,
         0.1208650973866179e-2,
        -0.5395239384953e-5
    };
    y = x = xx;
    tmp = x + 5.5;
    tmp -= (x + 0.5)*log(tmp);
    ser = 1.000000000190015;
    for (int j = 0; j <= 5; j ++) {
        ser += cof[j] / (++y);
    }
    return -tmp + log(2.5066282746310005 * ser/x);
}

// Returns the incomplete gamma function Q(a,x) evaluated by its continued
// fraction representation as gammcf.
void gcf(float *gammcf, float a, float x, float *gln)
{
    float an, b, c, d, del, h;
    int i;
    *gln = gammln(a);
    b = x + 1.0 - a;
    c = 1.0 / FPMIN;
    d = 1.0 / b;
    h = d;
    for (i = 1; i <= ITMAX; i ++) {
        an = -i * (i - a);
        b += 2.0;
        d = an * d + b;
        if (fabs(d) < FPMIN) {
            d = FPMIN;
        }
        c = b + an / c;
        if (fabs(c) < FPMIN) {
            c = FPMIN;
        }
        d = 1.0 / d;
        del = d * c;
        h *= del;
        if (fabs(del - 1.0) < EPS) {
            break;
        }
    }
    if (i > ITMAX) {
        nrerror("a too large, ITMAX too small in gcf");
    }
    *gammcf = exp(-x + a*log(x) - (*gln)) * h;
}

// Returns the incomplete gamma function P(a,x) evaluated by its series
// representation as gamser. Also returns lnT(a) as gln.
void gser(float *gamser, float a, float x, float *gln)
{
    float sum, del, ap;
    *gln = gammln(a);
    if (x <= 0.0) {
        if (x < 0.0) {
            nrerror("x less than zero in routine gser");
        }
        *gamser = 0.0;
        return;
    } else {
        ap = a;
        del = sum = 1.0 / a;
        for (int n = 1; n < 100; n ++) {
            ++ ap;
            del *= x / ap;
            sum += del;
            if (fabs(del) < fabs(sum) * 3.0e-7) {
                *gamser = sum * exp(-x + a * log(x) - (*gln));
                return;
            }
        }
        nrerror("a too large. ITMAX too small in routine gser");
        return;
    }
}

// Returns the incomplete gamma function P(a,x)
float gammp(float a, float x)
{
    float gamser, gammcf, gln;
    if (x < 0.0 || a <= 0.0) {
        nrerror("Invalid arguments in routine gammp");
    }
    if (x < (a + 1.0)) {
        gser(&gamser, a, x, &gln);
        return gamser;
    } else {
        gcf(&gammcf, a, x, &gln);
        return 1.0 - gammcf;
    }
}

// Returns the incomplete gamma function Q(a,x) = 1 - P(a, x)
float gammq(float a, float x)
{
    return 1.0 - gammp(a, x);
}

// Returns the error function erf(x).
float erff(float x)
{
    return x < 0.0 ? -gammp(0.5, x*x) : gammp(0.5, x*x);
}

float ewald_kval(float kx, float ky, float kz, float rijx, float rijy, float rijz, float qiqj, float alpha2i)
{
    float k2 = kx * kx + ky * ky + kz * kz;
    return exp(-k2 * alpha2i) / k2 * qiqj * cos(kx * rijx + ky * rijy + kz * rijz);
}


/**
 * @function ewald
 * Direct ewald summation algorithm.
 * 
 * @param X
 * @param Y
 * @param Z
 * @param q
 * @param np
 * @param alpha
 * @param L
 * @param rcut
 * @param kcut
 *
 * @return
 */
float ewald(float *X, float *Y, float *Z, int nparticles, float *q, float alpha,
            float L, float dc, float rcut, int kcut)
{
    float Ur = 0.0, Uk = 0.0, Uself = 0.0, Udip = 0.0;
    float qiqj, rij, rijx, rijy, rijz, rijn, rijnx, rijny, rijnz;
    float tpi = M_PI * 2.0;
    float alpha2i = 1.0 / alpha / alpha;
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
            for (int knx = -kcut; knx < kcut + 1; knx ++) {
                for (int kny = -kcut; kny < kcut + 1; kny ++) {
                    for (int knz = -kcut; knz < kcut + 1; knz ++) {
                        kx = knx * tpi;
                        ky = kny * tpi;
                        kz = knz * tpi;
                        if (knx == 0 && kny == 0 && knz == 0) {
                            continue;
                        }
                        kE = ewald_kval(kx, ky, kz, rijx, rijy, rijz, qiqj, alpha2i);
                        printf("kE: %f\n", kE);
                        Uk += kE;
                    }
                }
            }
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
                            rijny = rijy + ny * L;
                            rijnz = rijz + nz * L;
                            rijn = sqrt(rijnx * rijnx + rijny * rijny + rijnz * rijnz);
                            Ur += qiqj * erfc(alpha * rijn) / rijn;
                        }
                    }
                }
            }
        }
        Uself += q[i] * q[i];
        Udip += q[i] * sqrt((X[i] * X[i] + Y[i] * Y[i] + Z[i] * Z[i]));
    }
    
    float L3i = 1.0 / L / L / L;
    
    Ur *= 0.5;
    Uk *= 2.0 * M_PI * L3i;
    Uself *= -alpha / sqrt(M_PI);
//    Udip *= 2.0 * M_PI * L3i / (1.0 + 2.0 * dc) * Udip;
    
    printf("Real space energy:  %12.8f\n", Ur);
    printf("Reciprocal space E: %12.8f\n", Uk);
    printf("Self interaction E: %12.8f\n", Uself);
    printf("Energy (no dipole): %12.8f\n", Ur + Uk + Uself);
    
    return Ur + Uk + Uself + Udip;
}


