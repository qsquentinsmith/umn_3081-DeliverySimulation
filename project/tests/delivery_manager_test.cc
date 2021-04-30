#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
//#include "drone.h"

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
    std::vector<float> position_to_add;
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    drone = new Drone(position_to_add, direction_to_add, obj); 
    drone2 = new Drone(position_to_add, direction_to_add, obj);

  
    //package setup 
    obj1 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj1, "type", "package");
    
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "position", position_to_add);
    
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj1, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(obj1, "radius", 1.0);
    
    Customer* customer = nullptr; 
    float weight = 5.0; 

    package = new Package(position_to_add, direction_to_add, weight, customer, obj1); 
    package2 = new Package(position_to_add, direction_to_add, weight, customer, obj1);
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
  
  TEST_F(DeliveryManagerTest, ConstuctorTest) {
    Observer* observer_ = new Observer();
	  DeliveryManager* deliveryManager = new DeliveryManager(observer_);

    /*** Constructor **/
    ASSERT_NE(observer_, nullptr);
    ASSERT_NE(deliveryManager, nullptr);
   
  }


   TEST_F(DeliveryManagerTest, AddWaitingCarrierTest) {
    Observer* observer_ = new Observer();
	  DeliveryManager* deliveryManager = new DeliveryManager(observer_);

    /*** AddWaitingCarrier(), RemoveWaitingCarrier() ***/
    deliveryManager->AddWaitingCarrier((IEntity*) drone);
    deliveryManager->AddWaitingCarrier((IEntity*) drone2);
    ASSERT_EQ(deliveryManager->RemoveWaitingCarrier(), drone);

  }


  TEST_F(DeliveryManagerTest, RemoveWaitingCarrierTest) {
    Observer* observer_ = new Observer();
	  DeliveryManager* deliveryManager = new DeliveryManager(observer_);

    /*** AddWaitingCarrier(), RemoveWaitingCarrier() ***/
    deliveryManager->AddWaitingCarrier((IEntity*) drone);
    deliveryManager->AddWaitingCarrier((IEntity*) drone2);
    ASSERT_EQ(deliveryManager->RemoveWaitingCarrier(), drone);

    /*** AddWaitingPackage(), RemoveWaitingPackage() ***/
    deliveryManager->AddWaitingPackage((IEntity*) package);
    deliveryManager->AddWaitingPackage((IEntity*) package2);
    ASSERT_EQ(deliveryManager->RemoveWaitingPackage(), package);
  }


  TEST_F(DeliveryManagerTest, GetFirstCarrierAvailableTest) {
    Observer* observer_ = new Observer();
	  DeliveryManager* deliveryManager = new DeliveryManager(observer_);

    /*** AddWaitingCarrier(), RemoveWaitingCarrier() ***/
    deliveryManager->AddWaitingCarrier((IEntity*) drone);
    deliveryManager->AddWaitingCarrier((IEntity*) drone2);
 
    /*** AddWaitingPackage(), RemoveWaitingPackage() ***/
    deliveryManager->AddWaitingPackage((IEntity*) package);
    deliveryManager->AddWaitingPackage((IEntity*) package2);
  
    /*** GetFirstCarrierAvailable() ***/
    ASSERT_EQ(deliveryManager->GetFirstCarrierAvailable(), drone);
  }


    /** note: Public functions not included are 
    - IsTypeCarrier() (private helper function), 
    - AddCarrierAndPackage() (relies on many outside classes), 
    - MoveCarriersAndPackages() (relies on many outside classes)
    */



}  // namespace csci3081