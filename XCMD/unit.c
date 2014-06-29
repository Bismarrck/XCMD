//
//  unit.c
//  XCMD
//
//  Created by Bismarrck on 6/29/14.
//  Copyright (c) 2014 TCCL. All rights reserved.
//

#include <stdio.h>
#include "unit.h"


/**
 * @function reducedTimeToSI
 * Convert the reduced time to SI time (picosecond).
 */
float reducedTimeToSI(float rt)
{
    return rt * 2180.0;
}

/**
 * @function reducedTemperatureToSI
 * Convert the reduced temperature to kelvin.
 */
float reducedTemperatureToSI(float rt)
{
    return rt * 119.8;
}

/**
 * @function reducedLengthToSI
 * Convert the reduced length to angstroms.
 */
float reducedLengthToSI(float rl)
{
    return rl * 3.405;
}

/**
 * @function reducedPressToSI
 * Convert the reduced pressure to MPa.
 */
float reducedPressToSI(float rp)
{
    return rp * 41.9;
}

/**
 * @function reducedEnergyToSI
 * Convert the reduced energy to keV.
 */
float reducedEnergyToSI(float re)
{
    return re * 8.6173324 * 0.01;
}