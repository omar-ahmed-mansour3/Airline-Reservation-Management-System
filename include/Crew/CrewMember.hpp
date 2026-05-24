#ifndef CREWMEMBER_H
#define CREWMEMBER_H
#include<string>
#include<iostream>
#define MAX_HOURS 100
class CrewMember
{
    private:
    //************ATTRIBUTES************* */
    std::string employeeID;
    std::string name;
    double currentFlightHours;
    double maxAllowedHours = MAX_HOURS;

    
    public: 
//**********rule of 5***************** */
    CrewMember( std::string employeeID, std::string name, 
        double currentFlightHours, double maxAllowedHours );

    CrewMember(const CrewMember& other);
    CrewMember& operator=(const CrewMember& other);
    
    virtual ~CrewMember();

//**************setters and getters***************** */
// Getters
    std::string getEmployeeID() const;
    std::string getName() const;
    double getCurrentFlightHours() const;
    double getMaxAllowedHours() const;

    // Setters
    void setEmployeeID(const std::string& id);
    void setName(const std::string& empName);
    void setCurrentFlightHours(double hours);
    void setMaxAllowedHours(double maxHours);

//************Pure virtual functions**************************/

virtual void showStaffProfile() const = 0;
virtual std::string getStaffRole() const = 0;

//************ virtual functions**************************/
virtual void addFlightHours(double hours);
virtual bool isWithinLimits(double additionalHours) const;



};

#endif