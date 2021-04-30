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
    std::vector<float> drone_position_to_add;
    drone_position_to_add.push_back(498.292);
    drone_position_to_add.push_back(253.883);
    drone_position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "position", drone_position_to_add);
    std::vector<float> drone_direction_to_add;
    drone_direction_to_add.push_back(1);
    drone_direction_to_add.push_back(0);
    drone_direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "direction", drone_direction_to_add);
    JsonHelper::AddFloatToJsonObject(droneObj, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(droneObj, "radius", 1.0);
    Drone drone = Drone(drone_position_to_add, drone_direction_to_add, droneObj);

    //package setup
    picojson::object packageObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(packageObj, "type", "package");
    std::vector<float> package_position_to_add;
    package_position_to_add.push_back(-951.412);
    package_position_to_add.push_back(254.665);
    package_position_to_add.push_back(298.271);
    JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "position", package_position_to_add);
    std::vector<float> package_direction_to_add;
    package_direction_to_add.push_back(1);
    package_direction_to_add.push_back(0);
    package_direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "direction", package_direction_to_add);
    JsonHelper::AddFloatToJsonObject(packageObj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(packageObj, "weight", 1.0);
    Package package = Package(package_position_to_add, package_direction_to_add, 5.0, nullptr, packageObj);

    //customer setup
    picojson::object customerObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(customerObj, "type", "customer");
    std::vector<float> customer_position_to_add;
    customer_position_to_add.push_back(-951.412);
    customer_position_to_add.push_back(254.665);
    customer_position_to_add.push_back(298.271);
    JsonHelper::AddStdFloatVectorToJsonObject(customerObj, "position", customer_position_to_add);
    JsonHelper::AddFloatToJsonObject(customerObj, "radius", 1.0);

    Customer customer = Customer(customer_position_to_add, customerObj);

    //robot setup
    picojson::object robotObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(robotObj, "type", "robot");
    std::vector<float> robot_position_to_add;
    robot_position_to_add.push_back(498.292);
    robot_position_to_add.push_back(253.883);
    robot_position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "position", robot_position_to_add);
    std::vector<float> robot_direction_to_add;
    robot_direction_to_add.push_back(1);
    robot_direction_to_add.push_back(0);
    robot_direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "direction", robot_direction_to_add);
    JsonHelper::AddFloatToJsonObject(robotObj, "speed", 30.0);
    JsonHelper::AddFloatToJsonObject(robotObj, "radius", 1.0);

    Robot robot = Robot(robot_position_to_add, robot_direction_to_add, robotObj);
    
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