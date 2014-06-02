//
//  ewald.h
//  XCMD
//
//  Created by Bismarrck on 5/20/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_EWALD_H__
#define __XCMD_EWALD_H__

/**
 * @function scrfc
 * The zero order screening function.
 */
extern float scrfc(float alpha, float R);

/**
 * @function dscrfc
 * The derivative of zero order screening function to R.
 */
extern float dscrfc(float alpha, float R);

/**
 * @function scrf1
 * The first order screening function.
 */
extern float scrf1(float alpha, float R);

/**
 * @function dscrf1
 * The derivative of first order screening function to R.
 */
extern float dscrf1(float alpha, float R);

/**
 * @function scrf2
 * The second order screening function.
 */
extern float scrf2(float alpha, float R);

/**
 * @function dscrf2
 * The derivative of second order screening function to R.
 */
extern float dscrf2(float alpha, float R);

/**
 * @function scrf3
 * The third order screen function.
 */
extern float scrf3(float alpha, float R);

/**
 * @function scrf4
 * The fourth order screen function.
 */
extern float scrf4(float alpha, float R);

/**
 * @function scrf5
 * The fifth order screen function.
 */
extern float scrf5(float alpha, float R);

/**
 * @function ewald
 * Direct ewald summation algorithm.
 *
 * @param X     The x coordinates of each atom.
 * @param Y     The y coordinates of each atom.
 * @param Z     The z coordinates of each atom.
 * @param q     The q of each atom.
 * @param np    The number of particles in this configuration.
 * @param alpha The alpha constant.
 * @param L     The side length of the square box.
 * @param rcut  The cutoff radius for the real space.
 * @param kcut  The cutoff parameter for the reciporal space.
 *
 * @return  The total columb energy.
 */
float ewald(float *X, float *Y, float *Z, int nparticles, float *q, float alpha,
            float L, float rcut, int kcut);


#endif
