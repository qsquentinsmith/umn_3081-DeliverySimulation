/**
 *@file light_weight.h
 */
#ifndef LIGHT_WEIGHT_H_
#define LIGHT_WEIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "package_decorator.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A subclass of PackageDecorator; decoration which changes the package color to green
 *
 */
	class LightWeight : public PackageDecorator  {
		public:
			/**
			* @brief Constructs a light weight package 
			* 
			* @param package: a package pointer (concrete or decorated) using type EntityBase* 
			*
			*/
			LightWeight(EntityBase* package) : PackageDecorator(package) {}

			/**
		  	* @brief uses instance variable's SetDynamic(bool val) + changes package color to green 
		  	* 
		  	* @param val: true or false depending on whether the entity should be moving   
		  	* 
		  	*/
			void SetDynamic(bool val);

	};
}  // namespace csci3081


#endif  // LIGHT_WEIGHT_H_