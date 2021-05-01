/**
 *@file smart_path.h
 */
#ifndef SMART_PATH_H_
#define SMART_PATH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "istrategy.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Smart Path class handles operations used when a drone or robot uses the smart route.
 * 
 */ 
  class Smart : public IStrategy {
    public: 
      /**
      * @brief allows smart strategy access to the graph pointer to retrieve smart routes
      *
      * @param graph: passes in graph from delivery simulations call to IGraph facade
      * 
      */

      Smart(const IGraph* graph); 

       /**
        * @brief determines the coordinates for the beeline route 
        * 
        * @param source: initial position of the carrier  
		    * @param destination: final position of the carrier
        *
        * @return a vector of coordinates which follow the beeline path 
        */
      vector<vector<float>> GetRoute(vector<float> source, vector<float> destination); 

     private:
       const IGraph* graph_;

  };

}

#endif  // SMART_PATH_H_