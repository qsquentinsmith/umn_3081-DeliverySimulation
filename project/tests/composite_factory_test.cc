#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "composite_factory.h"
#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class CompositeFactoryTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/

  //testing CreateEntity
  TEST_F(CompositeFactoryTest, CreateEntityTest) {

    //drone setup
    picojson::object droneObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(droneObj, "type", "drone");
    std::vector<float> dronePositionToAdd;
    dronePositionToAdd.push_back(498.292);
    dronePositionToAdd.push_back(253.883);
    dronePositionToAdd.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "position", dronePositionToAdd);
    std::vector<float> droneDirectionToAdd;
    droneDirectionToAdd.push_back(1);
    droneDirectionToAdd.push_back(0);
    droneDirectionToAdd.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "direction", droneDirectionToAdd);
    JsonHelper::AddFloatToJsonObject(droneObj, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(droneObj, "radius", 1.0);
    Drone drone = Drone(dronePositionToAdd, droneDirectionToAdd, droneObj);

    //package setup
    picojson::object packageObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(packageObj, "type", "package");
    std::vector<float> packagePositionToAdd;
    packagePositionToAdd.push_back(-951.412);
    packagePositionToAdd.push_back(254.665);
    packagePositionToAdd.push_back(298.271);
    JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "position", packagePositionToAdd);
    std::vector<float> packageDirectionToAdd;
    packageDirectionToAdd.push_back(1);
    packageDirectionToAdd.push_back(0);
    packageDirectionToAdd.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "direction", packageDirectionToAdd);
    JsonHelper::AddFloatToJsonObject(packageObj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(packageObj, "weight", 1.0);
   
    Package package = Package(packagePositionToAdd, packageDirectionToAdd, 5.0, nullptr, packageObj);

    //customer setup
    picojson::object customerObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(customerObj, "type", "customer");
    std::vector<float> customerPositionToAdd;
    customerPositionToAdd.push_back(-951.412);
    customerPositionToAdd.push_back(254.665);
    customerPositionToAdd.push_back(298.271);
    JsonHelper::AddStdFloatVectorToJsonObject(customerObj, "position", customerPositionToAdd);
    JsonHelper::AddFloatToJsonObject(customerObj, "radius", 1.0);

    Customer customer = Customer(customerPositionToAdd, customerObj);

    //robot setup
    picojson::object robotObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(robotObj, "type", "robot");
    std::vector<float> robotPositionToAdd;
    robotPositionToAdd.push_back(498.292);
    robotPositionToAdd.push_back(253.883);
    robotPositionToAdd.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "position", robotPositionToAdd);
    std::vector<float> robotDirectionToAdd;
    robotDirectionToAdd.push_back(1);
    robotDirectionToAdd.push_back(0);
    robotDirectionToAdd.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "direction", robotDirectionToAdd);
    JsonHelper::AddFloatToJsonObject(robotObj, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(robotObj, "radius", 1.0);
    
    Robot robot = Robot(robotPositionToAdd, robotDirectionToAdd, robotObj);

    //EntityFactory set up
    CompositeFactory compositeFactory;

    DroneFactory droneFactory;
    PackageFactory packageFactory;
    CustomerFactory customerFactory;
    RobotFactory robotFactory;

    /******* Tests *******/

    /** AddFactory() **/
    compositeFactory.AddFactory(&droneFactory);
    compositeFactory.AddFactory(&packageFactory);
    compositeFactory.AddFactory(&customerFactory);
    compositeFactory.AddFactory(&robotFactory);

    /** CreateEntity(): Creating Entities with correct objects **/
    Drone* droneFromFactory = (Drone*) compositeFactory.CreateEntity(droneObj);
    Package* packageFromFactory = (Package*) compositeFactory.CreateEntity(packageObj);
    Customer* customerFromFactory = (Customer*) compositeFactory.CreateEntity(customerObj);
    Robot* robotFromFactory = (Robot*) compositeFactory.CreateEntity(robotObj);

    EXPECT_EQ(typeid(Drone*), typeid(droneFromFactory));
    EXPECT_EQ(typeid(Package*), typeid(packageFromFactory));
    EXPECT_EQ(typeid(Customer*), typeid(customerFromFactory));
    EXPECT_EQ(typeid(Robot*), typeid(robotFromFactory));

    /** CreateEntity(): Creating Entities with incorrect objects **/
    droneFromFactory = (Drone*) compositeFactory.CreateEntity(robotObj);
    packageFromFactory = (Package*) compositeFactory.CreateEntity(customerObj);
    customerFromFactory = (Customer*) compositeFactory.CreateEntity(packageObj);
    robotFromFactory = (Robot*) compositeFactory.CreateEntity(droneObj);

    EXPECT_EQ(typeid(Drone*), typeid(droneFromFactory));
    EXPECT_EQ(typeid(Package*), typeid(packageFromFactory));
    EXPECT_EQ(typeid(Customer*), typeid(customerFromFactory));
    EXPECT_EQ(typeid(Robot*), typeid(robotFromFactory));
   }

}  // namespace csci3081