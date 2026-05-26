#include"AirlineSystem.hpp"


AirlineSystem::AirlineSystem() {}
AirlineSystem::~AirlineSystem() {}


void AirlineSystem::seedMockData() {
    // -----------------------------------------------------------------
    // 1. SEED CREW MEMBERS (Polymorphic: Pilots & Attendants)
    // -----------------------------------------------------------------
    auto pilot1 = std::make_shared<Pilot>("P-01", "Captain Ahmed", 120.0, "LIC-9988", "Boeing 737");
    auto attendant1 = std::make_shared<FlightAttendant>("FA-01", "Sarah Mansour", 80.0, std::vector<std::string>{"English", "Arabic"});
    
    this->crewRegistry.push_back(pilot1);
    this->crewRegistry.push_back(attendant1);

    // -----------------------------------------------------------------
    // 2. SEED AIRCRAFT (The Fleet)
    // -----------------------------------------------------------------
    auto plane1 = std::make_shared<Aircraft>("FLEET-737", "Boeing 737", 120, true, std::vector<Maintenance>{});
    auto plane2 = std::make_shared<Aircraft>("FLEET-320", "Airbus A320", 150, true, std::vector<Maintenance>{});
    
    this->fleetRegistry.push_back(plane1);
    this->fleetRegistry.push_back(plane2);

    // -----------------------------------------------------------------
    // 3. SEED USERS (Polymorphic accounts for instant login tests)
    // -----------------------------------------------------------------
    // Format matches your constructor orders
    auto testAdmin = std::make_shared<Administrators>(1, "admin", "admin123", "Omar Ahmed", "0100", "admin@airline.com");
    auto testPassenger = std::make_shared<Passenger>(2, "passenger", "pass123", "John Doe", "0111", "john@mail.com", "A112233", "Window", "Standard");
    
    this->userRegistry.push_back(testAdmin);
    this->userRegistry.push_back(testPassenger);

    // -----------------------------------------------------------------
    // 4. SEED FLIGHTS (Leveraging the smart pointers built above)
    // -----------------------------------------------------------------
    // Collect pointers to pass into the flight schedules
    std::vector<std::shared_ptr<CrewMember>> sampleCrew = { pilot1, attendant1 };

    // Flight 1: 5 rows, 4 columns per row seat map
    // Note: If your FlightStatus enum uses different naming (e.g., Scheduled vs Active), adjust here
    auto flight1 = std::make_shared<Flight>("MS-101", "Cairo", "Dubai", "14:00", 350.0, 3.5, FlightStatus::Scheduled, plane1, sampleCrew, 5, 4);
    
    // Flight 2: 6 rows, 6 columns per row seat map
    auto flight2 = std::make_shared<Flight>("MS-202", "Cairo", "London", "09:30", 650.0, 5.0, FlightStatus::Scheduled, plane2, sampleCrew, 6, 6);

    this->flightSchedule.push_back(flight1);
    this->flightSchedule.push_back(flight2);
    
    std::cout << "[SYSTEM NOTICE] Seed data injected successfully into system memory.\n";
}



static std::string toLower(const std::string& s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
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

    void AirlineSystem::updateAircraftAvailability(std::string aircraftID, bool isAvailable)
    {
        for (const auto& plane : this->fleetRegistry) 
        {
            if (plane != nullptr && plane->getAircraftID() == aircraftID) 
            {
                plane->setIsAvailable(isAvailable);
                
                std::cout << "\n[SUCCESS] Aircraft " << aircraftID << " status updated to: " 
                        << (isAvailable ? "AVAILABLE" : "GROUNDED") << std::endl;
                return;
            }
        }
        std::cout << "[ERROR] Could not update. Aircraft '" << aircraftID << "' not found in fleet." << std::endl;
    }

    bool AirlineSystem::usernameExists(const std::string& username) const
    {
        for (const auto& user : this->userRegistry)
        {
            if (user != nullptr && user->get_username() == username)
                return true;
        }
        return false;
    }


// =====================================================================
//             FLIGHT & AIRCRAFT & CREW & USER MANAGEMENT (Admin Services)
// =====================================================================

    //*****************************Aircrafts**********************
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

    

    std::shared_ptr<Aircraft> AirlineSystem::getAircraftByID(std::string aircraftID) const
    {
        for (const auto& plane : this->fleetRegistry)
        {
            if (plane != nullptr && plane->getAircraftID() == aircraftID)
                return plane;
        }

        std::cout << "[ERROR] Aircraft '" << aircraftID << "' not found." << std::endl;
        return nullptr;
    }



    void AirlineSystem::scheduleMaintenance(std::string aircraftID, const Maintenance& newLog)
    {
        for (const auto& plane : this->fleetRegistry) 
        {
            if (plane != nullptr && plane->getAircraftID() == aircraftID) 
            {
                plane->addMaintenanceLog(newLog);
                plane->setIsAvailable(false);//ground it to be fixed
                
                std::cout << "\n[SUCCESS] Maintenance scheduled for Aircraft " << aircraftID << "." << std::endl;
                std::cout << "[ALERT] Aircraft has been automatically GROUNDED until maintenance is complete." << std::endl;
                return;
            }
        }
        std::cout << "[ERROR] Could not schedule maintenance. Aircraft '" << aircraftID << "' not found." << std::endl;
    }

    void AirlineSystem::removeAircraft(std::string aircraftID)
    {
        for (auto it = this->fleetRegistry.begin(); it != this->fleetRegistry.end(); ++it) 
        {
            if ((*it) != nullptr && (*it)->getAircraftID() == aircraftID) 
            {
                this->fleetRegistry.erase(it);
                
                std::cout << "[SUCCESS] Aircraft " << aircraftID << " has been permanently retired and removed from the fleet." << std::endl;
                return; 
            }
        }
        std::cout << "[ERROR] Could not remove. Aircraft '" << aircraftID << "' not found." << std::endl;
    }
    
    
    //****************************flights***************************

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

    void AirlineSystem::removeFlight(std::string flightNum)
    {
        
        for (auto it = this->flightSchedule.begin(); it != this->flightSchedule.end(); it++) 
        {
            if ((*it) != nullptr && (*it)->getFlightNumber() == flightNum) 
            {
                
                if ((*it)->getFlightStatus() != FlightStatus::Canceled) 
                {
                    std::cout << "[INFO] Auto-canceling flight before removal..." << std::endl;
                    this->cancelFlight(flightNum);
                }
                this->flightSchedule.erase(it);
                
                std::cout << "[SUCCESS] Flight " << flightNum << " has been completely erased from the system registry." << std::endl;
                return; 
            }
        }
        std::cout << "[ERROR] Could not remove. Flight '" << flightNum << "' not found." << std::endl;
    }

    void AirlineSystem::updateFlightDetails
        (std::string flightNum, std::string newOrigin, std::string newDest, std::string newTime, double newPrice)
    {
        
        std::shared_ptr<Flight> flight = this->getFlightByNumber(flightNum);
        
        if (flight == nullptr) return;
  
        //Apply the updates
        flight->setOrigin(newOrigin);
        flight->setDestination(newDest);
        flight->setDepartureTime(newTime);

        if (newPrice > 0.0) 
        {
            flight->setPrice(newPrice);
        }

        std::cout << "\n[SUCCESS] Flight " << flightNum << " has been updated!" << std::endl;
        std::cout << "New Route: " << flight->getOrigin() << " -> " << flight->getDestination() << std::endl;
        std::cout << "New Time:  " << flight->getDepartureTime() << std::endl;
    }


//*******************************CREW***********************************
    void AirlineSystem::assignCrewToFlight(std::string flightNum, std::shared_ptr<CrewMember> crew)
    {
        if (crew == nullptr) 
        {
            std::cout << "[ERROR] Cannot assign an empty/invalid crew member." << std::endl;
            return;
        }

        std::shared_ptr<Flight> targetFlight = this->getFlightByNumber(flightNum);

        if (targetFlight == nullptr) return;

        std::cout << "\nAttempting to assign " << crew->getStaffRole() << " " << crew->getName() 
                << " to Flight " << flightNum << "..." << std::endl;


        if (targetFlight->assignCrewMember(crew)) 
        {
            crew->addFlightHours(targetFlight->gethoursFlying());
            
            std::cout << "[SUCCESS] Crew assignment complete and logged in the system." << std::endl;
            std::cout << "[INFO] " << crew->getName() << "'s updated flight hours: " 
                    << crew->getCurrentFlightHours() << " / " << crew->getMaxAllowedHours() << " hrs" << std::endl;
        }
        else
        {
            std::cout << "[REGULATORY ERROR] Assignment failed for " << crew->getName() << "." << std::endl;
            std::cout << "Adding " << targetFlight->gethoursFlying() << " hours would exceed their legal maximum of " 
                    << crew->getMaxAllowedHours() << " hours. Please select another crew member." << std::endl;
        }
    }

    std::vector<std::shared_ptr<CrewMember>> AirlineSystem::getCrewByRole(std::string role) const 
    {
        std::vector<std::shared_ptr<CrewMember>> filteredList;
        for (const auto& member : this->crewRegistry) 
        {
            if (member->getStaffRole() == role) 
            {
                filteredList.push_back(member);
            }
        }
        return filteredList;
    }
    

//***********************USER************************** */

    bool AirlineSystem::deleteUser(const std::string& username)
    {
        for (auto it = userRegistry.begin(); it != userRegistry.end(); ++it)
        {
            if ((*it)->get_username() == username)
            {
                userRegistry.erase(it);
                return true;
            }
        }
        return false;
    }

    bool AirlineSystem::updateUser(const std::string& username, const std::string& newFullName,
                                const std::string& newPhone, const std::string& newEmail,
                                const std::string& newPassword)
    {
        for (const auto& user : userRegistry)
        {
            if (user->get_username() == username)
            {
                user->set_full_name(newFullName);
                user->set_Phone(newPhone);
                user->set_email(newEmail);
                user->set_password(newPassword);
                return true;
            }
        }
        return false;
    }


// =====================================================================
//            Booking Services (Passenger & Booking Agent Services)
// =====================================================================
    std::shared_ptr<Flight> AirlineSystem:: getFlightByNumber(std::string flightNum) const
    {
        for(const auto& flight : this->flightSchedule)
        {
            if(flight!=nullptr && flightNum == flight->getFlightNumber())
            {
                return flight;
            }
        }

        std::cout << "[ERROR] Flight '" << flightNum << "' could not be found in the system." << std::endl;
        return nullptr;
    }
    
    std::vector<std::shared_ptr<Flight>> AirlineSystem:: searchAvailableFlights
        (std::string origin, std::string dest, std::string date,double maxPrice) const
    {
        std::vector<std::shared_ptr<Flight>> available;

        for(const auto& flight : this->flightSchedule)
        {
            if (flight->getFlightStatus() == FlightStatus::Scheduled || 
                flight->getFlightStatus() == FlightStatus::Delayed)
            {
                if (!origin.empty() && toLower(flight->getOrigin()) != toLower(origin)) continue;
                if (!dest.empty()   && toLower(flight->getDestination()) != toLower(dest)) continue;
                if (!date.empty()   && flight->getDepartureTime() != date) continue;
                if (maxPrice > 0    && flight->getPrice() > maxPrice) continue;
                available.push_back(flight);
            }
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
  
    bool  AirlineSystem:: processNewBooking
        (std::shared_ptr<User> user, std::shared_ptr<Flight> flight, std::string seatNum, PaymentMethod method, int loyaltyPointsToUse=0)
        {
            if(flight==nullptr || user==nullptr)//input check
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

    std::vector<std::shared_ptr<Reservation>> AirlineSystem::getUserReservations(const std::string& username) const
    {
        std::vector<std::shared_ptr<Reservation>> userReservations;
        for (const auto& res : this->activeReservations)
        {
            if (res->getPassenger()->get_username() == username)
                userReservations.push_back(res);
        }
        return userReservations;
    }
    
