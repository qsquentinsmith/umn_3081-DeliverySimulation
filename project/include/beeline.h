/**
 *@file beeline.h
 */
#ifndef BEELINE_H_
#define BEELINE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "istrategy.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Beeline class will help facilitate beeline movement by producing 
 * the appropriate coordinates to fly above buildings and directly to the destination 
 * 
 */ 
  class Beeline : public IStrategy {
    public: 
        /**
        * @brief determines the coordinates for the beeline route 
        * 
        * @param source: initial position of the carrier  
		    * @param destination: final position of the carrier
        *
        * @return a vector of coordinates which follow the beeline path 
        */
        vector<vector<float>> GetRoute(vector<float> source, vector<float> destination); 
    
  };

}

#endif  // BEELINE_H_