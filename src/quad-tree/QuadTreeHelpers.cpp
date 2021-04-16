/**
 * @file QuadTreeHelpers.cpp.c
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 16/04/2021
 */
 
#include "QuadTreeHelpers.h"


bool quad::isIntersecting(const rect &rec1, const rect &rec2)
{
    if (rec1.x + rec1.w >= rec2.x && rec1.x <= rec2.x + rec2.w)
    {
        // We have hit on the x-axis.
        if (rec1.y + rec1.h >= rec2.y && rec1.y <= rec2.y + rec2.h)
        {
            return true;  // We have also hit on the y-axis.
        }
    }
    return false;
}