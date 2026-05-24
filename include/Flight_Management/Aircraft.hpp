#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include<string>
#include<vector>
#include"Maintenance.hpp"
class Aircraft
{
    private:
    std:: string aircraftID;
    std::string model;
    int totalSeats;
    bool isAvailable;//available to flights or not fot some reason
    std::vector<Maintenance> maintenanceHistory;

    public:
    //**********rule of 5***************** */

    Aircraft(std:: string aircraftID, std::string model,int totalSeats,
        bool isAvailable,std::vector<Maintenance> maintenanceHistory);

    Aircraft(const Aircraft& other);
    Aircraft& operator=(const Aircraft& other);
    ~Aircraft();

//************** Getters and Setters ***************** */
    std::string getAircraftID() const;
    std::string getModel() const;
    int getTotalSeats() const;
    bool getIsAvailable() const;
    std::vector<Maintenance> getMaintenanceHistory() const;

    void setAircraftID(const std::string& id);
    void setModel(const std::string& mdl);
    void setTotalSeats(int seats);
    void setIsAvailable(bool available);
    void setMaintenanceHistory(const std::vector<Maintenance>& history);


//************class specific functions************************* */
    
    void addMaintenanceLog(const Maintenance& log);
    void displayAircraftSpecs() const;
    void printFullMaintenanceHistory() const;

};

#endif
