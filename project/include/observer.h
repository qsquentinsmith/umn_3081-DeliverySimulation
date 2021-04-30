/**
 *@file observer.h
 */
#ifndef OBSERVER_H_
#define OBSERVER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "json_helper.h"
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include "entity_base.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Observer Class is a helper class which aids in the notification of observers. 
 * 
 */ 
	class Observer {
		public:
            /**
			* @brief Adds an observer to the observers_ vector
			* 
			* @param observer: IEntityObserver pointer to be added to simulation
			*
			*/
			void AddObserver(IEntityObserver* observer);

      		/**
			* @brief Removes an observer from the observers_ vector
			* 
			* @param observer: IEntityObserver pointer to be removed to simulation
			* 
			*/
			void RemoveObserver(IEntityObserver* observer);

			/**
			* @brief Notify observers that the package was scheduled
			* 
			* @param package: IEntity pointer of package scheduled
			* 
			*/
			void Scheduled(IEntity* package);

			/**
			* @brief Notify observers that the carrier is moving
			* 
			* @param carrier: IEntity pointer of carrier moving
			* @param route: std::vector<std::vector<float>> carrier path
			* 
			*/
			void Moving(IEntity* carrier, std::vector<std::vector<float>> route);

			/**
			* @brief Notify observers that the package is moving
			* 
			* @param package: IEntity pointer of package moving
			* 
			*/
			void EnRoute(IEntity* package);

			/**
			* @brief Notify observers that the package was delivered
			* 
			* @param package: IEntity pointer of package delivered
			* 
			*/
			void Delivered(IEntity* package);

			/**
			* @brief Notify observers that the carrier is idle
			* 
			* @param carrier: IEntity pointer of the idle carrier
			* 
			*/
			void Idle(IEntity* carrier);
		
			/**
			* @brief Notify observers that the package was changed colors
			* 
			* @param package: IEntity pointer of package delivered
			* 
			*/
			void ColorChange(IEntity* package);

			/**
			* @brief Implements notification process for observers
			* 
			* @param jsonObj: picojson::object with notification data
			* @param entityObj: IEntity pointer of the entity to notify about
			* 
			*/
			void Notify(picojson::object jsonObj, IEntity* entityObj);

			/**
			* @brief Returns list of observers for testing
			* 
			* @return Vector of observers
			*/
			std::vector<IEntityObserver*> GetObserverList();

			/**
			* @brief Returns json object for testing
			* 
			* @return PicoJson Object
			*/
			picojson::object GetJsonObject();

		private:
            std::vector<IEntityObserver*> observers_;
            //used for testing
            picojson::object testObj;
	}; //class

} //namespace 

#endif  // OBSERVER_H_
