/**
 *@file parabolic.h
 */
#ifndef PARABOLIC_H_
#define PARABOLIC_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "istrategy.h"
 #include "math.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/

  /**
 * @brief The Parabolic class handles operations used when a drone uses the parabolic route  
 * 
 */ 
  class Parabolic : public IStrategy {
    public:

      /**
      * @brief Gets a parabolic route for the drone to fly on
      *
      * @param source: represents the drones location or the first point of the parabola
      * @param destination: represents the final position along the parabola (package or customer)
      * @return a vector of 3 dimentional coordinates for the drone to fly to
      */
      std::vector<std::vector<float>> GetRoute(std::vector<float> source, std::vector<float> destination);

    private:
      void CreatePath();
      std::vector<float> Midpoint(Vector3D initialPosition, Vector3D finalPosition);
      void SolveEquation(Vector3D init, Vector3D mid, Vector3D end);
      const float maximumHeight = 100.0;
      std::vector<float> source;
      std::vector<float> destination;
      std::vector<std::vector<float>> route;
      bool toPackage = true;

};
}

#endif  // PARABOLIC_H_