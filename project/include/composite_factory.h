/**
 *@file composite_factory.h
 */
#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "drone_factory.h"
#include "customer_factory.h"
#include "package_factory.h"
#include "robot_factory.h"
#include <vector>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory that determines the correct factory to create entities
 *
 */
	class CompositeFactory : public entity_project::IEntityFactory {
		public:
            /**
            * @brief Creates an entity (Drone, Customer or Package)
            *   
            * @param val: picojson object containing entity information 
            *
            * The Delivery Simulation uses this method to create entities 
            *
            * @return A Drone, Customer or Package pointer casted as an IEntity pointer or nullptr
            */
            IEntity* CreateEntity(const picojson::object& val);


            /**
            * @brief Adds a factory to this class's vector of factories 
            *
            * @param factory: a pointer to a certain entity factory   
            *
            * The Delivery Simulation uses this method to add the given factory 
            * to keep track of all factories in this composite factory  
            *
            */
            void AddFactory(IEntityFactory* factory); 
            
        private: 
        	std::vector<IEntityFactory*> componentFactories; 
	};

}  // namespace csci3081


#endif  // COMPOSITE_FACTORY_H_