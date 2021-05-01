/**
 *@file drone.h
 */
#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "carrier.h"
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Drone Class represents the drone that will carry out deliveries.  
 * 
 */ 
  class Drone : public Carrier {
   public:
      /**
      * @brief Constructs a Drone object  
      * 
      * @param pos: Drone position as a vector of floats  
      * @param dir: Drone direction as a vector of floats  
      * @param details: picojson object containing drone information 
      * 
      * Used in the drone factory to create drones  
      * 
      */
      Drone(std::vector<float> pos, std::vector<float> dir, const picojson::object& details);

      /**
      * @brief sets the strategy for which path the drone will use. Beeline path is default for drone.
      * 
      */
      void SetStrategy();

      /**
      * @brief Gets the route to be used based on the path selected in SetStrategy
      * 
      * @param source: starting coordinates
      * @param destination: ending coordinates 
      * 
      * @return a vector of vector coordinates outlining the path needed to get from the starting position to the destination
      * 
      */
      vector<vector<float>> GetRoute(vector<float> source, vector<float> destination);
  };

}

#endif  // DRONE_H_