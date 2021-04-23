/**
 *@file drone_factory.h
 */
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "json_helper.h"
#include "drone.h"
using entity_project::IEntity;

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory that constructs drones
 *
 *
 */
	class DroneFactory : public entity_project::IEntityFactory {
		public:
		   /**
			* @brief Creates a Drone object  
		    * 
	        * @param val: picojson object containing drone information 
		    * 
		    * Used in the composite factory to create Drone objects 
		    * 
		    * @return A Drone pointer casted as an IEntity pointer or nullptr
		    */
            IEntity* CreateEntity(const picojson::object& val);
	};

}  // namespace csci3081


#endif  // DRONE_BASE_H_