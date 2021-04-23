/**
 * @file robot.h
 */
#ifndef ROBOT_H_
#define ROBOT_H_
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
 * @brief The Robot Class represents the robot that will carry out deliveries.  
 * 
 */ 
  class Robot : public Carrier {
   public:
      /**
      * @brief Constructs a Robot object  
      * 
      * @param pos: Robot position as a vector of floats  
      * @param dir: Robot direction as a vector of floats  
      * @param details: picojson object containing robot information 
      * 
      * Used in the robot factory to create robot  
      * 
      */
      Robot(std::vector<float> pos, std::vector<float> dir, const picojson::object& details);

       /**
      * @brief sets the strategy for which path the robot will use. Smart path is the only path robot can use currently.
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
#endif  // ROBOT_H_