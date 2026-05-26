#include "Aircraft.hpp"
#include <iostream>

//********** Rule of 5******************/


Aircraft::Aircraft(std::string aircraftID, std::string model, int totalSeats,
                   bool isAvailable, std::vector<Maintenance> maintenanceHistory)
    : aircraftID(aircraftID),
      model(model),
      totalSeats(totalSeats),
      isAvailable(isAvailable),
      maintenanceHistory(maintenanceHistory)
{}

Aircraft::Aircraft(std::string aircraftID, std::string model, int rows, int columnsPerRow,
                   bool isAvailable, std::vector<Maintenance> maintenanceHistory)
    : aircraftID(aircraftID),
      model(model),
      totalSeats(rows * columnsPerRow),
      rows(rows),
      columnsPerRow(columnsPerRow),
      isAvailable(isAvailable),
      maintenanceHistory(maintenanceHistory)
{}


Aircraft::Aircraft(const Aircraft& other)
{
    this->aircraftID = other.aircraftID;
    this->model = other.model;
    this->totalSeats = other.totalSeats;
    this->isAvailable = other.isAvailable;
    this->maintenanceHistory = other.maintenanceHistory; 
}


Aircraft& Aircraft::operator=(const Aircraft& other)
{
    if (this != &other)
    {
        this->aircraftID = other.aircraftID;
        this->model = other.model;
        this->totalSeats = other.totalSeats;
        this->isAvailable = other.isAvailable;
        this->maintenanceHistory = other.maintenanceHistory; 
    }
    return *this;
}


Aircraft::~Aircraft() {}


//************** Getters and Setters ************** */

std::string Aircraft::getAircraftID() const 
{
    return this->aircraftID;
}

std::string Aircraft::getModel() const 
{
    return this->model;
}

int Aircraft::getTotalSeats() const 
{
    return this->totalSeats;
}

int Aircraft::getRows() const 
{
    return this->rows;
}
int Aircraft::getColumnsPerRow() const 
{
    return this->columnsPerRow;
}

bool Aircraft::getIsAvailable() const 
{
    return this->isAvailable;
}

std::vector<Maintenance> Aircraft::getMaintenanceHistory() const 
{
    return this->maintenanceHistory;
}

void Aircraft::setAircraftID(const std::string& id) 
{
    this->aircraftID = id;
}

void Aircraft::setModel(const std::string& mdl) 
{
    this->model = mdl;
}

void Aircraft::setTotalSeats(int seats) 
{
    if (seats > 0) 
    {
        this->totalSeats = seats;
    }
}

void Aircraft::setRows(int rows) 
{
    if (rows > 0) 
    {
        this->rows = rows;
    }
}
void Aircraft::setColumnsPerRow(int cols) 
{
    if (cols > 0) 
    {
        this->columnsPerRow = cols;
    }
}

void Aircraft::setIsAvailable(bool available) 
{
    this->isAvailable = available;
}

void Aircraft::setMaintenanceHistory(const std::vector<Maintenance>& history) 
{
    this->maintenanceHistory = history;
}


//************ Class Specific Functions *******************/

// Pushes a new maintenance record into the fleet array log
void Aircraft::addMaintenanceLog(const Maintenance& log)
{
    this->maintenanceHistory.push_back(log);
}

// Prints technical metrics about the airframe
void Aircraft::displayAircraftSpecs() const
{
    std::cout << "--- AIRCRAFT SPECIFICATIONS ---" << std::endl;
    std::cout << "Aircraft ID:    " << this->aircraftID << std::endl;
    std::cout << "Model:          " << this->model << std::endl;
    std::cout << "Total Seats:    " << this->totalSeats << std::endl;
    std::cout << "Rows:           " << this->rows << std::endl;
    std::cout << "Columns per Row: " << this->columnsPerRow << std::endl;
    std::cout << "Operational Status: " << (this->isAvailable ? "Available" : "Grounded") << std::endl;
}


void Aircraft::printFullMaintenanceHistory() const
{
    std::cout << "\n----MAINTENANCE LOG HISTORY FOR: " << this->aircraftID <<" ---"<< std::endl;

    
    if (this->maintenanceHistory.empty())
    {
        std::cout << "No historical maintenance logs found for this airframe." << std::endl;
        return;
    }

    for (int i = 0; i < this->maintenanceHistory.size(); i++)
    {
        this->maintenanceHistory[i].displayLog();
        std::cout << "--------------------------------------" << std::endl;
    }
}