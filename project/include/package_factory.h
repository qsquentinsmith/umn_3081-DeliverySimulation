/**
 *@file package_factory.h
 */
#ifndef PACKAGE_FACTORY_H_
#define PACKAGE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "json_helper.h"
#include "package.h"
using entity_project::IEntity;

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory that constructs packages.
 *
 *
 */
	class PackageFactory : public entity_project::IEntityFactory {
		public:
		   /**
		    * @brief Creates a Package object  
		    * 
	        * @param val: picojson object containing package information 
		    * 
		    * Used in the composite factory to create Package objects 
		    * 
		    * @return A Package pointer casted as an IEntity pointer or nullptr
		    */
            IEntity* CreateEntity(const picojson::object& val);
	};

}  // namespace csci3081


#endif  // PACKAGE_FACTORY_H_