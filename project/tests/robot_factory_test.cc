#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "robot_factory.h"
#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class RobotFactoryTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //Testing CreateEntity
  TEST_F(RobotFactoryTest, CreateEntityTest) {

    //setting up picojson::object for creat identity
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "robot");
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
    Robot robot = Robot(positionToAdd, directionToAdd, obj);

    RobotFactory robotFactory;
    IEntity* robotFromFactory = robotFactory.CreateEntity(obj);


    // checking if values are set properly
    ASSERT_FLOAT_EQ(robot.GetPosition()[0], robotFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(robot.GetPosition()[1], robotFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(robot.GetPosition()[2], robotFromFactory->GetPosition().at(2));
    ASSERT_FLOAT_EQ(robot.GetDirection()[0], robotFromFactory->GetDirection().at(0));
    ASSERT_FLOAT_EQ(robot.GetDirection()[1], robotFromFactory->GetDirection().at(1));
    ASSERT_FLOAT_EQ(robot.GetDirection()[2], robotFromFactory->GetDirection().at(2));

  }

}  // namespace csci3081