/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class for entities in the simulation
 *
 * This class can be used as the base class for all entities in the delivery system and implements the IEntity interface.
 */
	class EntityBase : public IEntity {
		public:
	  	  	/**
		  	* @brief destructor  
	    	* 
	      	* NOT USED 
		  	* 
	      	*/
	  		virtual ~EntityBase(); 

	  	  	/**
		  	* @brief Gets the picojson object    
	      	* 
	      	* Getting the picojson object for an entity lets us parse it for information 
	      	*
	      	* @return A picojson object for an entity 
	      	*/
	  		picojson::object& GetDetails();

	  	  	/**
		  	* @brief Gets the entity's ID    
	      	*
	      	* @return The entity's ID
	      	*/
	  		int GetId() const;  

	  	  	/**
		  	* @brief Gets the entity's name   
	      	* 
	      	* Not used, included because overrides IEntity pure virtual method 
	     	*
	      	* @return The entity's name
	      	*/
	  		const std::string& GetName();  

	  	  	/**
		  	* @brief Gets the entity's radius    
	      	* 
	 	  	* Used to get package's and customer's radius 
	      	*
	      	* @return The entity's radius
	      	*/
	  		float GetRadius() const;

	  	  	/**
		  	* @brief Gets the version    
	      	* 
		  	* Used for the Observer Pattern 
	     	*
	      	* @return The version 
	      	*/
	  		int GetVersion() const;

	  	  	/**
		  	* @brief Determines whether the entity is moving     
	      	* 
	 	  	* Used to check if carrier entity is moving 
	      	*
	      	* @return true or false depending on if the entity is moving
	      	*/
	  		bool IsDynamic() const; 

		  	/**
		  	* @brief Sets the details of an entity 
		  	* 
		  	* @param obj: a picojson::object pointer
		  	* NOT USED
		  	* 
		  	*/
		  	void SetDetails(const picojson::object& obj);

		  	/**
		  	* @brief Sets an entity's ID to a unique integer 
		  	* 
		  	* @param id: a unique integer 
		  	* 
		  	*/			
		  	void SetId(int id);
			/**
		  	* @brief Sets an entity's color to a hexidecimal color code 
		  	* 
		  	* @param color: Hexidecimal color code  
		  	* 
		  	*/
			void SetColor(std::string color);

		  	/**
		  	* @brief Sets the version
		  	* 
		  	* @param val: integer that represents the version 
		  	* Used for the Observer Pattern 
		  	* 
		  	*/
		  	void SetVersion(int val);

			//VIRTUAL METHOD 
		  	/**
		  	* @brief Sets whether the entity is moving or not  
		  	* 
		  	* @param val: true or false depending on whether the entity should be moving   
		  	*
		  	* Used to change the state of the entity to moving or not moving 
		  	* 
		  	*/
			virtual void SetDynamic(bool val) = 0;

			/**
			* @brief gets the destination of an entity in the simulation
			* 
			* @return returns a vector of three floats that represents a coordinate in the simulation
			*/
			std::vector<float> GetDestination();

	 	protected:
	  		picojson::object details_; 
	  		int id_ = -99; 
	  		std::string name; 
	  		float radius; 
			int version = 0;
			bool dynamic = false; 
	};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
