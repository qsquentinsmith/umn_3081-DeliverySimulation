#include "entity_base.h"

namespace csci3081 {

  EntityBase::~EntityBase() {}

  picojson::object& EntityBase::GetDetails() { 
    return details_; 
  } 

  int EntityBase::GetId() const {
    return id_; 
  }

  const std::string& EntityBase::GetName() {
    return name; 
  }

  float EntityBase::GetRadius() const {
    return radius; 
  }

  int EntityBase::GetVersion() const {
    return version;
  }

  bool EntityBase::IsDynamic() const {
    return dynamic;
  }

  void EntityBase::SetDetails(const picojson::object& obj) {
    id_++;
  }

  void EntityBase::SetColor(std::string color){
    details_["color"] = picojson::value(color);
  }

  void EntityBase::SetId(int id) { 
    id_ = id; 
  }

  void EntityBase::SetVersion(int val) {
    version = val;
  }
  
}