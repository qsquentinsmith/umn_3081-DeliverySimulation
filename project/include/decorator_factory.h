/**
 *@file decorator_factory.h
 */
#ifndef DECORATOR_FACTORY_H_
#define DECORATOR_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "light_weight.h"
 #include "middle_weight.h"
 #include "heavy_weight.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Decorator Factory is a simple factory which creates the decorated packages 
 * 
 */ 
  class DecoratorFactory {
   public:
      /**
	* @brief Creates a decorated package depending on the weight of the given package
	* 
	* @param package: a Package pointer with weight information 
      *
      * @return the decorated package pointer casted as an EntityBase* 
	*/
      EntityBase* GetDecoratedPackage(Package* package);
  }; 

};

#endif  // DECORATOR_FACTORY_H_