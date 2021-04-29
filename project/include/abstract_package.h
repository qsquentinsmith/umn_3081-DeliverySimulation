/**
 *@file abstract_package.h
 */
#ifndef ABSTRACT_PACKAGE_H_
#define ABSTRACT_PACKAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
// #include "entity_base.h"
// #include "package.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The interface for a decorated package 
 *
 */
	class AbstractPackage  {
		public:
		   /**
		    * @brief Method to be overloaded by the Package class and its decorator classes
		    * 
		    */
            virtual void Decorate() = 0;

	};
}  // namespace csci3081


#endif  // ABSTRACT_PACKAGE_H_