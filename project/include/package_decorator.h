/**
 *@file package_decorator.h
 */
#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
// #include "entity_base.h"
// #include "package.h"
//#include "abstract_package.h"
#include "package.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The interface for a decorated package 
 *
 */
	class PackageDecorator : public EntityBase {
		public:
            PackageDecorator(EntityBase* package);

			const vector<float>& GetPosition() const; 

			const vector<float>& GetDirection() const; 

			void SetDynamic(bool val);

        protected: 
            EntityBase* package_; 
	};
}  // namespace csci3081


#endif  // PACKAGE_DECORATOR_H_