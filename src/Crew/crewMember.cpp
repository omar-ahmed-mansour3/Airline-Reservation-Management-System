#include"CrewMember.hpp"

//**********rule of 5***************** */

CrewMember:: CrewMember(std::string employeeID, std::string name, 
        double currentFlightHours, double maxAllowedHours)
        :employeeID(employeeID),
        name(name),currentFlightHours(currentFlightHours),
        maxAllowedHours(maxAllowedHours){}

CrewMember::CrewMember(const CrewMember& other)
{
    this->employeeID = other.employeeID;
    this->name = other.name;
    this->currentFlightHours = other.currentFlightHours;
    this->maxAllowedHours = other.maxAllowedHours;
}

CrewMember& CrewMember:: operator=(const CrewMember& other)
{
    if(this!=&other)
    {
        this->employeeID = other.employeeID;
        this->name = other.name;
        this->currentFlightHours = other.currentFlightHours;
        this->maxAllowedHours = other.maxAllowedHours;
    }
    return *this;

}

CrewMember:: ~CrewMember(){}


//**************setters and getters************** */

std::string CrewMember::getEmployeeID() const {
    return this->employeeID;
}

std::string CrewMember::getName() const {
    return this->name;
}

double CrewMember::getCurrentFlightHours() const {
    return this->currentFlightHours;
}

double CrewMember::getMaxAllowedHours() const {
    return this->maxAllowedHours;
}

// Setters
void CrewMember::setEmployeeID(const std::string& id) {
    this->employeeID = id;
}

void CrewMember::setName(const std::string& empName) {
    this->name = empName;
}

void CrewMember::setCurrentFlightHours(double hours) {
    if (hours >= 0 && hours <= this->maxAllowedHours) {
        this->currentFlightHours = hours;
    } else {
        std::cout << "[Warning] Attempted to set invalid flight hours!" << std::endl;
    }
}


void CrewMember::setMaxAllowedHours(double maxHours) {
    if (maxHours > 0) {
        this->maxAllowedHours = maxHours;
    }
}


//************ virtual functions**************************/
void CrewMember:: addFlightHours(double hours)
{
    if ( hours + currentFlightHours  <= this->maxAllowedHours) {
        this->currentFlightHours += hours;
    } else {
        std::cout << "[Warning] Attempted to exceed max flight hours!" << std::endl;
    }
}

bool CrewMember:: isWithinLimits(double additionalHours) const
{
    if ( additionalHours + currentFlightHours  <= this->maxAllowedHours) {
        return true;
    } 
    else 
    {
       return false;
    }
}