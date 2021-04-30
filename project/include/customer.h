/**
 *@file customer.h
 */
#ifndef CUSTOMER_H_
#define CUSTOMER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Customer Class represents the customer the package will be delivered to.
 * 
 */ 
  class Customer : public csci3081::EntityBase {
   public:
    /**
     * @brief Constructs a Customer object 
     * 
     * @param pos: Customer position as a vector of floats 
     * @param details: picojson object containing customer information 
     * 
     * Used to create a pointer for the Package class, since the Package needs to know the customer location +
     * Used in the customer factory to create customers 
     *
     */
      Customer(std::vector<float> pos, const picojson::object& details);
    
    /**
     * @brief Gets the position of the customer 
     *
     * Used for packages to store customer locations  
     * 
     * @return a vector of floats inidicating customer positon 
     */
      const std::vector<float>& GetPosition() const;

    /**
     * @brief Gets the direction of the customer 
     *
     * Purely for the purpose of overriding the IEntity pure virtual method +
     * the customer direction is a zero vector since it does not move 
     * 
     * @return a zero vector of floats  
     */
      const std::vector<float>& GetDirection() const;

      void SetDynamic(bool val) {}



    private:
      std::vector<float> position; 
      std::vector<float> direction; 
  };

}

#endif  // CUSTOMER_H_