#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "istrategy.h"
#include "beeline.h"
#include "smart_path.h"
#include "parabolic.h"
#include "drone.h"
#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class StrategyTest : public ::testing::Test {
      
    protected:
      std::vector<float> source;
      std::vector<float> target;
        
      virtual void SetUp() {
        source.push_back(0);
        source.push_back(0);
        source.push_back(0);

        target.push_back(100);
        target.push_back(0);
        target.push_back(100);

    }
    virtual void TearDown() {
      
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(StrategyTest, ParabolicTest) {
    IStrategy* strategy = new Parabolic(); 

    /*** GetRoute(): for parabolic ***/
    std::vector<std::vector<float>> route = strategy->GetRoute(source, target);
    ASSERT_EQ(route.size(), 41) <<"check parabolic size";

    /*** Check random vectors in vector route ***/
    ASSERT_FLOAT_EQ(route[0][0], 0);
    ASSERT_FLOAT_EQ(route[0][1], 0);
    ASSERT_FLOAT_EQ(route[0][2], 0);

    ASSERT_FLOAT_EQ(route[10][0], 24.390242);
    ASSERT_FLOAT_EQ(route[10][1], 73.76561);
    ASSERT_FLOAT_EQ(route[10][2], 24.390242);

    ASSERT_FLOAT_EQ(route[20][0], 48.780483);
    ASSERT_FLOAT_EQ(route[20][1], 99.940514);
    ASSERT_FLOAT_EQ(route[20][2], 48.780483);

    ASSERT_FLOAT_EQ(route[30][0], 73.170723);
    ASSERT_FLOAT_EQ(route[30][1], 78.524704);
    ASSERT_FLOAT_EQ(route[30][2], 73.170723);

    ASSERT_FLOAT_EQ(route[40][0], 97.560966);
    ASSERT_FLOAT_EQ(route[40][1], 9.5181646);
    ASSERT_FLOAT_EQ(route[40][2], 97.560966);
  }


TEST_F(StrategyTest, Beeline) {
    IStrategy* strategy = new Beeline(); 
    
    /*** GetRoute(): for beeline ***/
    std::vector<std::vector<float>> route = strategy->GetRoute(source, target);
    ASSERT_EQ(route.size(), 4) << "Check beeline size";

    /*** Check vectors in vector route ***/
    ASSERT_EQ(route[0][0], 0);
    ASSERT_EQ(route[0][1], 0);
    ASSERT_EQ(route[0][2], 0);

    ASSERT_EQ(route[1][0], 0);
    ASSERT_EQ(route[1][1], 350);
    ASSERT_EQ(route[1][2], 0);

    ASSERT_EQ(route[2][0], 100);
    ASSERT_EQ(route[2][1], 350);
    ASSERT_EQ(route[2][2], 100);

    ASSERT_EQ(route[3][0], 100);
    ASSERT_EQ(route[3][1], 0);
    ASSERT_EQ(route[3][2], 100);
  }

/***** Smart Test for drone and robot are not tested to reliance on IGraph class ***/



}  // namespace csci3081