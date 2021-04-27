/**
 *@file idecorate.h
 */
#ifndef IDECORATE_H_
#define IDECORATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "package.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The decorate Interface: a family of decorations inherit from this class
 *
 */
	class IDecorate  {
		public:
		   /**
		    * @brief Method to be overloaded by child decoratior pattern classes
		    * 
	        * @param entity: entity to be decorated  
		    */
            virtual void Decorate(IEntity* entity) = 0;

	};
}  // namespace csci3081


#endif  // IDECORATE_H_