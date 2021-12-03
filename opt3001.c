/*
 * opt3001.c
 *
 *  Created on: Mar 14, 2021
 *      Author: younghyunkim, edited by Anirudh Jayendra, 17th March 2021
 */

#include "opt3001.h"
#include "math.h"

/******************************************************************************
 * Initialize the opt3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/

void opt3001_init(void)
{
    // Initialize OPT3001
    /* ADD CODE */
    i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, 0xC610);
}


/******************************************************************************
 * Returns the current ambient light in lux
 *  ******************************************************************************/
float opt3001_read_lux(void)
{
    // Read the Result register of OPT3001 and convert into Lux, then return.
    /* ADD CODE */
    uint16_t result = i2c_read_16(OPT3001_SLAVE_ADDRESS, RESULT_REG);
    float lux = (0.01 * (pow(2,(result>>12))) * (result & 0000111111111111));

    return lux; // Need to modify

}

