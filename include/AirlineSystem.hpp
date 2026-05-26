#ifndef AIRLINESYSTEM_H
#define AIRLINESYSTEM_H
#include"User.hpp"
#include "Flight.hpp"
#include"Reservation.hpp"
class AirlineSystem
{
private:
    
    std::vector<std::shared_ptr<User>> userRegistry;
    std::vector<std::shared_ptr<Aircraft>> fleetRegistry;
    std::vector<std::shared_ptr<Flight>> flightSchedule;
    std::vector<std::shared_ptr<Reservation>> activeReservations;
    std::vector<std::shared_ptr<CrewMember>> crewRegistry;
public:
    AirlineSystem();
    ~AirlineSystem();


/******************Authentication & User Services ***************/    
    std::shared_ptr<User> loginUser(std::string username, std::string password);
    void registerNewUser(std::shared_ptr<User> newUser);
    bool usernameExists(const std::string& username) const;

/*********************The Booking Engine***************************/

    bool processNewBooking
        (std::shared_ptr<User> user, std::shared_ptr<Flight> flight, std::string seatNum, PaymentMethod method);

// =====================================================================
//            FLIGHT & AIRCRAFT & CREW & User MANAGEMENT (Admin Services)
// =====================================================================

    //**************Aircrafts******************************** 
    std::shared_ptr<Aircraft> getAircraftByID(std::string aircraftID) const;

    void addAircraftToFleet(std::shared_ptr<Aircraft> aircraft);
    void updateAircraftAvailability(std::string aircraftID, bool isAvailable);// only by admins
    void scheduleMaintenance(std::string aircraftID, const Maintenance& newLog);// only by admins
    void removeAircraft(std::string aircraftID);

    //*************flights*********************************************/
    std::shared_ptr<Flight> getFlightByNumber(std::string flightNum) const;
    std::vector<std::shared_ptr<Flight>> searchAvailableFlights
            (std::string origin, std::string dest, std::string date) const;

    void scheduleNewFlight(std::shared_ptr<Flight> flight);
    void cancelFlight(std::string flightNum);//status = canceled, refunds people
    void removeFlight(std::string flightNum);//remove from saved data
    void updateFlightDetails
    (std::string flightNum, std::string newOrigin, std::string newDest, std::string newTime, double newPrice);

    //**********************CREW*******************************/
    void assignCrewToFlight(std::string flightNum, std::shared_ptr<CrewMember> crew);
    std::vector<std::shared_ptr<CrewMember>> getCrewByRole(std::string role) const ;

    /***********************USER************************************/
    bool deleteUser(const std::string& username);

    bool updateUser(const std::string& username, const std::string& newFullName,
                const std::string& newPhone, const std::string& newEmail,
                const std::string& newPassword);

};



#endif