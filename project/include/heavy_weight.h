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
 * @brief A subclass of PackageDecorator; decoration which changes the package color to red
 *
 */
	class HeavyWeight : public PackageDecorator  {
		public:
			/**
			* @brief Constructs a heavy weight package 
			* 
			* @param package: a package pointer (concrete or decorated) using type EntityBase* 
			*
			*/
			HeavyWeight(EntityBase* package) : PackageDecorator(package) {}

			/**
		  	* @brief uses instance variable's SetDynamic(bool val) + changes package color to red
		  	* 
		  	* @param val: true or false depending on whether the entity should be moving   
		  	* 
		  	*/
			void SetDynamic(bool val);

	};
}  // namespace csci3081


#endif  // HEAVY_WEIGHT_H_