/**
 *@file customer_factory.h
 */
#ifndef CUSTOMER_FACTORY_H_
#define CUSTOMER_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "json_helper.h"
using entity_project::IEntity;

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory that constructs customers
 *
 */
	class CustomerFactory : public entity_project::IEntityFactory {
		public:
		   /**
			* @brief Creates a Customer object  
		    * 
	        * @param val: picojson object containing customer information 
		    * 
		    * Used in the composite factory to create Customer objects 
		    * 
		    * @return A Customer pointer casted as an IEntity pointer or nullptr
		    */
            IEntity* CreateEntity(const picojson::object& val);
	};

}  // namespace csci3081


#endif  // CUSTOMER_FACTORY_H_