#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "customer_factory.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class CustomerFactoryTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //Testing CreateEntity
  TEST_F(CustomerFactoryTest, CreateEntityTest) {

    //setting up picojson::object for creat identity
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    std::vector<float> positionToAdd;
    positionToAdd.push_back((float)-951.412);
    positionToAdd.push_back((float)254.665);
    positionToAdd.push_back((float)298.271);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);

    Customer customer = Customer(positionToAdd, obj);

    CustomerFactory customerFactory;
    IEntity* customerFromFactory = customerFactory.CreateEntity(obj);

    //checks that factory didnt return a nullptr

    // checking if values are set properly
    ASSERT_FLOAT_EQ(customer.GetPosition()[0], customerFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(customer.GetPosition()[1], customerFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(customer.GetPosition()[2], customerFromFactory->GetPosition().at(2));

  }

}  // namespace csci3081