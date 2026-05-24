#include "Pilot.hpp"

//********** Rule of 5 ***************** */

Pilot::Pilot(std::string id, std::string name, double maxHours, 
             std::string license, std::string model)
    : CrewMember(id, name, 0.0, maxHours), //current hours = 0
      licenseNumber(license), 
      aircraftModel(model) 
{}


Pilot::Pilot(const Pilot& other):CrewMember(other) 
{
    this->licenseNumber = other.licenseNumber;
    this->aircraftModel = other.aircraftModel;
}

Pilot& Pilot::operator=(const Pilot& other) {
    if (this != &other) {
        CrewMember::operator=(other); 
        this->licenseNumber = other.licenseNumber;
        this->aircraftModel = other.aircraftModel;
    }
    return *this;
}


Pilot::~Pilot() {}


//************** Getters and Setters ************** */

std::string Pilot::getLicenseNumber() const {
    return this->licenseNumber;
}

std::string Pilot::getAircraftModel() const {
    return this->aircraftModel;
}

void Pilot::setLicenseNumber(const std::string& license) {
    this->licenseNumber = license;
}

void Pilot::setAircraftModel(const std::string& model) {
    this->aircraftModel = model;
}


//************ Virtual Overrides ******************/

void Pilot::showStaffProfile() const {
    std::cout << "--- PILOT STAFF PROFILE ---" << std::endl;
    std::cout << "ID: " << getEmployeeID() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Role: " << getStaffRole() << std::endl;
    std::cout << "License Number: " << this->licenseNumber << std::endl;
    std::cout << "Certified Aircraft Model: " << this->aircraftModel << std::endl;
    std::cout << "Flight Hours: " << getCurrentFlightHours() << " / " << getMaxAllowedHours() << " hrs" << std::endl;
}

std::string Pilot::getStaffRole() const {
    return "Pilot";
}