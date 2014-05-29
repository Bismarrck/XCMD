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
