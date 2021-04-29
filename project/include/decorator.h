/**
 *@file decorator.h
 */
#ifndef DECORATOR_H_
#define DECORATOR_H_

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
 * @brief The decorator is a base class that contains a vecotr of all decorations to be applied in the simulation 
 * 
 */ 
  class Decorator {
   public:
      void GetDecoratedPackage(Package* package);
      // Decorator(AbstractPackage* package) : PackageDecorator(package) {}

      // /**
	// * @brief Calls decorate on all decorations that apply to entity in the decorations vector
	// * 
	// */
      // void Decorate();

      // /**
	// * @brief Adds a new decoration to the decorations vector
	// * 
	// * @param decoration: Decoration to be added to the decorations vector
	// */
      // void AddDecoration(PackageDecorator* decoration);
      
//   private:
//         vector<PackageDecorator*> decorations;
  }; 

};

#endif  // DECORATOR_H_