#ifndef FLIGHT_H
#define FLIGHT_H
#include "Aircraft.hpp"
#include <memory>
#include"CrewMember.hpp"
#include<vector>
enum class FlightStatus {
    Scheduled,
    Delayed,
    Boarding,
    Canceled
};
class Flight
{
    private:
    std::string flightNumber; //unique id
    std::string origin; //departure city 
    std::string destination;
    std::string departureTime;
    double Price;
    double hoursFlying;
    FlightStatus status;
    std:: shared_ptr<Aircraft> assignedAircraft;
    std:: vector< std::shared_ptr<CrewMember>>assignedCrew;
    int rows; //seats
    int columnsPerRow;//seats
    std::vector<std::vector<std::string>>seatMap;

    public:

//**********rule of 5***************** */
    //if u have seat map ready
    Flight( std::string flightNumber, std::string origin, std::string destination, std::string departureTime,
     double Price, double hoursFlying, FlightStatus status, std:: shared_ptr<Aircraft> assignedAircraft, 
     std:: vector< std::shared_ptr<CrewMember>>assignedCrew, std::vector<std::vector<std::string>>seatMap);
    
    // if you have the row and col but not the vector
    Flight( std::string flightNumber, std::string origin, std::string destination, std::string departureTime,
     double Price, double hoursFlying, FlightStatus status, std:: shared_ptr<Aircraft> assignedAircraft, 
     std:: vector< std::shared_ptr<CrewMember>>assignedCrew,int rows, int columnsPerRow  );

    Flight(const Flight& other);
    Flight& operator=(const Flight& other);
    ~Flight();


//************** Getters ************** */
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureTime() const;
    double getPrice() const;
    double gethoursFlying() const;
    FlightStatus getFlightStatus() const;
    std::shared_ptr<Aircraft> getAssignedAircraft() const;
    const std::vector<std::shared_ptr<CrewMember>>& getAssignedCrew() const;
    int getRows() const;
    int getColumnsPerRow() const;
    const std::vector<std::vector<std::string>>& getSeatMap() const;

//************** Setters ************** */
    void setFlightNumber(const std::string& fNum);
    void setOrigin(const std::string& orig);
    void setDestination(const std::string& dest);
    void setDepartureTime(const std::string& dTime);
    void setPrice(double price);
    void sethoursFlying(double hoursflying);
    void setFlightStatus(FlightStatus newStatus);
    void setAssignedAircraft(std::shared_ptr<Aircraft> aircraft);
    void setAssignedCrew(const std::vector<std::shared_ptr<CrewMember>>& crew);
    void setRows(int rows);
    void setcolPerRow(int col);
    void setSeatMap(const std::vector<std::vector<std::string>>& seats);


//************class specific functions************************* */

    /***general flight managment*/
    bool assignCrewMember(std::shared_ptr<CrewMember> crew);
    void updateFlightStatus(FlightStatus newStatus);
    void displayFlightDetails() const;
    void printCrewRoster() const;

    //*****seat managment */
    void displayAvailableSeats() const;
    bool reserveSeat(std::string seatNumber);
    void releaseSeat(std::string seatNumber);

    
};

#endif