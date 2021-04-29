#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "entity_base.h"
#include "observer.h"


#include <iostream>
#include <string>

namespace csci3081 {

using entity_project::IEntity;

class ObserverTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    observer_ = new Observer();
    new_observer = nullptr;
    entity_ = nullptr;

  }
  virtual void TearDown() {
    delete observer_;
  }

  Observer* observer_;
  IEntityObserver* new_observer;
  IEntity* entity_;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ObserverTest, AddObserverTest) {
  EXPECT_EQ(observer_->GetObserverList().size(), 0);
  observer_->AddObserver(new_observer);
  EXPECT_EQ(observer_->GetObserverList().size(), 1);
}

TEST_F(ObserverTest, RemoveObserverTest) {
  EXPECT_EQ(observer_->GetObserverList().size(), 0);
  observer_->AddObserver(new_observer);
  EXPECT_EQ(observer_->GetObserverList().size(), 1);
  observer_->RemoveObserver(new_observer);
  EXPECT_EQ(observer_->GetObserverList().size(), 0);
}

TEST_F(ObserverTest, ScheduledTest) {
  observer_->Scheduled(entity_);
  picojson::object obj = observer_->GetJsonObject();

  EXPECT_EQ(JsonHelper::ContainsKey(obj, "value"), true);
  EXPECT_EQ(JsonHelper::GetString(obj, "value"), "scheduled");
}

TEST_F(ObserverTest, MovingTest) {
  std::vector<float> point;
  point.push_back(0);
  point.push_back(0);
  point.push_back(0);
  std::vector<std::vector<float>> route;
  route.push_back(point);

  observer_->Moving(entity_, route);
  picojson::object obj = observer_->GetJsonObject();
  picojson::object route_obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStdVectorVectorFloatToJsonObject(route_obj, "path", route);

  EXPECT_EQ(JsonHelper::ContainsKey(obj, "value"), true);
  EXPECT_EQ(JsonHelper::GetString(obj, "value"), "moving");
  EXPECT_EQ(JsonHelper::ContainsKey(obj, "path"), true);
  EXPECT_EQ(JsonHelper::GetValue(obj, "path").serialize(), JsonHelper::GetValue(route_obj, "path").serialize());
}

TEST_F(ObserverTest, EnRouteTest) {
  observer_->EnRoute(entity_);
  picojson::object obj = observer_->GetJsonObject();

  EXPECT_EQ(JsonHelper::ContainsKey(obj, "value"), true);
  EXPECT_EQ(JsonHelper::GetString(obj, "value"), "en route");
}

TEST_F(ObserverTest, DeliveredTest) {
  observer_->Delivered(entity_);
  picojson::object obj = observer_->GetJsonObject();

  EXPECT_EQ(JsonHelper::ContainsKey(obj, "value"), true);
  EXPECT_EQ(JsonHelper::GetString(obj, "value"), "delivered");
}

TEST_F(ObserverTest, IdleTest) {
  observer_->Idle(entity_);
  picojson::object obj = observer_->GetJsonObject();

  EXPECT_EQ(JsonHelper::ContainsKey(obj, "value"), true);
  EXPECT_EQ(JsonHelper::GetString(obj, "value"), "idle");
}

TEST_F(ObserverTest, ColorChangeTest) {
  //setting up package
  picojson::object obj1 = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj1, "type", "package");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj1, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj1, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj1, "radius", 1.0);
  float weight = 5.0; 
  Package* package = new Package(position_to_add, direction_to_add, weight, nullptr, obj1);

  

  observer_->ColorChange(((IEntity*)package));
  picojson::object obj = observer_->GetJsonObject();

  EXPECT_EQ(JsonHelper::ContainsKey(obj, "value"), true);
  EXPECT_EQ(JsonHelper::GetString(obj, "value"), "updateDetails");
  EXPECT_EQ(JsonHelper::ContainsKey(obj, "details"), true);
  EXPECT_EQ(JsonHelper::GetValue(obj, "details").serialize(), picojson::value(((EntityBase*) package)->GetDetails()).serialize());
}

}  // namespace csci3081