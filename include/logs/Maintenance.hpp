#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include<string>

enum class MaintenanceStatus
{
    Scheduled, InProgress, Completed
};
class Maintenance
{
private:
    //**********ATTRIBUTES***************** */
    std::string maintenanceID;
    std::string scheduleDate;
    std::string completionDate;
    std::string description;
    MaintenanceStatus status;

public:

//**********rule of 5******************/
    Maintenance(std::string maintenanceID, std::string scheduleDate, std::string completionDate,
        std::string description, MaintenanceStatus status);

    Maintenance(const Maintenance& other);

    Maintenance& operator=(const Maintenance& other);
    ~Maintenance();

//**************Getters and Setters***************** */
    std::string getMaintenanceID() const;
    std::string getScheduleDate() const;
    std::string getCompletionDate() const;
    std::string getDescription() const;
    MaintenanceStatus getStatus() const;

    void setMaintenanceID(const std::string& id);
    void setScheduleDate(const std::string& sDate);
    void setCompletionDate(const std::string& cDate);
    void setDescription(const std::string& desc);
    void setStatus(MaintenanceStatus newStatus);

//************class specific functions************************* */
void completeMaintenance(std::string finishDate);
void displayLog() const;


};

#endif
