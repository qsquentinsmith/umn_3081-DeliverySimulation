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
 * @brief A decoration used in the decorator pattern that changes lighter packages to green
 *
 */
	class LightWeight : public PackageDecorator  {
		public:
			LightWeight(Package* package) : PackageDecorator(package) {}

			void SetDynamic(bool val);

	};
}  // namespace csci3081


#endif  // LIGHT_WEIGHT_H_