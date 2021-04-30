/**
 *@file carrier.h
 */
#ifndef CARRIER_H_
#define CARRIER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "math.h"
#include "battery.h"
#include "beeline.h"
#include "smart_path.h"
#include "parabolic.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief Represents entities that will carry packages (e.g Drone, Robot).  
 * 
 */ 
  class Carrier : public EntityBase {
   public:
      /**
      * @brief Gets the carrier's position   
      * 
      * @return a vector of floats indicating the carrier position  
      */
      const std::vector<float>& GetPosition() const;

      /**
      * @brief Gets the carrier's direction// check battery    
      * 
      * @return a vector of floats indicating the carrier direction   
      */
      const std::vector<float>& GetDirection() const;

      /**
      * @brief Gets the carrier's current speed .
      * 
      * @return a float that represents the speed.
      */
      float GetSpeed();

      /**
      * @brief Gets the carrier's route to be followed.
      * 
      * @param source: the coordinates of the starting position
      * @param destination: the coordinates of the destination position
      * 
      * @return a vector of coordinates that follow a certain path 
      */
      virtual vector<vector<float>> GetRoute(vector<float> source, vector<float> destination) = 0;

      /**
      * @brief Gets the carrier's route.
      * 
      * @return a vector of coordinates that follow a certain path.
      */
      vector<vector<float>> GetRoute(); 

      /**
      * @brief Determines whether carrier is scheduled for a package pick-up.
      * 
      * @return true or false depending on if the package is scheduled.
      */
			bool IsScheduled();

      /**
      * @brief Sets the carrier's position.
      *
      * @param pos: a vector of floats indicating new carrier position. 
      *       
      */
      void SetPosition(vector<float> pos);

      /**
      * @brief Sets the carrier's direction   
      * 
      * @param dir: a vector of floats indicating new carrier direction  
      *
      */
      void SetDirection(vector<float> dir);

      /**
      * @brief Sets the carrier's speed  
      * 
      * @param sp: a float that represents the new carrier speed  
      *
      */
      void SetSpeed(float sp);

      /**
      * @brief Sets the carrier's route   
      * 
      * @param rt: a vector of coordinates that follow a certain path  
      *
      */
      void SetRoute(vector<vector<float>> rt);

      /**
      * @brief Sets whether the carrier is scheduled  
      *
      * @param val: true or false depending on if the package is scheduled
      *       
      */
      void SetScheduled(bool val);

      /**
      * @brief Checks if the carrier has reached the next position in its route 
      * 
      * @param nextPosition: coordinate of next position
      * @param radius: distance from next position that's considered "close enough"
      *
      * @return true or false depending on if the carrier has reached the next position
      */
      bool ReachedNextPosition(vector<float> nextPosition, float radius);

      /**
      * @brief Computes the new direction the carrier must travel 
      * 
      * @param nextPosition: represents the next position in the route
      *
      * @return a Vector3D representing the current carrier direction 
      */
      Vector3D GetNewDirection(vector<float> nextPosition); 

      /**
      * @brief Computes the new position the carrier must go to 
      *
      * @param dir: a Vector3D that represents the direction of the carrier
      * @param dt: the time step for each update
      *
      * @return a vector of floats representing the new position 
      */
      vector<float> GetNewPosition(Vector3D dir, float dt); 

      /**
      * @brief moves the carrier along the route 
      * 
      * @param dt: the time step for each update  
      *
      * @return true or false depending on if the carrier has reached the destination 
      */
      bool Move(float dt); 

      /**
      * @brief Sets graph variable for carriers. 
      * 
      * @param graph: read only graph  
      *
      */
      void SetGraph(const IGraph* graph);

      /**
      * @brief Gets the read only graph 
      * 
      * @return read only graph 
      *
      */
      const IGraph* GetGraph();

      /**
      * @brief Gets battery object
      * 
      * @return battery object pointer
      *
      */
      Battery* GetBattery();

      /**
      * @brief Get carrier version  
      *
      * @return integer 0 or 1, 0 for no recent change and 1 for recent change 
      */
      int GetVersion();

      /**
      * @brief Set carrier version
      * 
      * @param ver: Integer version value
      */
      void SetVersion(int ver);


      /**
      * @brief Gets the path associated with carrier
      * 
      * @return path name
      */
      std::string GetPath(); 

      /**
      * @brief Set strategy for carrier
      * 
      * 
      */
      virtual void SetStrategy() = 0; 

      void SetDynamic(bool val); 

    protected:
      Battery* battery_ = nullptr; 
      const IGraph* graph_;
      IStrategy* strategy;
      std::string path = ""; 
      std::vector<float> position; 
      std::vector<float> direction;
      float speed;
      vector<vector<float>> route; 
      bool scheduled = false; 
      int version;
      int iter = 0; 
  };

}

#endif  // CARRIER_H_