/**
 *@file robot_factory.h
 */
#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "json_helper.h"
#include "robot.h"
using entity_project::IEntity;

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory that constructs robots
 *
 *
 */
	class RobotFactory : public entity_project::IEntityFactory {
		public:
		   /**
		    * @brief Creates a Robot object  
		    * 
	        * @param val: picojson object containing robot information 
		    * 
		    * Used in the composite factory to create Robot objects 
		    * 
		    * @return A Robot pointer casted as an IEntity pointer or nullptr
		    */
            IEntity* CreateEntity(const picojson::object& val);
	};

}  // namespace csci3081


#endif  // ROBOT_FACTORY_H_