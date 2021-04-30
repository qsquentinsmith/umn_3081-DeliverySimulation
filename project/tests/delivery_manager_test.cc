#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class DeliveryManagerTest : public ::testing::Test {
   protected:
    Drone* drone;
    Drone* drone2;
    picojson::object obj;
    Package* package;
    Package* package2;
    picojson::object obj1;
    
    virtual void SetUp() {

    //drone setup 
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    std::vector<float> positionToAdd;
    positionToAdd.push_back(498.292);
    positionToAdd.push_back(253.883);
    positionToAdd.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);
    std::vector<float> directionToAdd;
    directionToAdd.push_back(1);
    directionToAdd.push_back(0);
    directionToAdd.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", directionToAdd);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    drone = new Drone(positionToAdd, directionToAdd, obj); 
    drone2 = new Drone(positionToAdd, directionToAdd, obj);

    

    //package setup 
    obj1 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj1, "type", "package");
    
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "position", positionToAdd);
    
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "direction", directionToAdd);
    JsonHelper::AddFloatToJsonObject(obj1, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(obj1, "radius", 1.0);

    Customer* customer = nullptr; 
    float weight = 5.0; 

    package = new Package(positionToAdd, directionToAdd, weight, customer, obj1); 
    package2 = new Package(positionToAdd, directionToAdd, weight, customer, obj1);
    }
    virtual void TearDown() {
      delete drone;
      delete drone2;
      delete package;
      delete package2;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //Testing drone constructor
  TEST_F(DeliveryManagerTest, FunctionTests) {
    Observer* observer_ = new Observer();
	DeliveryManager* deliveryManager = new DeliveryManager(observer_);

    
    deliveryManager->AddWaitingCarrier((IEntity*) drone);
    deliveryManager->AddWaitingCarrier((IEntity*) drone2);
    ASSERT_NE(deliveryManager->RemoveWaitingCarrier(), nullptr) << "addwaitingcarriers";

    
    deliveryManager->AddWaitingPackage((IEntity*) package);
    deliveryManager->AddWaitingPackage((IEntity*) package2);
    ASSERT_NE(deliveryManager->RemoveWaitingPackage(), nullptr) << "addwaitingpackage";

    ASSERT_NE(deliveryManager->GetFirstCarrierAvailable(), nullptr);
    
  }




}  // namespace csci3081