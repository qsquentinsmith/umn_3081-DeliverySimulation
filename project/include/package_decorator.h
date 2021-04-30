/**
 *@file package_decorator.h
 */
#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
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
			/**
			* @brief Base constructor for all package decorations 
			* 
			* @param package: a package pointer (concrete or decorated) using type EntityBase* 
			*
			*/
            PackageDecorator(EntityBase* package);

			/**
			* @brief Overriden IEntity virtual method, uses instance variable's GetPosition() 
			* 
			* @return a vector of floats indicating the package position  
			*/
			const vector<float>& GetPosition() const; 

			/**
			* @brief Overriden IEntity virtual method, uses instance variable's GetDirection()   
			* 
			* @return a vector of floats indicating the package direction   
			*/
			const vector<float>& GetDirection() const; 

			/**
		  	* @brief Overriden EntityBase virtual method, uses instance variable's SetDynamic(bool val)
		  	* 
		  	* @param val: true or false depending on whether the entity should be moving   
		  	* 
		  	*/
			void SetDynamic(bool val);

        protected: 
            EntityBase* package_; 
	};
}  // namespace csci3081


#endif  // PACKAGE_DECORATOR_H_