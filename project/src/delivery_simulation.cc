#include "delivery_simulation.h"
#include "json_helper.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	factory = new CompositeFactory();
	AddFactory(new DroneFactory()); 
	AddFactory(new CustomerFactory());
	AddFactory(new PackageFactory()); 
	AddFactory(new RobotFactory());
	observer_ = new Observer();
	deliveryManager = new DeliveryManager(observer_);
	// decorator = new Decorator();
	// decorator->AddDecoration(new Light_Weight());
	// decorator->AddDecoration(new Middle_Weight());
	// decorator->AddDecoration(new Heavy_Weight());

}

DeliverySimulation::~DeliverySimulation() {
	delete factory; 
	delete deliveryManager; 
}

int DeliverySimulation::Uid() { 
	id_++; 
	return id_; 
}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
	std::string entityType = JsonHelper::GetString(val, "type");
	IEntity* entity_ = factory->CreateEntity(val);

	if (entityType == "drone" || entityType == "robot") {
		((Carrier*) entity_)->SetGraph(graph_);
		((Carrier*) entity_)->SetStrategy();
	}
	// else if (entityType == "package") {
	// 	// AbstractPackage* package = new PackageDecorator((AbstractPackage*)entity_); 
	// 	// AbstractPackage* decoratedPackage = nullptr; 
	// 	// if (JsonHelper::ContainsKey(((Package*)entity_)->GetDetails(), "weight")) {
	// 	// 	float weight = ((Package*) package)->GetWeight(); 
	// 	// 	if (weight >= 0.0 && weight < 2.0) {
	// 	// 		decoratedPackage = new LightWeight(package); 
	// 	// 	} 
    // 	// }

	// // 	if (decoratedPackage) { decoratedPackage->Decorate(); }

	// 	observer_->ColorChange(entity_);
	// }

	if (entity_) {
		EntityBase* base = dynamic_cast<EntityBase*>(entity_);
		base->SetId(Uid());
		return entity_; 
	}
	return NULL;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	if (this->factory) {
		this->factory->AddFactory(factory);
	}
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
 	entities_.push_back(entity);
	
	const picojson::object& obj = entity->GetDetails(); 
    std::string carrierType = JsonHelper::GetString(obj, "type"); 

	if((carrierType == "drone" || carrierType == "robot") && entity->IsDynamic() == false && ((Carrier*) entity)->IsScheduled() == false){	//remember to add trucks
		deliveryManager->AddWaitingCarrier(entity);
	}
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	graph_ = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	IEntity* carrier = nullptr; 
	((Package*) package)->SetCustomer((Customer*) dest); //gives package the customer location

	//*****Notify package scheduled*****
	observer_->Scheduled(package);

	if (deliveryManager) {
		
		carrier = deliveryManager->GetFirstCarrierAvailable(); //gets carrier to be used 
		
		if (carrier && package) {
			((Carrier*)carrier)->SetGraph(graph_);

			deliveryManager->AddCarrierAndPackage(carrier, package); //carrier and package given to DeliveryManager to move
		}// inner if 
		
		// more packages than carriers
		else {
			deliveryManager->AddWaitingPackage(package);
		}//else if
	}// outer if 
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	observer_->AddObserver(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	observer_->RemoveObserver(observer);
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { 
	return entities_; 
}

void DeliverySimulation::Update(float dt) {
	if (deliveryManager) {
		deliveryManager->MoveCarriersAndPackages(dt);
	}	
}

// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
