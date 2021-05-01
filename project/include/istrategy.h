/**
 *@file istrategy.h
 */
#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector3D.h"
#include <EntityProject/facade/delivery_system.h>
using entity_project::IGraph;

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The Strategy Interface: a family of routing algorithms inherit from this class
 *
 */
	class IStrategy  {
		public:
		   /**
		    * @brief Encapsulated method for carrier entities, which gets a route depending on
		    * the strategy used 
		    * 
	        * @param source: initial position of the carrier  
			* @param destination: final position of the carrier  
		    * 
		    * Pointer to this class is used as an attribute for carrier classes (e.g. Drone)
		    * 
		    */
            virtual vector<vector<float>> GetRoute(vector<float> source, vector<float> destination) = 0;
	};
}  // namespace csci3081


#endif  // ISTRATEGY_H_