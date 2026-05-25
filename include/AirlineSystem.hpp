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
public:
    AirlineSystem();
    ~AirlineSystem();


/******************Authentication & User Services ***************/    
    std::shared_ptr<User> loginUser(std::string username, std::string password);
    void registerNewUser(std::shared_ptr<User> newUser);

/**********************Search & Query Services*********************/

std::shared_ptr<Flight> getFlightByNumber(std::string flightNum) const;
std::vector<std::shared_ptr<Flight>> searchAvailableFlights
            (std::string origin, std::string dest, std::string date) const;

/***************Admin Routing Services*******************/

    void addAircraftToFleet(std::shared_ptr<Aircraft> aircraft);
    void scheduleNewFlight(std::shared_ptr<Flight> flight);
    void cancelFlight(std::string flightNum);//status = canceled, refunds people

/*********************The Booking Engine***************************/

    bool processNewBooking
        (std::shared_ptr<User> user, std::shared_ptr<Flight> flight, std::string seatNum, PaymentMethod method);

    

};



#endif