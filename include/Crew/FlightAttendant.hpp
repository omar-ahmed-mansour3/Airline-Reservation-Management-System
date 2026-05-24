#ifndef FLIGHT_ATTENDANT_HPP
#define FLIGHT_ATTENDANT_HPP

#include "CrewMember.hpp"
#include<vector>
class FlightAttendant : public CrewMember {

private:
/********************Attributes*****************/
std::vector<std::string> languagesSpoken;

public:
FlightAttendant(std::string id, std::string name, double maxHours, 
                std::vector<std::string> languages);


FlightAttendant(const FlightAttendant& other);
FlightAttendant& operator=(const FlightAttendant& other);

~FlightAttendant();

/**************** Getters & Setters ************/
std::vector<std::string> getLanguagesSpoken() const;
void setLanguagesSpoken(const std::vector<std::string>& languages);
void addLanguagesSpoken(const std::string& language);

//************overriden functions************* */
void showStaffProfile() const;
std::string getStaffRole() const;


};

#endif