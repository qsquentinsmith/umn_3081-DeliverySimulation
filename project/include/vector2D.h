/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
using std::vector; 
#include <math.h>

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Vector2D Class is a helper class which aids in 2D Vector math.
 * 
 */ 
  class Vector2D {
    public:
      /**
      * @brief Constructs default Vector2D object 
      *
      * Default vector is <0,0,0>, only x and z dimensions relevant 
      * 
      */
        Vector2D();

      /**
      * @brief Constructs a Vector2D object  
      *
      * @param pos: a vector of floats  
      * 
      * Separates vector to individual components
      */
        Vector2D(std::vector<float> pos); 

      /**
      * @brief Gets the x component of the vector   
      *
      * @return x component 
      */
        float GetXPos();

      /**
      * @brief Gets the y component of the vector   
      *
      * @return y component 
      */
        float GetYPos(); 

      /**
      * @brief Gets the z component of the vector   
      *
      * @return z component 
      */
        float GetZPos(); 

      /**
      * @brief Sets the y component of the vector  
      *
      * @param y: float to set y component to 
      */
        void SetYPos(float y); 

      /**
      * @brief Converts Vector2D or Vector3D object to float of vectors    
      *
      * @return vector of floats 
      */
        std::vector<float> Convert();

      /**
      * @brief Adds input vector to current vector    
      *
      * @param rhsVec: Vector2D to add to left hand side vector
      *
      * @return New Vector2D object 
      */
        Vector2D operator+(Vector2D rhsVec);

      /**
      * @brief Subtracts input vector from current vector    
      *
      * @param rhsVec: Vector2D to subtract from left hand side vector
      *
      * @return New Vector2D object 
      */
        Vector2D operator-(Vector2D rhsVec);

      /**
      * @brief Multiplies each component of the vector by the input number    
      *
      * @param num: number to multiply vector components by
      *
      * @return New Vector2D object 
      */
        Vector2D operator*(float num);

      /**
      * @brief Calculates the magnitude of vector    
      *
      * @return Magnitude of the Vector2D object 
      */
        float Magnitude();


      /**
      * @brief Normalizes the vector    
      *
      * @return Normalized Vector2D object 
      */
        Vector2D Normalize(); 
 
    protected:
        float xPos; 
        float yPos; 
        float zPos; 
  };

}