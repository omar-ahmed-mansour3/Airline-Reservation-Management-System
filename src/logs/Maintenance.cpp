#include "Maintenance.hpp"
#include <iostream>

//********** Rule of 5 ******************/


Maintenance::Maintenance(std::string maintenanceID, std::string scheduleDate, std::string completionDate,
                         std::string description, MaintenanceStatus status)
    : maintenanceID(maintenanceID),
      scheduleDate(scheduleDate),
      completionDate(completionDate == "" ? "N/A" : completionDate), //  defaults to "N/A"
      description(description),
      status(status)
{}


Maintenance::Maintenance(const Maintenance& other)
{
    this->maintenanceID = other.maintenanceID;
    this->scheduleDate = other.scheduleDate;
    this->completionDate = other.completionDate;
    this->description = other.description;
    this->status = other.status;
}


Maintenance& Maintenance::operator=(const Maintenance& other)
{
    if (this != &other)
    {
        this->maintenanceID = other.maintenanceID;
        this->scheduleDate = other.scheduleDate;
        this->completionDate = other.completionDate;
        this->description = other.description;
        this->status = other.status;
    }
    return *this;
}


Maintenance::~Maintenance() {}


//************** Getters and Setters ************** */

std::string Maintenance::getMaintenanceID() const 
{
    return this->maintenanceID;
}

std::string Maintenance::getScheduleDate() const 
{
    return this->scheduleDate;
}

std::string Maintenance::getCompletionDate() const 
{
    return this->completionDate;
}

std::string Maintenance::getDescription() const 
{
    return this->description;
}

MaintenanceStatus Maintenance::getStatus() const 
{
    return this->status;
}

void Maintenance::setMaintenanceID(const std::string& id) 
{
    this->maintenanceID = id;
}

void Maintenance::setScheduleDate(const std::string& sDate) 
{
    this->scheduleDate = sDate;
}

void Maintenance::setCompletionDate(const std::string& cDate) 
{
    this->completionDate = cDate;
}

void Maintenance::setDescription(const std::string& desc) 
{
    this->description = desc;
}

void Maintenance::setStatus(MaintenanceStatus newStatus) 
{
    this->status = newStatus;
}


//************ Class Specific Functions *******************/


void Maintenance::completeMaintenance(std::string finishDate)
{
    if (this->status == MaintenanceStatus::Scheduled || this->status == MaintenanceStatus::InProgress)
    {
        this->status = MaintenanceStatus::Completed;
        this->completionDate = finishDate;
    }
    else
    {
        std::cout << "[Info] Maintenance record " << this->maintenanceID 
                  << " is already marked as Completed." << std::endl;
    }
}


void Maintenance::displayLog() const
{
    std::string statusStr;
    switch (this->status)
    {
        case MaintenanceStatus::Scheduled:  statusStr = "Scheduled"; break;
        case MaintenanceStatus::InProgress: statusStr = "In Progress"; break;
        case MaintenanceStatus::Completed:  statusStr = "Completed"; break;
    }

    std::cout << "--- MAINTENANCE LOG [" << this->maintenanceID << "] ---" << std::endl;
    std::cout << "Description:     " << this->description << std::endl;
    std::cout << "Scheduled Date:  " << this->scheduleDate << std::endl;
    std::cout << "Completion Date: " << this->completionDate << std::endl;
    std::cout << "Status:          " << statusStr << std::endl;
}