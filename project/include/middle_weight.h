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
 * @brief A decoration used in the decorator pattern that changes medium weight packages to yellow
 *
 */
	class MiddleWeight : public PackageDecorator {
		public:
		    /**
		    * @brief Changes the packages color to yellow if it weighs between 2.0 and 4.0 
		    * 
		    */
            void Decorate();

	};
}  // namespace csci3081


#endif  // MIDDLE_WEIGHT_H_