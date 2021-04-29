/**
 *@file heavy_weight.h
 */
#ifndef HEAVY_WEIGHT_H_
#define HEAVY_WEIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "package_decorator.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A decoration used in the decorator pattern that changes heavier packages to red
 *
 */
	class HeavyWeight : public PackageDecorator  {
		public:
		   /**
		    * @brief Changes the packages color to red if it weighs more than 4.0 
		    * 
		    */
            void Decorate();

	};
}  // namespace csci3081


#endif  // HEAVY_WEIGHT_H_