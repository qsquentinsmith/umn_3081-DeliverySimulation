/**
 *@file decorator_factory.h
 */
#ifndef DECORATOR_FACTORY_H_
#define DECORATOR_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "package_decorator.h"
 #include "light_weight.h"
 #include "middle_weight.h"
 #include "heavy_weight.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Decorator Factory is a simple factory which builds and uses decorated packages 
 * 
 */ 
  class DecoratorFactory {
   public:
      /**
	* @brief Creates a decorated package and calls its respective SetDynamic method
	* 
	* @param package: a Package pointer with weight information 
	*/
      EntityBase* GetDecoratedPackage(Package* package);
  }; 

};

#endif  // DECORATOR_FACTORY_H_