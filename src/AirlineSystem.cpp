#include"AirlineSystem.hpp"


AirlineSystem::AirlineSystem() {}
AirlineSystem::~AirlineSystem() {}


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
    
    
    void AirlineSystem::viewMaintenanceLogs(const std::string& aircraftID) const
    {
        for (const auto& plane : this->fleetRegistry)
        {
            if (plane->getAircraftID() == aircraftID)
            {
                plane->printFullMaintenanceHistory();
                return;
            }
        }
        std::cout << "[ERROR] Aircraft '" << aircraftID << "' not found.\n";
    }

    void AirlineSystem::completeMaintenance(const std::string& aircraftID, 
    const std::string& maintenanceID, const std::string& completionDate)
    {
        for (const auto& plane : this->fleetRegistry)
        {
            if (plane->getAircraftID() == aircraftID)
            {
                for (auto& log : plane->getMaintenanceHistoryRef())
                {
                    if (log.getMaintenanceID() == maintenanceID)
                    {
                        log.completeMaintenance(completionDate);
                        plane->setIsAvailable(true);
                        std::cout << "[SUCCESS] Maintenance " << maintenanceID 
                                << " marked complete. Aircraft is now available.\n";
                        return;
                    }
                }
                std::cout << "[ERROR] Maintenance ID '" << maintenanceID << "' not found.\n";
                return;
            }
        }
        std::cout << "[ERROR] Aircraft '" << aircraftID << "' not found.\n";
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
        (std::shared_ptr<User> user, std::shared_ptr<Flight> flight, std::string seatNum, PaymentMethod method, int loyaltyPointsToUse)
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


            double finalPrice = flight->getPrice();
            int loyaltyDiscount = 0;

            auto passenger = std::dynamic_pointer_cast<Passenger>(user);

            if (passenger != nullptr && loyaltyPointsToUse > 0)
            {
                if (loyaltyPointsToUse > passenger->getLoyaltyPoints())
                {
                    std::cout << "[WARNING] You only have " << passenger->getLoyaltyPoints() 
                            << " points. Using all available points.\n";
                    loyaltyPointsToUse = passenger->getLoyaltyPoints();
                }
                loyaltyDiscount = loyaltyPointsToUse * 10; // 1 point = $10
                if (loyaltyDiscount > finalPrice) loyaltyDiscount = finalPrice;
                finalPrice -= loyaltyDiscount;
            }

            std::cout << "\n--- PRICE BREAKDOWN ---\n";
            std::cout << "Base Fare:         $" << flight->getPrice() << "\n";
            if (loyaltyDiscount > 0)
                std::cout << "Loyalty Discount:  -$" << loyaltyDiscount << " (" << loyaltyPointsToUse << " points)\n";
            
            std::cout << "Final Price:       $" << finalPrice << "\n";
            std::cout << "-----------------------\n";

            // txnId and timestamp already generated above

            auto newPayment = std::make_shared<Payment>(txnId, finalPrice, method, timestamp);
            if (newPayment->processPayment())
            {
                if (passenger != nullptr)
                {
                    if (loyaltyPointsToUse > 0)
                        passenger->deductLoyaltyPoints(loyaltyPointsToUse);
                    
                    passenger->addLoyaltyPoints(1); // 1 point per booking
                    std::cout << "[LOYALTY] +1 point earned! Total points: " 
                            << passenger->getLoyaltyPoints() << "\n";
                }

                std::string bookingId = "PNR-" + std::to_string(rand() % 90000 + 10000);
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
                std::cout << "[ERROR] Payment declined. Releasing seat " << seatNum << " back to the public." << std::endl;
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

    std::shared_ptr<User> AirlineSystem::getUserByUsername(const std::string& username) const
{
    for (const auto& user : this->userRegistry)
    {
        if (user->get_username() == username)
            return user;
    }
    return nullptr;
}

bool AirlineSystem::checkInPassenger(const std::string& bookingId)
{
    for (const auto& reservation : this->activeReservations)
    {
        if (reservation->getBookingId() == bookingId)
        {
            return reservation->checkIn();
        }
    }
    std::cout << "[ERROR] Reservation not found for check-in." << std::endl;
    return false;
}

// =====================================================================
//                        REPORTS (Admin Only)
// =====================================================================


    void AirlineSystem::generateMaintenanceReport() const
{
    std::cout << "\n=============================================\n";
    std::cout << "         MAINTENANCE REPORT                  \n";
    std::cout << "=============================================\n";
    std::cout << "Total Aircraft in Fleet: " << this->fleetRegistry.size() << "\n\n";

    for (const auto& plane : this->fleetRegistry)
    {
        std::cout << "Aircraft: " << plane->getAircraftID() 
                  << " | Model: " << plane->getModel()
                  << " | Status: " << (plane->getIsAvailable() ? "Available" : "Grounded") << "\n";

        auto history = plane->getMaintenanceHistory();
        if (history.empty())
        {
            std::cout << "  No maintenance logs found.\n";
        }
        else
        {
            int scheduled = 0, inProgress = 0, completed = 0;
            for (const auto& log : history)
            {
                switch (log.getStatus())
                {
                    case MaintenanceStatus::Scheduled:  scheduled++;  break;
                    case MaintenanceStatus::InProgress: inProgress++; break;
                    case MaintenanceStatus::Completed:  completed++;  break;
                }
            }
            std::cout << "  Total Logs: "   << history.size()  << "\n";
            std::cout << "  Scheduled: "    << scheduled       << "\n";
            std::cout << "  In Progress: "  << inProgress      << "\n";
            std::cout << "  Completed: "    << completed        << "\n";
        }
        std::cout << "---------------------------------------------\n";
    }
}

    void AirlineSystem::generateUserActivityReport() const
{
    std::cout << "\n=============================================\n";
    std::cout << "         USER ACTIVITY REPORT                \n";
    std::cout << "=============================================\n";

    int totalPassengers = 0, totalAdmins = 0, totalBookingAdmins = 0;
    for (const auto& user : this->userRegistry)
    {
        if      (user->getRole() == "Passenger")    totalPassengers++;
        else if (user->getRole() == "Administrators") totalAdmins++;
        else if (user->getRole() == "BookingAdmin") totalBookingAdmins++;
    }

    std::cout << "Total Users:          " << this->userRegistry.size()  << "\n";
    std::cout << "Passengers:           " << totalPassengers             << "\n";
    std::cout << "Booking Agents:       " << totalBookingAdmins          << "\n";
    std::cout << "Administrators:       " << totalAdmins                 << "\n\n";

    // booking stats
    int confirmed = 0, canceled = 0, refunded = 0, pending = 0;
    double totalRevenue = 0.0;

    for (const auto& res : this->activeReservations)
    {
        switch (res->getBookingStatus())
        {
            case BookingStatus::Confirmed:      
                confirmed++; 
                if (res->getPayment() != nullptr)
                    totalRevenue += res->getPayment()->getAmount();
                break;
            case BookingStatus::Canceled:       canceled++;  break;
            case BookingStatus::Refunded:       refunded++;  break;
            case BookingStatus::PendingPayment: pending++;   break;
        }
    }

    std::cout << "Total Reservations:   " << this->activeReservations.size() << "\n";
    std::cout << "Confirmed:            " << confirmed  << "\n";
    std::cout << "Canceled:             " << canceled   << "\n";
    std::cout << "Refunded:             " << refunded   << "\n";
    std::cout << "Pending Payment:      " << pending    << "\n";
    std::cout << "Total Revenue:        $" << totalRevenue << "\n";
    std::cout << "=============================================\n";
}

    void AirlineSystem::generateFlightReport() const
{
    std::cout << "\n=============================================\n";
    std::cout << "           FLIGHT REPORT                     \n";
    std::cout << "=============================================\n";
    std::cout << "Total Flights: " << this->flightSchedule.size() << "\n\n";

    int scheduled = 0, delayed = 0, boarding = 0, canceled = 0;
    for (const auto& flight : this->flightSchedule)
    {
        switch (flight->getFlightStatus())
        {
            case FlightStatus::Scheduled: scheduled++; break;
            case FlightStatus::Delayed:   delayed++;   break;
            case FlightStatus::Boarding:  boarding++;  break;
            case FlightStatus::Canceled:  canceled++;  break;
        }
    }

    std::cout << "Scheduled: " << scheduled << "\n";
    std::cout << "Delayed:   " << delayed   << "\n";
    std::cout << "Boarding:  " << boarding  << "\n";
    std::cout << "Canceled:  " << canceled  << "\n\n";

    // per flight booking count
    std::cout << "--- Bookings Per Flight ---\n";
    for (const auto& flight : this->flightSchedule)
    {
        int bookingCount = 0;
        for (const auto& res : this->activeReservations)
        {
            if (res->getFlight()->getFlightNumber() == flight->getFlightNumber() &&
                res->getBookingStatus() == BookingStatus::Confirmed)
                bookingCount++;
        }
        std::cout << "Flight " << flight->getFlightNumber()
                  << " (" << flight->getOrigin() << " -> " << flight->getDestination() << ")"
                  << " | Confirmed Bookings: " << bookingCount << "\n";
    }
    std::cout << "=============================================\n";
}


bool AirlineSystem::cancelUserReservation(const std::string& bookingId)
{
    for (const auto& res : this->activeReservations)
    {
        if (res->getBookingId() == bookingId)
        {
            res->cancelReservation(); // handles seat release and refund message

            // deduct 1 loyalty point if user is a passenger
            auto passenger = std::dynamic_pointer_cast<Passenger>(res->getPassenger());
            if (passenger != nullptr && passenger->getLoyaltyPoints() > 0)
            {
                passenger->deductLoyaltyPoints(1);
                std::cout << "[LOYALTY] -1 point deducted. Total points: " 
                          << passenger->getLoyaltyPoints() << "\n";
            }
            return true;
        }
    }
    std::cout << "[ERROR] Reservation not found.\n";
    return false;
}


//******************file I/O methods******************/

void AirlineSystem::saveData() const
{
    nlohmann::json root;

    //****USERS 
    nlohmann::json usersArray = nlohmann::json::array();
    for (const auto& user : this->userRegistry)
    {
        nlohmann::json u;
        u["userid"]    = user->get_userid();
        u["username"]  = user->get_username();
        u["password"]  = user->get_password();
        u["full_name"] = user->getFullName();
        u["phone"]     = user->get_Phone();
        u["email"]     = user->get_email();
        u["role"]      = user->getRole();

        // passenger-specific fields
        if (user->getRole() == "Passenger")
        {
            auto p = std::dynamic_pointer_cast<Passenger>(user);
            u["loyaltyPoints"]  = p->getLoyaltyPoints();
            u["passport"]       = p->getPassport();
            u["seatPreference"] = p->getSeatPreference();
            u["mealPreference"] = p->getMealPreference();
        }
        usersArray.push_back(u);
    }
    root["users"] = usersArray;

    //** CREW 
    nlohmann::json crewArray = nlohmann::json::array();
    for (const auto& member : this->crewRegistry)
    {
        nlohmann::json c;
        c["employeeID"]        = member->getEmployeeID();
        c["name"]              = member->getName();
        c["currentHours"]      = member->getCurrentFlightHours();
        c["maxHours"]          = member->getMaxAllowedHours();
        c["role"]              = member->getStaffRole();

        if (member->getStaffRole() == "Pilot")
        {
            auto pilot = std::dynamic_pointer_cast<Pilot>(member);
            c["licenseNumber"]  = pilot->getLicenseNumber();
            c["aircraftModel"]  = pilot->getAircraftModel();
        }
        else if (member->getStaffRole() == "Flight Attendant")
        {
            auto fa = std::dynamic_pointer_cast<FlightAttendant>(member);
            c["languages"] = fa->getLanguagesSpoken();
        }
        crewArray.push_back(c);
    }
    root["crew"] = crewArray;

    //*****AIRCRAFT
    nlohmann::json fleetArray = nlohmann::json::array();
    for (const auto& plane : this->fleetRegistry)
    {
        nlohmann::json a;
        a["aircraftID"]   = plane->getAircraftID();
        a["model"]        = plane->getModel();
        a["totalSeats"]   = plane->getTotalSeats();
        a["isAvailable"]  = plane->getIsAvailable();

        nlohmann::json logsArray = nlohmann::json::array();
        for (const auto& log : plane->getMaintenanceHistory())
        {
            nlohmann::json m;
            m["maintenanceID"]   = log.getMaintenanceID();
            m["scheduleDate"]    = log.getScheduleDate();
            m["completionDate"]  = log.getCompletionDate();
            m["description"]     = log.getDescription();
            m["status"]          = static_cast<int>(log.getStatus());
            logsArray.push_back(m);
        }
        a["maintenanceHistory"] = logsArray;
        fleetArray.push_back(a);
    }
    root["fleet"] = fleetArray;

    // **** FLIGHTS ****
    nlohmann::json flightsArray = nlohmann::json::array();
    for (const auto& flight : this->flightSchedule)
    {
        nlohmann::json f;
        f["flightNumber"]   = flight->getFlightNumber();
        f["origin"]         = flight->getOrigin();
        f["destination"]    = flight->getDestination();
        f["departureTime"]  = flight->getDepartureTime();
        f["price"]          = flight->getPrice();
        f["hoursFlying"]    = flight->gethoursFlying();
        f["status"]         = static_cast<int>(flight->getFlightStatus());
        f["rows"]           = flight->getRows();
        f["cols"]           = flight->getColumnsPerRow();

        // save aircraft ID to re-link on load
        if (flight->getAssignedAircraft() != nullptr)
            f["aircraftID"] = flight->getAssignedAircraft()->getAircraftID();
        else
            f["aircraftID"] = "";

        // save crew IDs to re-link on load
        nlohmann::json crewIDs = nlohmann::json::array();
        for (const auto& member : flight->getAssignedCrew())
            crewIDs.push_back(member->getEmployeeID());
        f["crewIDs"] = crewIDs;

        // save seat map
        f["seatMap"] = flight->getSeatMap();

        flightsArray.push_back(f);
    }
    root["flights"] = flightsArray;

    // **** RESERVATIONS ****
    nlohmann::json resArray = nlohmann::json::array();
    for (const auto& res : this->activeReservations)
    {
        nlohmann::json r;
        r["bookingId"]        = res->getBookingId();
        r["seatNumber"]       = res->getSeatNumber();
        r["passengerUsername"] = res->getPassenger()->get_username();
        r["flightNumber"]     = res->getFlight()->getFlightNumber();
        r["status"]           = static_cast<int>(res->getBookingStatus());
        r["isCheckedIn"]      = res->getIsCheckedIn();

        if (res->getPayment() != nullptr)
        {
            r["payment"]["transactionID"] = res->getPayment()->getTransactionID();
            r["payment"]["amount"]        = res->getPayment()->getAmount();
            r["payment"]["method"]        = static_cast<int>(res->getPayment()->getMethod());
            r["payment"]["status"]        = static_cast<int>(res->getPayment()->getStatus());
            r["payment"]["timestamp"]     = res->getPayment()->getTimestamp();
        }
        resArray.push_back(r);
    }
    root["reservations"] = resArray;

    // *****WRITE TO FILE 
    std::ofstream file("data/airline_data.json");
    if (file.is_open())
    {
        file << root.dump(4); // 4 = indentation spaces
        file.close();
        std::cout << "[SYSTEM] Data saved successfully.\n";
    }
    else
    {
        std::cout << "[ERROR] Could not open data file for saving.\n";
    }
}



void AirlineSystem::loadData()
{
    std::ifstream file("data/airline_data.json");
    if (!file.is_open())
    {
        std::cout << "[SYSTEM] No saved data found. Starting fresh.\n";
        return;
    }

    nlohmann::json root;
    try { file >> root; }
    catch (...) 
    { 
        std::cout << "[ERROR] Failed to parse saved data.\n"; 
        return; 
    }
    file.close();

    
    for (const auto& u : root["users"])
    {
        std::string role = u["role"];
        std::shared_ptr<User> user = nullptr;

        if (role == "Passenger")
        {
            auto p = std::make_shared<Passenger>(
                u["userid"], u["username"], u["password"],
                u["full_name"], u["phone"], u["email"],
                u["passport"], u["seatPreference"], u["mealPreference"]
            );
            p->setLoyaltyPoints(u.value("loyaltyPoints", 0));
            user = p;
        }
        else if (role == "BookingAdmin")
        {
            user = std::make_shared<BookingAdmin>(
                u["userid"], u["username"], u["password"],
                u["full_name"], u["phone"], u["email"]
            );
        }
        else if (role == "Administrators")
        {
            user = std::make_shared<Administrators>(
                u["userid"], u["username"], u["password"],
                u["full_name"], u["phone"], u["email"]
            );
        }

        if (user != nullptr)
            this->userRegistry.push_back(user);
    }


    for (const auto& c : root["crew"])
    {
        std::string role = c["role"];
        std::shared_ptr<CrewMember> member = nullptr;

        if (role == "Pilot")
        {
            member = std::make_shared<Pilot>(
                c["employeeID"], c["name"], c["maxHours"],
                c["licenseNumber"], c["aircraftModel"]
            );
        }
        else if (role == "Flight Attendant")
        {
            std::vector<std::string> langs = c["languages"];
            member = std::make_shared<FlightAttendant>(
                c["employeeID"], c["name"], c["maxHours"], langs
            );
        }

        if (member != nullptr)
        {
            member->setCurrentFlightHours(c["currentHours"]);
            this->crewRegistry.push_back(member);
        }
    }

   
    for (const auto& a : root["fleet"])
    {
        std::vector<Maintenance> logs;
        for (const auto& m : a["maintenanceHistory"])
        {
            Maintenance log(
                m["maintenanceID"], m["scheduleDate"], m["completionDate"],
                m["description"], static_cast<MaintenanceStatus>(m["status"].get<int>())
            );
            logs.push_back(log);
        }

        auto plane = std::make_shared<Aircraft>(
            a["aircraftID"], a["model"], a["totalSeats"],
            a["isAvailable"], logs
        );
        this->fleetRegistry.push_back(plane);
    }

    for (const auto& f : root["flights"])
    {
        // re-link aircraft by ID
        std::shared_ptr<Aircraft> aircraft = nullptr;
        std::string aircraftID = f["aircraftID"];
        if (!aircraftID.empty())
            aircraft = this->getAircraftByID(aircraftID);

        // re-link crew by ID
        std::vector<std::shared_ptr<CrewMember>> crew;
        for (const auto& empID : f["crewIDs"])
        {
            for (const auto& member : this->crewRegistry)
            {
                if (member->getEmployeeID() == empID.get<std::string>())
                {
                    crew.push_back(member);
                    break;
                }
            }
        }

        // restore seat map
        std::vector<std::vector<std::string>> seatMap = f["seatMap"];

        auto flight = std::make_shared<Flight>(
            f["flightNumber"], f["origin"], f["destination"],
            f["departureTime"], f["price"], f["hoursFlying"],
            static_cast<FlightStatus>(f["status"].get<int>()),
            aircraft, crew, seatMap
        );
        flight->setRows(f["rows"].get<int>());
        flight->setcolPerRow(f["cols"].get<int>()); 
        this->flightSchedule.push_back(flight);
    }

    for (const auto& r : root["reservations"])
    {
        // re-link user and flight by ID
        auto user   = this->getUserByUsername(r["passengerUsername"]);
        auto flight = this->getFlightByNumber(r["flightNumber"]);

        if (user == nullptr || flight == nullptr) continue;

        auto res = std::make_shared<Reservation>(
            r["bookingId"], r["seatNumber"], user, flight,
            static_cast<BookingStatus>(r["status"].get<int>())
        );

        // restore check-in
        if (r["isCheckedIn"].get<bool>())
            res->setIsCheckedIn(true);

        // restore payment
        if (r.contains("payment"))
        {
            auto pay = std::make_shared<Payment>(
                r["payment"]["transactionID"],
                r["payment"]["amount"],
                static_cast<PaymentMethod>(r["payment"]["method"].get<int>()),
                r["payment"]["timestamp"]
            );
            pay->setStatus(static_cast<PaymentStatus>(r["payment"]["status"].get<int>()));
            res->setPayment(pay);
        }

        this->activeReservations.push_back(res);
    }

    std::cout << "[SYSTEM] Data loaded successfully.\n";
}