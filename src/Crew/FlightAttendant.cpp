#include "FlightAttendant.hpp"

//********** Rule of 5 ***************** */

FlightAttendant::FlightAttendant(std::string id, std::string name, double maxHours, 
                                 std::vector<std::string> languages)
    : CrewMember(id, name, 0.0, maxHours), 
      languagesSpoken(languages)
{}


FlightAttendant::FlightAttendant(const FlightAttendant& other)
    : CrewMember(other) 
{
    this->languagesSpoken = other.languagesSpoken; 
}


FlightAttendant& FlightAttendant::operator=(const FlightAttendant& other) 
{
    if (this != &other) {
        CrewMember::operator=(other); 
        this->languagesSpoken = other.languagesSpoken;
    }
    return *this;
}


FlightAttendant::~FlightAttendant() {}


//************** Getters and Setters ************** */

std::vector<std::string> FlightAttendant::getLanguagesSpoken() const 
{
    return this->languagesSpoken;
}

void FlightAttendant::setLanguagesSpoken(const std::vector<std::string>& languages) 
{
    this->languagesSpoken = languages;
}

void FlightAttendant::addLanguagesSpoken(const std::string& language)
{
    this->languagesSpoken.push_back(language);
}

//************ Virtual Overrides ******************/
void FlightAttendant::showStaffProfile() const 
{
    std::cout << "--- FLIGHT ATTENDANT STAFF PROFILE ---" << std::endl;
    std::cout << "ID: " << getEmployeeID() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Role: " << getStaffRole() << std::endl;
    
    // Print languages 
    std::cout << "Languages Spoken: ";
    if (this->languagesSpoken.empty()) 
    {
        std::cout << "None specified";
    } 
    else 
    {
        for (int i = 0; i < this->languagesSpoken.size(); i++) 
        {
            std::cout << this->languagesSpoken[i];
            if (i < this->languagesSpoken.size() - 1) 
            {
                std::cout << ", "; // Add comma except for the last lang
            }
        }
    }
    std::cout << std::endl;
    
    std::cout << "Flight Hours: " << getCurrentFlightHours() << " / " << getMaxAllowedHours() << " hrs" << std::endl;
}

std::string FlightAttendant::getStaffRole() const 
{
    return "Flight Attendant";
}

