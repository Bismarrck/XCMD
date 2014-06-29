//
//  unit.h
//  XCMD
//
//  Created by Bismarrck on 6/29/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#ifndef __XCMD_UNIT_H__
#define __XCMD_UNIT_H__


/**
 * @function reducedTimeToSI
 * Convert the reduced time to SI time (picosecond).
 */
float reducedTimeToSI(float rt);

/**
 * @function reducedTemperatureToSI
 * Convert the reduced temperature to kelvin.
 */
float reducedTemperatureToSI(float rt);

/**
 * @function reducedLengthToSI
 * Convert the reduced length to angstroms.
 */
float reducedLengthToSI(float rl);

/**
 * @function reducedPressToSI
 * Convert the reduced pressure to MPa.
 */
float reducedPressToSI(float rp);

/**
 * @function reducedEnergyToSI
 * Convert the reduced energy to keV.
 */
float reducedEnergyToSI(float re);


#endif
