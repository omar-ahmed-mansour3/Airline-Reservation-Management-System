#include"AirlineSystem.hpp"



/******************Authentication & User Services ***************/    

    std::shared_ptr<User> AirlineSystem::loginUser(std::string username, std::string password) 
{
    for (const auto& user : this->userRegistry) 
    {
        if (user->get_username() == username) 
        {
            if (user->get_password() == password) 
            {
                std::cout << "[SUCCESS] Login successful. Welcome back, " 
                          << user->getFullName() << "!" << std::endl;
                return user; 
            } 
            else 
            {
                std::cout << "[ERROR] Incorrect password for user: " << username << std::endl;
                return nullptr;
            }
        }
    }

    std::cout << "[ERROR] Username '" << username << "' does not exist." << std::endl;
    return nullptr;
}

    void AirlineSystem:: registerNewUser(std::shared_ptr<User> newUser)
    {
        if(newUser==nullptr)
        {
            std::cout<<"[ERROR] Cannot register an invalid or empty user profile." << std::endl;
            return;
        }
        for( const auto& user : this->userRegistry)
        {
            if(newUser->get_username() == user->get_username())
            {
                std::cout << "[ERROR] Registration failed. The username '" 
                      << newUser->get_username() << "' is already taken!" << std::endl;
            return;
            }
        }

        this->userRegistry.push_back(newUser);
        std::cout << "[SUCCESS] Account created! Welcome to the airline, " 
              << newUser->getFullName() << "." << std::endl;
        return;
        
    }

/**********************Search & Query Services*********************/
    std::shared_ptr<Flight> AirlineSystem:: getFlightByNumber(std::string flightNum) const
    {
        for(const auto& flight : this->flightSchedule)
        {
            if(flight!=nullptr && flightNum == flight->getFlightNumber())
            {
                return flight;
            }

            std::cout << "[ERROR] Flight '" << flightNum << "' could not be found in the system." << std::endl;
            return nullptr;
        }

    }

    std::vector<std::shared_ptr<Flight>> AirlineSystem:: searchAvailableFlights
    (std::string origin, std::string dest, std::string date) const
    {
        std::vector<std::shared_ptr<Flight>> available;

        for(const auto& flight : this->flightSchedule)
        {
            if(flight!=nullptr && (flight->getFlightStatus()== Scheduled || flight->getFlightStatus()== Delayed)
             &&flight->getOrigin()==origin &&flight->getDestination()==dest 
             && flight->getDepartureTime()==date)
            {
                available.push_back(flight);
            }

            if (available.empty()) 
            {
                std::cout << "[INFO] No available flights found from " << origin 
                  << " to " << dest << " on " << date << "." << std::endl;
            } 
            else 
            {
            std::cout << "[SUCCESS] Found " << available.size() 
                  << " available flight(s) matching your criteria!" << std::endl;
            }
            return available;
        }
    }
       
    
/***************Admin Routing Services*******************/

    void AirlineSystem:: addAircraftToFleet(std::shared_ptr<Aircraft> aircraft)
    {
        if(aircraft == nullptr)
        {
            std::cout << "[ERROR] Cannot add an empty/invalid aircraft to the fleet." << std::endl;
            return;
        }
        for(const auto& plane: this->fleetRegistry)
        {
            if(plane!=nullptr && plane->getAircraftID() == aircraft->getAircraftID())
            {
                std::cout << "[ERROR] Aircraft ID '" << aircraft->getAircraftID() 
                        << "' is already registered in the fleet!" << std::endl;
                return;
            }

        }

        this->fleetRegistry.push_back(aircraft);
        std::cout << "[SUCCESS] Aircraft '" << aircraft->getAircraftID() 
                << "' (" << aircraft->getModel() << ") has been successfully added to the fleet." << std::endl;
        return;
        
    }

    void AirlineSystem:: scheduleNewFlight(std::shared_ptr<Flight> flight)
    {
        if(flight == nullptr)
        {
            std::cout << "[ERROR] Cannot add an empty/invalid." << std::endl;
            return;
        }

        for(const auto& existingFlight : this->flightSchedule)
        {
            if(existingFlight->getFlightNumber() == flight->getFlightNumber())
            {
                std::cout << "[ERROR] Scheduling failed. Flight '" << flight->getFlightNumber() 
                      << "' is already active in the schedule!" << std::endl;
                return; 
            }
        }
        this->flightSchedule.push_back(flight);
        std::cout << "[SUCCESS] Flight '" << flight->getFlightNumber() 
              << "' from " << flight->getOrigin() 
              << " to " << flight->getDestination() 
              << " has been successfully scheduled!" << std::endl;
        return;

    }

    void AirlineSystem:: cancelFlight(std::string flightNum)//status = canceled, refunds people
    {
        std::shared_ptr<Flight> targetFlight = this->getFlightByNumber(flightNum);

        if (targetFlight == nullptr) return; //sanity check, unlikely to happen

        if (targetFlight->getFlightStatus() == FlightStatus::Canceled) //if no :: it will use booking status
        {
            std::cout << "[INFO] Flight '" << flightNum << "' is already canceled. No action taken." << std::endl;
            return;
        }
        targetFlight->setFlightStatus(FlightStatus::Canceled);

        std::cout << "\n=================================================" << std::endl;
        std::cout << "[ALERT] FLIGHT '" << flightNum << "' HAS BEEN CANCELED." << std::endl;
        std::cout << "Initiating automated refund process for all passengers..." << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;

        int refundCount=0;
        for(const auto& reserv: this->activeReservations)
        {
            if(reserv->getFlight()== targetFlight)
            {
                refundCount++;
                reserv->cancelReservation();
            }
        }

        std::cout << "=================================================" << std::endl;
        std::cout << "[SUCCESS] Flight cancellation complete. " 
        << refundCount << " passenger(s) refunded.\n" << std::endl;
    }

/*********************The Booking Engine***************************/ 

     bool  AirlineSystem:: processNewBooking
        (std::shared_ptr<User> user, std::shared_ptr<Flight> flight, std::string seatNum, PaymentMethod method)
        {
            if(flight==nullptr && user==nullptr)//input check
            {
                std::cout << "[ERROR] Invalid user or flight data. Booking aborted." << std::endl;
                return false;
            }

            if(flight->getFlightStatus()== FlightStatus::Canceled)
            {
                std::cout << "[ERROR] Cannot book a seat on a canceled flight." << std::endl;
                return false;
            }  
            
            std::cout << "\n--- Processing New Booking ---" << std::endl;
            std::cout << "Passenger: " << user->getFullName() << " | Flight: " << flight->getFlightNumber() << std::endl;
            
            if (!flight->reserveSeat(seatNum)) //check if seat already booked
            {
                std::cout << "[ERROR] Booking failed. Seat " << seatNum << " is unavailable." << std::endl;
                return false;
            }


            std::string txnId = "TXN-" + std::to_string(rand() % 9000 + 1000); //random ticket number
            std::string timestamp = "2024-10-31 14:00";


            auto newPayment = std::make_shared<Payment>(txnId, flight->getPrice(), method, timestamp);
            if (newPayment->processPayment()) 
            {
            
                std::string bookingId = "PNR-" + std::to_string(rand() % 90000 + 10000); // random bookingId
                
                auto newBooking = std::make_shared<Reservation>(
                    bookingId, seatNum, user, flight, BookingStatus::Confirmed
                );
                newBooking->setPayment(newPayment);
                this->activeReservations.push_back(newBooking);
                std::cout << "\n[SUCCESS] Booking complete! Your Reservation ID is: " << bookingId << std::endl;
                newBooking->displayTicket(); 
                return true;
            
            }
            else
            {
                std::cout << "[ERROR] Payment declined. Releasing seat " <<
                seatNum << " back to the public." << std::endl;
                flight->releaseSeat(seatNum);
                return false;
            }

            

        }
