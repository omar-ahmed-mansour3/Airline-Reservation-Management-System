#ifndef PILOT_HPP
#define PILOT_HPP

#include "CrewMember.hpp"

class Pilot : public CrewMember {

private:
//************ATTRIBUTES************* */
std::string licenseNumber;
std::string aircraftModel; // to restrict pilot to a certain model they are trained to

public:

//**********rule of 5***************** */
Pilot(std::string id, std::string name, double maxHours, 
      std::string license, std::string model);
Pilot(const Pilot& other);
Pilot& operator=(const Pilot& other);
~Pilot();



//************** Getters and Setters ************** */
std::string getLicenseNumber() const;
std::string getAircraftModel() const;
void setLicenseNumber(const std::string& license);
void setAircraftModel(const std::string& model);

//************ Virtual Overrides ******************/
void showStaffProfile() const override;
std::string getStaffRole() const override;


};

#endif