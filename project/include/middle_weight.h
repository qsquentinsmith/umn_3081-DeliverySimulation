/**
 *@file middle_weight.h
 */
#ifndef MIDDLE_WEIGHT_H_
#define MIDDLE_WEIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "package_decorator.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A subclass of PackageDecorator; decoration which changes the package color to yellow
 *
 */
	class MiddleWeight : public PackageDecorator {
		public:
			/**
			* @brief Constructs a middle weight package 
			* 
			* @param package: a package pointer (concrete or decorated) using type EntityBase* 
			*
			*/
			MiddleWeight(EntityBase* package) : PackageDecorator(package) {}

			/**
		  	* @brief uses instance variable's SetDynamic(bool val) + changes package color to yellow
		  	* 
		  	* @param val: true or false depending on whether the entity should be moving   
		  	* 
		  	*/
			void SetDynamic(bool val);

	};
}  // namespace csci3081


#endif  // MIDDLE_WEIGHT_H_