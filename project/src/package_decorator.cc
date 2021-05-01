#include "package_decorator.h"

namespace csci3081 {
    PackageDecorator::PackageDecorator(EntityBase* package) {
        package_ = package; 
    }

    const vector<float>& PackageDecorator::GetPosition() const {
        return package_->GetPosition(); 
    }

	const vector<float>& PackageDecorator::GetDirection() const {
        return package_->GetDirection(); 
    }

    void PackageDecorator::SetDynamic(bool val) {
        package_->SetDynamic(val); 
    }

}