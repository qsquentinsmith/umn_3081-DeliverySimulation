/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector2D.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Vector3D Class is a helper class which aids in 3D Vector math.
 * 
 */ 
  class Vector3D : public csci3081::Vector2D {
    public:
      /**
      * @brief Constructs default Vector3D object 
      *
      * Default vector is <0,0,0>
      * 
      */
        Vector3D(); 

      /**
      * @brief Constructs a Vector3D object
      *
      * @param: a vector of floats  
      * 
      * Separates vector to individual components
      */
        Vector3D(std::vector<float> pos);

      /**
      * @brief Adds input vector to current vector    
      *
      * @return New Vector3D object 
      */
        Vector3D operator+(Vector3D rhsVec);

      /**
      * @brief Subtracts input vector from current vector    
      *
      * @return New Vector3D object 
      */
        Vector3D operator-(Vector3D rhsVec);


      /**
      * @brief Multiplies each component of the vector by the input number    
      *
      * @return New Vector3D object 
      */
        Vector3D operator*(float num);

      /**
      * @brief Normalizes the vector    
      *
      * @return Normalized Vector3D object 
      */
        Vector3D Normalize(); 

  };

}