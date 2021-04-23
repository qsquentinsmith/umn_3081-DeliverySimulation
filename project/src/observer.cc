#include "observer.h"

namespace csci3081 {

void Observer::AddObserver(IEntityObserver* observer) {
	observers_.push_back(observer);
}

void Observer::RemoveObserver(IEntityObserver* observer) {
	for(int i = 0; i < observers_.size(); i++) {
		if(observers_.at(i) == observer) {
			observers_.erase(observers_.begin() + i);
		}
	}
}

void Observer::Scheduled(IEntity* package) {
	picojson::object obj = JsonHelper::CreateJsonNotification();
	JsonHelper::AddStringToJsonObject(obj, "value", "scheduled");
	Notify(obj, package);
}

void Observer::Moving(IEntity* carrier, std::vector<std::vector<float>> route) {
	picojson::object obj = JsonHelper::CreateJsonNotification();
	JsonHelper::AddStringToJsonObject(obj, "value", "moving");
	JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", route);
	Notify(obj, carrier);
}

void Observer::EnRoute(IEntity* package) {
	picojson::object obj = JsonHelper::CreateJsonNotification();
	JsonHelper::AddStringToJsonObject(obj, "value", "en route");
	Notify(obj, package);
}

void Observer::Delivered(IEntity* package) {
	picojson::object obj = JsonHelper::CreateJsonNotification();
	JsonHelper::AddStringToJsonObject(obj, "value", "delivered");
	Notify(obj, package);
}

void Observer::Idle(IEntity* carrier) {
	picojson::object obj = JsonHelper::CreateJsonNotification();
	JsonHelper::AddStringToJsonObject(obj, "value", "idle");
	Notify(obj, carrier);
}

void Observer::Notify(picojson::object jsonObj, IEntity* entityObj) {
	//for testing
	test_obj = jsonObj;

	for (int i = 0; i < observers_.size(); i++) {
		observers_.at(i)->OnEvent(picojson::value(jsonObj), *entityObj);
	}
}

std::vector<IEntityObserver*> Observer::GetObserverList() {
	return observers_;
}

picojson::object Observer::GetJsonObject() {
	return test_obj;
}

}
