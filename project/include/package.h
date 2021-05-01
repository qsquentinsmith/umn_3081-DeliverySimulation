/**
 *@file package.h
 */
#ifndef PACKAGE_H_
#define PACKAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "customer.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Package Class represents the package to be delivered. 
 * 
 */ 
  class Package : public csci3081::EntityBase {
   public:
      /**
      * @brief Constructs a Package object  
      * 
      * @param pos: Package position as a vector of floats  
      * @param dir: Package direction as a vector of floats
      * @param wt: Package weight
      * @param cus: Pointer for associated customer 
      * @param obj: picojson object containing package information 
      * 
      * Used in the package factory to create packages  
      * 
      */
      Package(std::vector<float> pos, std::vector<float> dir, float wt, Customer* cus, const picojson::object& obj);
    
      /**
      * @brief Gets the package's position   
      * 
      * Used for vector math to determine new direction for the drone to move to the package 
      * 
      * @return a vector of floats indicating the package position  
      */
      const std::vector<float>& GetPosition() const;

      /**
      * @brief Gets the package's direction    
      * 
      * Can be used to see the package's current direction 
      * 
      * @return a vector of floats indicating the package direction   
      */
      const std::vector<float>& GetDirection() const;

      /**
      * @brief Gets package weight    
      * 
      * Can be used to check the package weight  
      * 
      * @return Package Weight    
      */
      float GetWeight();
      
      /**
      * @brief Gets the package destination, which is the customer postion     
      * 
      * Used for the drone and package to know where the customer is  
      * 
      * @return Customer position as a vector of floats    
      */
      const std::vector<float>& GetCustomerPosition();

      /**
      * @brief Sets the package's position  
      *
      * @param pos: a vector of floats indicating new package position  
      *       
      * Used for package movement 
      * 
      */
      void SetPosition(std::vector<float> pos);

      /**
      * @brief Sets the package's direction   
      * 
      * @param dir: a vector of floats indicating package direction  
      *
      * Not currently used, but may be used in the future  
      * 
      */
      void SetDirection(std::vector<float> dir);

      /**
      * @brief Sets the package's associated customer 
      * 
      * @param cus: Pointer for associated customer   
      *
      * Used while schedulig a delivery, giving package a destination  
      * 
      */
      void SetCustomer(Customer* cus); 

      /**
      * @brief Getter for customer pointer associated with the package
      * 
      * @return customer pointer 
      *
      */
      Customer* GetCustomer(); 

      /**
      * @brief Sets whether the package is moving or not  
      * 
      * @param val: true or false depending on whether the package should be moving   
      *
      */
      void SetDynamic(bool val); 

  private:
      std::vector<float> position; 
      std::vector<float> direction;
      float weight;
      Customer* customer; 
  }; 

}

#endif  // PACKAGE_H_