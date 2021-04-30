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
      Customer* customer;
      picojson::object obj;

    virtual void SetUp() {
      obj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj, "type", "customer");
      std::vector<float> positionToAdd;
      positionToAdd.push_back((float)-951.412);
      positionToAdd.push_back((float)254.665);
      positionToAdd.push_back((float)298.271);
      JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);

      customer = new Customer(positionToAdd, obj);
      
    }
    virtual void TearDown() {
      delete customer;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(CustomerFactoryTest, CreateEntityTest) {
    CustomerFactory customerFactory;
    IEntity* customerFromFactory;
    
    customerFromFactory = customerFactory.CreateEntity(obj);

    /*** CreateEntity() ***/
    ASSERT_NE(customerFromFactory, nullptr);

    ASSERT_FLOAT_EQ(customer->GetPosition()[0], customerFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(customer->GetPosition()[1], customerFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(customer->GetPosition()[2], customerFromFactory->GetPosition().at(2));
  }

}  // namespace csci3081