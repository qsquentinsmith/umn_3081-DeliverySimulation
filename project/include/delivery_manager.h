/**
 *@file delivery_manager.h
 */
#ifndef DELIVERY_MANAGER_H_
#define DELIVERY_MANAGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include "observer.h"
using std::string; 
#include "decorator_factory.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The DeliveryManager Class is a helper class which aids in delivery scheduling and movement. 
 * 
 */ 
	class DeliveryManager {
		public:
			/**
			* @brief Constructor  
			* 
			* @param observer: observer pointer
			*
			*/
            DeliveryManager(Observer* observer); 

			/**
			* @brief Gets the first carrier entity available to deliver a package from the list of entities
			* (current possibilities are drones and robots)   
			* 
			* @param entities: list of entities in the simulation 
			*
			* Used to schedule a carrier entity for package delivery 
			*
			* @return A pointer to the carrier entity that is casted as an IEntity pointer  
			*/
			IEntity* GetFirstCarrierAvailable(); 

			/**
			* @brief Adds the carrier entity and package to their respective lists managed by this class   
			* 
			* @param carrier: carrier entity pointer to be added (currently either drone or robot)
			* @param package: package pointer to be added 
			*
			* Used while scheduling a delivery 
			* (the entities in their respective lists are the ones that are currently moving) 
			*
			*/
			void AddCarrierAndPackage(IEntity* carrier, IEntity* package);

			/**
			* @brief Adds packages to an IEntity pointer vector. This list is the master list of all packages. Packages will be taken
			* from this list to schedule deliveries.
			*  
			* @param package: package pointer to be added 
			*
			*/
			void AddWaitingPackage(IEntity* package); 

			/**
			* @brief Adds carriers to an IEntity pointer vector. This list is the master list of all carriers. Carriers will be taken
			* from this list to deliver packages.
			*  
			* @param carrier: carrier pointer to be added 
			*
			*/
			void AddWaitingCarrier(IEntity* carrier); 

			/**
			* @brief Removes package from package waiting list. 
			*  
			* @return IEntity package pointer
			*
			*/
			IEntity* RemoveWaitingPackage(); 

			/**
			* @brief Removes carrier from carrier waiting list. 
			*  
			* @return IEntity carrier pointer
			*
			*/
			IEntity* RemoveWaitingCarrier(); 

			/**
			* @brief Moves the carriers and packages as necessary    
			* 
			* @param dt: change in time used for movement 
			*
			* Used to update the movement of carriers that are occupied along with their packages  
			*
			*/
			void MoveCarriersAndPackages(float dt);
			/**
			* @brief Sets route for carrier   
			* 
			* @param route: path to be set to route 
			*
			*/
			void SetRoute(std::vector<Vector3D> route);

			/**
			* @brief Gets route for carrier   
			* 
			* @return route 
			*
			*/
			std::vector<Vector3D> GetRoute();

		private:
            vector<string> carrierTypes; 
            
			vector<IEntity*> carriers_; 
			vector<IEntity*> packages_; 
			vector<IEntity*> waitingPackages;
			vector<IEntity*> waitingCarriers;
  			std::vector<IEntityObserver*> observers_;
			std::vector<Vector3D> route_;
			Observer* observer_;
			DecoratorFactory* decoratorFactory;

			/**
			* @brief Checks if the string passed in is a type of carrier
			* 
			* @param carrier: string to be checked if it is a type of carrier
			* 
			*/
			bool IsTypeCarrier(string carrier); //PRIVATE HELPER METHOD
			/**
			* @brief Handles Edge case when the package is in the same location of the Carrier in the scene
			* 
			* @param Carrier: pointer to the carrier being moved
			* @param Package: pointer to the package being moved
			* @param i: iterator for carriers and packages in scene
			* 
			*/
			void PackageCarrierSameLocation(Carrier* carrier, Package* package, int i);
			/**
			* @brief initiates sequence of events when carrier battery dies
			* 
			* @param Carrier: pointer to the carrier being moved
			* @param Package: pointer to the package being moved
			* @param i: iterator for carriers and packages in scene
			* 
			*/
			void DeadBattery(Carrier* carrier, Package* package, int i);
			/**
			* @brief Initiates sequence of events when Carrier arrives at Package
			* 
			* @param Carrier: pointer to the carrier being moved
			* @param Package: pointer to the package being 
			* @param i: iterator for carriers and packages in scene
			* 
			*/
			void CarrierArrivedAtPackage(Carrier* carrier, Package* package, int i);
			/**
			* @brief Initiates sequence of events when Carrier Arives at Customer
			* 
			* @param Carrier: pointer to the carrier being moved
			* @param Package: pointer to the package being 
			* @param i: iterator for carriers and packages in scene
			* 
			*/
			void CarrierArrivedAtCustomer(Carrier* carrier, Package* package, int i); 
	}; //class

} //namespace 

#endif  // DELIVERY_MANAGER_H_