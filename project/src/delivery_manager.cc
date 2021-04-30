#include "drone.h"
#include "robot.h"
#include "package.h"
#include "delivery_manager.h"
#include "json_helper.h"

namespace csci3081 {
    DeliveryManager::DeliveryManager(Observer* observer) {
        carrierTypes.push_back("drone"); 
        carrierTypes.push_back("robot"); 

        observer_ = observer;
    }

	//returns whether the given string is a carrier type (e.g. drone)
    bool DeliveryManager::IsTypeCarrier(string carrier) {
        for (int i = 0; i < carrierTypes.size(); i++) {
            if (carrierTypes.at(i) == carrier) {
                return true;
            }
        }
        return false; 
    }

    // returns carrier to be used in Schedule Delivery 
	IEntity* DeliveryManager::GetFirstCarrierAvailable() {
		if(waiting_carriers_.size() > 0){
			if ((waiting_carriers_.at(0))->IsDynamic() == false && ((Carrier*)waiting_carriers_.at(0))->IsScheduled() == false) {
				((Carrier*)waiting_carriers_.at(0))->SetScheduled(true);
				return RemoveWaitingCarrier();
			}	
  		}
		return nullptr; 
	}
		
	//carrier and package added to corresponding indices in their respective vectors
	void DeliveryManager::AddCarrierAndPackage(IEntity* carrier, IEntity* package) {
		carriers_.push_back(carrier);
		packages_.push_back(package);

		vector<float> carrierPosition = carrier->GetPosition(); 
		vector<float> packagePosition = package->GetPosition();
		vector<float> customerPosition = ((Package *) package)->GetCustomer()->GetPosition();
		EntityBase* base_package = dynamic_cast<EntityBase*>(package); //casted to access SetVersion
		vector<vector<float>> route; 

		//Edge Case 2: package already at drone location 
		if (carrierPosition == packagePosition) {
			route = ((Carrier *) carrier)->GetRoute(carrierPosition, customerPosition);
			((Carrier *) carrier)->SetRoute(route); 
			base_package->SetDynamic(true); 
		}
		//Normal movement from drone to package 
		else {
			route = ((Carrier *) carrier)->GetRoute(carrierPosition, packagePosition);
			((Carrier *) carrier)->SetRoute(route);
		}
		((Carrier *) carrier)->SetVersion(1); //IS THIS STILL CORRECT FOR EDGE CASE?

		base_package->SetVersion(1); //IS THIS STILL CORRECT FOR EDGE CASE?
	}

	//adds excess packages to separate vector 
	void DeliveryManager::AddWaitingPackage(IEntity* package) {
		waiting_packages_.push_back(package); 
	}

	//adds excess packages to separate vector 
	void DeliveryManager::AddWaitingCarrier(IEntity* carrier) {
		waiting_carriers_.push_back(carrier); 
	}

	//removes first package in vector of waiting packages 
	IEntity* DeliveryManager::RemoveWaitingPackage() {
		IEntity* removed = waiting_packages_.at(0);
		waiting_packages_.erase(waiting_packages_.begin());
		return removed; 
	}

	//removes first package in vector of waiting packages 
	IEntity* DeliveryManager::RemoveWaitingCarrier() {
		IEntity* removed = waiting_carriers_.at(0);
		waiting_carriers_.erase(waiting_carriers_.begin());
		return removed; 
	}

	//loops through carriers and moves them along with their associated packages 
	void DeliveryManager::MoveCarriersAndPackages(float dt) {
		for (int i = 0; i < carriers_.size(); i++) {
			Carrier* carrier = (Carrier*) carriers_.at(i); 
			Package* package = (Package*) packages_.at(i); 
			EntityBase* base_package = dynamic_cast<EntityBase*>(package);

			//Edge Case 1: package and customer at same location
			if (package->GetPosition() == package->GetCustomer()->GetPosition()) { 
				//drone stops moving 
				carrier->SetDynamic(false); 

				//*****Notify package delivered*****
				observer_->Delivered(packages_.at(i));
				//*****Notify carrier idle*****
				observer_->Idle(carriers_.at(i));

				package->SetDynamic(true);
				//package moved out of scene 
				
				vector<float> removed_location;
			 	removed_location.push_back(10000);
		 	 	removed_location.push_back(10000);
	      		removed_location.push_back(10000);
				package->SetPosition(removed_location);
				
				//carrier now ready for another delivery 
				waiting_carriers_.push_back(carriers_.at(i));

				//removed from respective lists 
				carriers_.erase(carriers_.begin()+i);
			 	packages_.erase(packages_.begin()+i);
			}

			else {

				if (carrier->IsDynamic() == false) {
					carrier->SetDynamic(true); 
				}

				//moves carrier 
				bool reachedDestination = carrier->Move(dt); 

				if (carrier->GetBattery()->IsDead()){
					carrier->SetDynamic(false);
					package->SetDynamic(false);
					
					//*****Notify carrier idle*****
					observer_->Idle(carriers_.at(i));

					carriers_.erase(carriers_.begin()+i);

					waiting_packages_.push_back(packages_.at(i));
					packages_.erase(packages_.begin()+i);

					if (waiting_packages_.size() > 0 && waiting_carriers_.size() > 0) {
						AddCarrierAndPackage(RemoveWaitingCarrier(), RemoveWaitingPackage());
					}
				}

				//*****Notify carrier move*****
				if(carrier->GetVersion() == 1) {
					observer_->Moving(carriers_.at(i), carrier->GetRoute());
					carrier->SetVersion(0);
				}

				//reached package + rerouting to customer 
				if (reachedDestination && package->IsDynamic() == false) {
					//call decorator function 
					decorator->GetDecoratedPackage(package); 
					observer_->ColorChange((IEntity*)package);
					package->SetDynamic(true);
					vector<float> carrierPosition = carrier->GetPosition(); 
					vector<float> customerPosition = package->GetCustomer()->GetPosition(); 
					package->SetPosition(carrierPosition);

					vector<vector<float>> route = ((Carrier *) carrier)->GetRoute(carrierPosition, customerPosition); 
					((Carrier *) carrier)->SetRoute(route); 
					//*****Notify package en route*****
					if(base_package->GetVersion() == 1) {
						observer_->EnRoute(packages_.at(i));
						base_package->SetVersion(0);
						carrier->SetVersion(1);
					}
				}

				//package moving to customer 
				else if (reachedDestination == false && package->IsDynamic()) {
					vector<float> carrierPosition = carrier->GetPosition();
					package->SetPosition(carrierPosition);
				}

				//reached customer 
				else if (reachedDestination && package->IsDynamic()) {
					//drone stops moving 
					vector<float> setStraight;
					setStraight.push_back(0);
					setStraight.push_back(1);
					setStraight.push_back(0);
					carrier->SetDirection(setStraight);

					carrier->SetDynamic(false); 

					//*****Notify package delivered*****
					observer_->Delivered(packages_.at(i));
					//*****Notify carrier idle*****
					observer_->Idle(carriers_.at(i));

					//package moved out of scene 
					vector<float> removed_location;
					removed_location.push_back(10000);
					removed_location.push_back(10000);
					removed_location.push_back(10000);
					package->SetPosition(removed_location);

					//removed from respective lists 
					waiting_carriers_.push_back(carriers_.at(i));

					carriers_.erase(carriers_.begin()+i);
					packages_.erase(packages_.begin()+i);

					if (waiting_packages_.size() > 0 && waiting_carriers_.size() > 0) {
						AddCarrierAndPackage(RemoveWaitingCarrier(), RemoveWaitingPackage());
					} 
					i--; //to loop again 
				}//else if reached customer
			}//else (not edge case)
		}//for 
	}//method

}//namespace

