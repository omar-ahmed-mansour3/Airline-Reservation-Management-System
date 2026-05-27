#include"ConsoleUI.hpp"

ConsoleUI::ConsoleUI(AirlineSystem& sys) 
    : system(sys), loggedInUser(nullptr) 
{}




void ConsoleUI::startApp() 
{
    std::cout << "\n=================================================" << std::endl;
    std::cout << "      WELCOME TO THE AIRLINE MANAGEMENT SYSTEM     " << std::endl;
    std::cout << "=================================================" << std::endl;

    bool appIsRunning = true;
    int choice;

    while (appIsRunning) 
    {
       
        if (this->loggedInUser == nullptr) 
        {
            this->displayMainMenu();
            
            std::cin >> choice;

            switch (choice) 
            {
                case 1: 
                    this->handleLogin(); 
                    break;
                case 2: 
                    this->handleRegistration(); 
                    break;
                case 3: 
                    std::cout << "\nShutting down system..." << std::endl;
                    appIsRunning = false; 
                    break;
                default: 
                    std::cout << "[ERROR] Invalid selection. Please try again." << std::endl;
                    break;
            }
        }

        if (this->loggedInUser == nullptr)
            continue;

        std::string role = this->loggedInUser->getRole();

        
        if (role == "Administrators") 
        {
            this->displayAdminMenu();
        } 
        else if (role == "BookingAdmin") 
        {
            this->displayBookingAgentMenu();
        } 
        else if (role == "Passenger")
        {
            this->displayPassengerMenu();
        }
        else 
        {
            std::cout << "\n[ERROR] Unknown user role detected. Forcing logout." << std::endl;
            this->loggedInUser = nullptr;
        }
        
        
    }
}
// ************ MENU STATES ************
void ConsoleUI:: displayMainMenu()
{
    std::cout << "\n--- MAIN MENU ---" << std::endl;
            std::cout << "1. Login" << std::endl;
            std::cout << "2. Register New Account" << std::endl;
            std::cout << "3. Exit System" << std::endl;
            std::cout << "Please select an option (1-3): ";
}

void ConsoleUI::handleLogin() 
{
    std::string username, password;

    std::cout << "\n=============================================\n";
    std::cout << "                 SYSTEM LOGIN                \n";
    std::cout << "=============================================\n";
    
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;

    this->loggedInUser = system.loginUser(username, password);

    if (this->loggedInUser == nullptr) 
    {
        std::cout << "\n[ERROR] Invalid username or password. Please try again.\n";
        return;
    }

    std::cout << "\n[SUCCESS] Welcome back, " << loggedInUser->getFullName() << "!\n";


}

void ConsoleUI::handleRegistration() 
{
    std::string username, password, fullName, phone, email, passport;
    int roleChoice;

    std::cout << "\n=============================================\n";
    std::cout << "             SYSTEM REGISTRATION             \n";
    std::cout << "=============================================\n";
    
    std::cout << "Enter a New Username: \n";
    std::cin >> username;
    if (system.usernameExists(username)) {
        std::cout << "\n[ERROR] Username '" << username << "' is already taken. Registration aborted.\n";
        return;
    }
    
    std::cout << "Enter a New Password: \n";
    std::cin >> password;
    
    std::cout << "Enter Your Full Name: \n";
    std::cin.ignore(); 
    std::getline(std::cin, fullName);

    std::cout<<"Enter Phone Number: \n";
    std::cin>> phone;
    std::cout<<"Enter Email: \n";
    std::cin>> email;

    std::cout << "Select Role (1: Passenger, 2: Booking Agent, 3: Admin): \n";
    std::cin >> roleChoice;

    std::shared_ptr<User> newUser = nullptr;

    if (roleChoice == 1) 
    {
        std::cout << "Enter Passport Number: \n";
        std::cin >> passport;
        newUser = std::make_shared<Passenger>(0, username, password, fullName, phone, email, passport);
    } 
    else if (roleChoice == 2) 
    {
        newUser = std::make_shared<BookingAdmin>(0, username, password, fullName, phone, email);
    } 
    else if (roleChoice == 3) 
    {
        newUser = std::make_shared<Administrators>(0, username, password, fullName, phone, email);
    } 
    else 
    {
        std::cout << "\n[ERROR] Invalid role selection. Registration aborted.\n";
        return; 
    }

    system.registerNewUser(newUser);


    this->loggedInUser = newUser;

    std::cout << "\n[SUCCESS] Registration complete! Welcome, " << loggedInUser->getFullName() << "!\n";

}



// ************ ROLE-BASED DASHBOARDS ************
void ConsoleUI::displayPassengerMenu()
{
    int choice;
    bool stayLoggedIn = true;

    while (stayLoggedIn)
    {
        std::cout << "\n--- PASSENGER SERVICES MAIN MENU ---" << std::endl;
        std::cout << "Please choose a number:\n";
        std::cout << "1. View My Profile & Loyalty Points\n"
                  << "2. Search Available Flights\n"
                  << "3. Book a Flight & Select Seats\n"
                  << "4. View, Modify or Cancel a Reservation\n"
                  << "5. Perform Online Check-In\n"
                  << "6. Logout" << std::endl;
        
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                this->loggedInUser->showProfile();
                break;
            case 2:
            {
                std::string origin, dest, date;
                double maxPrice;
                std::cout << "Origin (leave blank to skip): ";      
                std::cin.ignore(); std::getline(std::cin, origin);
                std::cout << "Destination (leave blank to skip): "; 
                std::getline(std::cin, dest);
                std::cout << "Date (leave blank to skip): ";        
                std::getline(std::cin, date);
                std::cout << "Max Price (0 to skip): ";             
                std::cin >> maxPrice;

                auto results = system.searchAvailableFlights(origin, dest, date, maxPrice);
                for (const auto& flight : results)
                    flight->displayFlightDetails();
                break;


            }
            case 3:
                this->handleFlightBooking();
                break;
            case 4:
                this->handleBookingManagement();
                break;
            case 5:
                this->handleCheckIn();
                break;
            case 6: // Logout
                std::cout << "\n[SUCCESS] Passenger logged out." << std::endl;
                this->loggedInUser = nullptr; 
                stayLoggedIn = false;         
                break;   
            default:
                std::cout << "\n[ERROR] Invalid choice! Please select a valid number from 1 to 6." << std::endl;
                break;
        }
    }
}

void ConsoleUI::displayAdminMenu()
{
    int choice;
    bool stayLoggedIn = true;

    while (stayLoggedIn)
    {
        std::cout << "\n*** MASTER AIRLINE ADMINISTRATION CONSOLE ***" << std::endl;
        std::cout << "Please choose a number:\n";
        std::cout << "1. View Admin Profile\n"
                  << "2. Manage User Accounts\n"
                  << "3. Manage Flight Schedules\n"
                  << "4. Manage Aircraft & Fleet\n"
                  << "5. Assign Flight Crew\n"
                  << "6. Maintenance Management\n"      
                  << "7. View Operational & Financial Reports\n"
                  << "8. Logout & Exit System" << std::endl; 

        std::cin >> choice;

        switch (choice)
        {
            case 1:
                this->loggedInUser->showProfile(); 
                break;
            case 2: // Manage Users
                this->handleUserManagement();
                break;
            case 3: // Manage Flights
                this->handleFlightManagement();
                break;
            case 4: // Manage Fleet
                this->handleFleetManagement();
                break;
            case 5: // Assign Crew
                this->handleCrewAssignment();
                break;
            case 6: // Maintenance Management
                this->handleMaintenanceManagement();
                break;
            case 7: // View Reports
                this->handleReports();
                break;
            case 8: // Logout
                std::cout << "\n[SUCCESS] Master Admin console locked. Logged out safely." << std::endl;
                this->loggedInUser = nullptr;
                stayLoggedIn = false;
                break;
            default:
                std::cout << "\n[ERROR] Invalid choice! Please select a valid option (1-8)." << std::endl;
                break;
        }
    }
}

void ConsoleUI::displayBookingAgentMenu()
{
    int choice;
    bool stayLoggedIn = true;

    while (stayLoggedIn)
    {
        std::cout << "\n--- BOOKING ADMIN SERVICES MAIN MENU ---" << std::endl;
        std::cout << "Please choose a number:\n";
        std::cout << "1. View Staff Profile\n"
                  << "2. Search Available Flights\n"
                  << "3. Facilitate Passenger Booking & Seat Selection\n"
                  << "4. Process Booking Modification or Cancellation\n"
                  << "5. Manage Airport Counter Check-In\n"
                  << "6. Logout" << std::endl;
                  
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
                this->loggedInUser->showProfile(); 
                break;
            case 2:
            {
                std::string origin, dest, date;
                double maxPrice;
                std::cout << "Origin (leave blank to skip): ";      
                std::cin.ignore(); std::getline(std::cin, origin);
                std::cout << "Destination (leave blank to skip): "; 
                std::getline(std::cin, dest);
                std::cout << "Date (leave blank to skip): ";        
                std::getline(std::cin, date);
                std::cout << "Max Price (0 to skip): ";             
                std::cin >> maxPrice;

                auto results = system.searchAvailableFlights(origin, dest, date, maxPrice);
                for (const auto& flight : results)
                    flight->displayFlightDetails();
                break;
            }
            case 3:
                this->handleFlightBooking();
                break;
            case 4:
                this->handleBookingManagement();
                break;
            case 5:
                this->handleCheckIn();
                break;
            case 6: // Logout
                std::cout << "\n[SUCCESS] Booking Agent logged out safely." << std::endl;
                this->loggedInUser = nullptr;
                stayLoggedIn = false;
                break;   
            default:
                std::cout << "\n[ERROR] Invalid choice! Please select a valid number from 1 to 6." << std::endl;
                break;
        }
    }
}


//*************Admin Functions *************/

void ConsoleUI::handleFlightManagement()
{
    int choice;
    std::cout << "\n--- FLIGHT MANAGEMENT ---" << std::endl;
    std::cout << "1. Schedule New Flight\n"
              << "2. Update Flight Details\n"
              << "3. Cancel Flight\n"
              << "4. Remove Flight\n"
              << "5. Update Flight Status\n"
              << "6. Back" << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        std::string num, origin, dest, time;
        double price, hours;
        std::cout << "Flight Number: "; std::cin >> num;
        std::cout << "Origin: ";        std::cin >> origin;
        std::cout << "Destination: ";   std::cin >> dest;
        std::cout << "Departure Time: "; std::cin >> time;
        std::cout << "Price: ";         std::cin >> price;
        std::cout << "Hours Flying: ";  std::cin >> hours;

        auto flight = std::make_shared<Flight>(
            num, origin, dest, time, price, hours,
            FlightStatus::Scheduled, nullptr,
            std::vector<std::shared_ptr<CrewMember>>{},
            50, 6  // hard coded rows and columns
        );
        system.scheduleNewFlight(flight);
    }
    else if (choice == 2)
    {
        std::string num, origin, dest, time;
        double price;
        std::cout << "Flight Number to update: "; std::cin >> num;
        std::cout << "New Origin: ";        std::cin >> origin;
        std::cout << "New Destination: ";   std::cin >> dest;
        std::cout << "New Departure Time: "; std::cin >> time;
        std::cout << "New Price: ";         std::cin >> price;
        system.updateFlightDetails(num, origin, dest, time, price);
    }
    else if (choice == 3)
    {
        std::string num;
        std::cout << "Flight Number to cancel: "; std::cin >> num;
        system.cancelFlight(num);
    }
    else if (choice == 4)
    {
        std::string num;
        std::cout << "Flight Number to remove: "; std::cin >> num;
        system.removeFlight(num);
    }
    else if (choice == 5)
    {
        std::string num;
        std::cout << "Flight Number: "; std::cin >> num;

        auto flight = system.getFlightByNumber(num);
        if (flight == nullptr)
        {
            std::cout << "[ERROR] Flight not found.\n";
            return;
        }

        std::cout << "Select New Status:\n"
                  << "1. Scheduled\n"
                  << "2. Delayed\n"
                  << "3. Boarding\n"
                  << "4. Canceled\n"
                  << "Choice: ";
        int statusChoice;
        std::cin >> statusChoice;

        FlightStatus newStatus;
        switch (statusChoice)
        {
            case 1: newStatus = FlightStatus::Scheduled; break;
            case 2: newStatus = FlightStatus::Delayed;   break;
            case 3: newStatus = FlightStatus::Boarding;  break;
            case 4: newStatus = FlightStatus::Canceled;  break;
            default:
                std::cout << "[ERROR] Invalid status choice.\n";
                return;
        }

        flight->updateFlightStatus(newStatus);
        std::cout << "[SUCCESS] Flight " << num << " status updated.\n";
    }
}

void ConsoleUI::handleFleetManagement()
{
    int choice;
    std::cout << "\n--- FLEET MANAGEMENT ---" << std::endl;
    std::cout << "1. Add Aircraft\n"
              << "2. Update Aircraft Availability\n"
              << "3. Schedule Maintenance\n"
              << "4. Remove Aircraft\n"
              << "5. Back" << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        std::string id, model;
        int seats;
        std::cout << "Aircraft ID: ";  std::cin >> id;
        std::cout << "Model: ";        std::cin >> model;

        auto aircraft = std::make_shared<Aircraft>(
            id, model, 50, 6, true, std::vector<Maintenance>{}
        );
        system.addAircraftToFleet(aircraft);
    }
    else if (choice == 2)
    {
        std::string id;
        int avail;
        std::cout << "Aircraft ID: ";           std::cin >> id;
        std::cout << "Available? (1=Yes, 0=No): "; std::cin >> avail;
        system.updateAircraftAvailability(id, avail == 1);
    }
    else if (choice == 3)
    {
        std::string id, mID, sDate, desc;
        std::cout << "Aircraft ID: ";       std::cin >> id;
        std::cout << "Maintenance ID: ";    std::cin >> mID;
        std::cout << "Scheduled Date: ";    std::cin >> sDate;
        std::cout << "Description: ";       std::cin >> desc;

        Maintenance log(mID, sDate, "", desc, MaintenanceStatus::Scheduled);
        system.scheduleMaintenance(id, log);
    }
    else if (choice == 4)
    {
        std::string id;
        std::cout << "Aircraft ID to remove: "; std::cin >> id;
        system.removeAircraft(id);
    }
}

void ConsoleUI::handleCrewAssignment()
{
    std::string flightNum, empID;
    std::cout << "\n--- CREW ASSIGNMENT ---" << std::endl;
    std::cout << "Flight Number: ";    std::cin >> flightNum;
    std::cout << "Employee ID: ";      std::cin >> empID;

    // Search the crew registry for this employee
    std::shared_ptr<CrewMember> found = nullptr;
    for (const auto& member : system.getCrewByRole("Pilot"))
    {
        if (member->getEmployeeID() == empID)
        {
            found = member;
            break;
        }
    }
    if (found == nullptr)
    {
        for (const auto& member : system.getCrewByRole("Flight Attendant"))
        {
            if (member->getEmployeeID() == empID)
            {
                found = member;
                break;
            }
        }
    }

    if (found == nullptr)
    {
        std::cout << "[ERROR] No crew member with ID '" << empID << "' found." << std::endl;
        return;
    }

    system.assignCrewToFlight(flightNum, found);
}


void ConsoleUI::handleUserManagement()
{
    int choice;
    std::cout << "\n--- USER MANAGEMENT ---" << std::endl;
    std::cout << "1. Create New User\n"
              << "2. Update User\n"
              << "3. Delete User\n"
              << "4. Back" << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        this->handleCreateUser(); 
    }
    else if (choice == 2)
    {
        std::string username, fullName, phone, email, password;
        std::cout << "Enter username to update: "; std::cin >> username;
        if (!system.usernameExists(username))
        {
            std::cout << "[ERROR] User not found.\n";
            return;
        }
        std::cout << "New Full Name: "; std::cin >> fullName;
        std::cout << "New Phone: ";     std::cin >> phone;
        std::cout << "New Email: ";     std::cin >> email;
        std::cout << "New Password: ";  std::cin >> password;

        if (system.updateUser(username, fullName, phone, email, password))
            std::cout << "[SUCCESS] User updated.\n";
        else
            std::cout << "[ERROR] Update failed.\n";
    }
    else if (choice == 3)
    {
        std::string username;
        std::cout << "Enter username to delete: "; std::cin >> username;

        if (system.deleteUser(username))
            std::cout << "[SUCCESS] User deleted.\n";
        else
            std::cout << "[ERROR] User not found.\n";
    }
}

//exact same function as handleRegisteration but does not log u in automatically.
void ConsoleUI::handleCreateUser() 
{
    std::string username, password, fullName , phone, email;
    int roleChoice;

    std::cout << "\n=============================================\n";
    std::cout << "            REGISTRATING A  User              \n";
    std::cout << "=============================================\n";
    
    std::cout << "Enter a New Username: \n";
    std::cin >> username;
    if (system.usernameExists(username)) {
        std::cout << "\n[ERROR] Username '" << username << "' is already taken. Registration aborted.\n";
        return;
    }
    
    std::cout << "Enter a New Password: \n";
    std::cin >> password;
    
    std::cout << "Enter Full Name: \n";
    std::cin.ignore(); 
    std::getline(std::cin, fullName);
    
    std::cout << "Enter Phone Number: \n";
    std::cin >> phone;
    
    std::cout << "Enter Email: \n";
    std::cin >> email;

    std::cout << "Select Role (1: Passenger, 2: Booking Agent, 3: Admin): \n";
    std::cin >> roleChoice;

    std::shared_ptr<User> newUser = nullptr;

    if (roleChoice == 1) 
    {
        newUser = std::make_shared<Passenger>(0, username, password, fullName, phone, email, "N/A");
    } 
    else if (roleChoice == 2) 
    {
        newUser = std::make_shared<BookingAdmin>(0, username, password, fullName, phone, email);
    } 
    else if (roleChoice == 3) 
    {
        newUser = std::make_shared<Administrators>(0, username, password, fullName, phone, email);
    } 
    else 
    {
        std::cout << "\n[ERROR] Invalid role selection. Registration aborted.\n";
        return; 
    }

    system.registerNewUser(newUser);
    std::cout << "\n[SUCCESS] User '" << newUser->getFullName() << "' created successfully.\n";

}


void ConsoleUI::handleMaintenanceManagement()
{
    int choice;
    bool stayInMenu = true;

    while (stayInMenu)
    {
        std::cout << "\n--- MAINTENANCE MANAGEMENT ---\n"
                  << "1. Schedule Maintenance\n"
                  << "2. Mark Maintenance Complete\n"
                  << "3. View Maintenance Logs\n"
                  << "4. Back\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string id, mID, sDate, desc;
            std::cout << "Aircraft ID: ";       std::cin >> id;
            std::cout << "Maintenance ID: ";    std::cin >> mID;
            std::cout << "Scheduled Date: ";    std::cin >> sDate;
            std::cout << "Description: ";       
            std::cin.ignore(); 
            std::getline(std::cin, desc);

            Maintenance log(mID, sDate, "", desc, MaintenanceStatus::Scheduled);
            system.scheduleMaintenance(id, log);
        }
        else if (choice == 2)
        {
            std::string aircraftID, maintenanceID, completionDate;
            std::cout << "Aircraft ID: ";        std::cin >> aircraftID;
            std::cout << "Maintenance ID: ";     std::cin >> maintenanceID;
            std::cout << "Completion Date: ";    std::cin >> completionDate;

            system.completeMaintenance(aircraftID, maintenanceID, completionDate);
        }
        else if (choice == 3)
        {
            std::string aircraftID;
            std::cout << "Aircraft ID: "; std::cin >> aircraftID;
            system.viewMaintenanceLogs(aircraftID);
        }
        else if (choice == 4)
        {
            stayInMenu = false;
        }
        else
        {
            std::cout << "[ERROR] Invalid choice.\n";
        }
    }
}

//****************BOOKING FUNCTIONS*****************
void ConsoleUI::handleFlightBooking()
{
    std::shared_ptr<User> bookingUser = resolvePassenger();
    if (bookingUser == nullptr) return;

    std::string flightNum;
    std::cout << "\nEnter Flight Number: ";
    std::cin >> flightNum;

    auto flight = system.getFlightByNumber(flightNum);
    if (flight == nullptr)
    {
        std::cout << "[ERROR] Flight '" << flightNum << "' not found.\n";
        return;
    }

    flight->displayFlightDetails();
    flight->displayAvailableSeats();

    std::string seat;
    while (true)
    {
        std::cout << "\nEnter Seat Number (e.g. 03B) or 'XXX' to cancel: ";
        std::cin >> seat;
        if (seat == "XXX")
        {
            std::cout << "[INFO] Booking cancelled.\n";
            return;
        }

        if (seat.length() < 3)
        {
            std::cout << "[ERROR] Invalid seat format. Use format like '01A'. Try again.\n";
            continue;
        }

        try
        {
            std::string rowPart = seat.substr(0, seat.length() - 1);
            char colChar = std::toupper(seat.back());
            int rowIndex = std::stoi(rowPart) - 1;
            int colIndex = colChar - 'A';

            const auto& seatMap = flight->getSeatMap();
            if (rowIndex < 0 || rowIndex >= flight->getRows() ||
                colIndex < 0 || colIndex >= flight->getColumnsPerRow())
            {
                std::cout << "[ERROR] Seat " << seat << " does not exist on this flight. Try again.\n";
                continue;
            }

            if (seatMap[rowIndex][colIndex] == "X")
            {
                std::cout << "[WARNING] Seat " << seat << " is already occupied. Pick another.\n";
                continue;
            }

            break;
        }
        catch (...)
        {
            std::cout << "[ERROR] Invalid seat format. Use format like '01A'. Try again.\n";
            continue;
        }
    }

    std::cout << "\nSelect Payment Method:\n"
              << "1. Credit Card\n"
              << "2. Debit Card\n"
              << "3. PayPal\n"
              << "4. Loyalty Points\n"
              << "5. Cash\n"
              << "Choice: ";
    int payChoice;
    std::cin >> payChoice;

    PaymentMethod method;
    switch (payChoice)
    {
        case 1: method = CreditCard;     break;
        case 2: method = DebitCard;      break;
        case 3: method = PayPal;         break;
        case 4: method = LoyaltyPoints;  break;
        case 5: method = Cash;           break;
        default:
            std::cout << "[ERROR] Invalid payment method.\n";
            return;
    }

    int loyaltyPointsToUse = 0;
    auto passenger = std::dynamic_pointer_cast<Passenger>(bookingUser);
    if (passenger != nullptr && passenger->getLoyaltyPoints() > 0)
    {
        std::cout << "\nYou have " << passenger->getLoyaltyPoints()
                  << " loyalty points (each worth $10 off).\n";
        std::cout << "How many points to redeem? (0 to skip): ";
        std::cin >> loyaltyPointsToUse;
    }

    system.processNewBooking(bookingUser, flight, seat, method, loyaltyPointsToUse);
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

void ConsoleUI::handleBookingManagement()
{
    std::shared_ptr<User> bookingUser = resolvePassenger();
    if (bookingUser == nullptr) return;

    auto reservations = system.getUserReservations(bookingUser->get_username());

    if (reservations.empty())
    {
        std::cout << "[INFO] You have no active reservations.\n";
        return;
    }

    std::cout << "\n--- YOUR RESERVATIONS ---\n";
    for (int i = 0; i < reservations.size(); i++)
    {
        std::cout << i + 1 << ". ";
        reservations[i]->displayTicket();
    }

    std::cout << "Enter reservation number (0 to go back): ";
    int pick;
    std::cin >> pick;

    if (pick == 0) return;

    if (pick < 1 || pick > reservations.size())
    {
        std::cout << "[ERROR] Invalid selection.\n";
        return;
    }

    auto selected = reservations[pick - 1];

    std::cout << "\n1. Modify Seat\n"
              << "2. Cancel Reservation\n"
              << "3. Back\n"
              << "Choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        selected->getFlight()->displayAvailableSeats();

        std::string newSeat;
        while (true)
        {
            std::cout << "Enter new seat number or 'XXX' to cancel: ";
            std::cin >> newSeat;

            if (newSeat == "XXX") return;

            if (newSeat.length() < 3)
            {
                std::cout << "[ERROR] Invalid format. Use format like '01A'.\n";
                continue;
            }

            try
            {
                std::string rowPart = newSeat.substr(0, newSeat.length() - 1);
                char colChar = std::toupper(newSeat.back());
                int rowIndex = std::stoi(rowPart) - 1;
                int colIndex = colChar - 'A';

                const auto& seatMap = selected->getFlight()->getSeatMap();
                if (rowIndex < 0 || rowIndex >= selected->getFlight()->getRows() ||
                    colIndex < 0 || colIndex >= selected->getFlight()->getColumnsPerRow())
                {
                    std::cout << "[ERROR] Seat does not exist. Try again.\n";
                    continue;
                }

                if (seatMap[rowIndex][colIndex] == "X")
                {
                    std::cout << "[WARNING] Seat already occupied. Pick another.\n";
                    continue;
                }

                break;
            }
            catch (...)
            {
                std::cout << "[ERROR] Invalid format. Try again.\n";
                continue;
            }
        }

        selected->modifySeat(newSeat);
    }
    else if (choice == 2)
    {
        system.cancelUserReservation(selected->getBookingId());
    }
}

std::shared_ptr<User> ConsoleUI::resolvePassenger()
{
    if (loggedInUser->getRole() == "Passenger")
        return loggedInUser;

    std::string passengerUsername;
    std::cout << "Enter Passenger Username: ";
    std::cin >> passengerUsername;

    auto passenger = system.getUserByUsername(passengerUsername);
    if (passenger == nullptr)
    {
        std::cout << "[ERROR] Passenger '" << passengerUsername << "' not found.\n";
        return nullptr;
    }
    if (passenger->getRole() != "Passenger")
    {
        std::cout << "[ERROR] That account is not a passenger.\n";
        return nullptr;
    }
    return passenger;
}

void ConsoleUI::handleCheckIn()
{
    std::shared_ptr<User> passenger = resolvePassenger();
    if (passenger == nullptr) return;

    auto reservations = system.getUserReservations(passenger->get_username());
    if (reservations.empty())
    {
        std::cout << "[INFO] No reservations found for check-in." << std::endl;
        return;
    }

    std::cout << "\n--- CHECK-IN ---\n";
    for (int i = 0; i < reservations.size(); i++)
    {
        std::cout << i + 1 << ". ";
        reservations[i]->displayTicket();
    }

    std::cout << "Select reservation number to check in (0 to go back): ";
    int selection;
    std::cin >> selection;
    if (selection == 0) return;

    if (selection < 1 || selection > reservations.size())
    {
        std::cout << "[ERROR] Invalid selection." << std::endl;
        return;
    }

    auto selected = reservations[selection - 1];
    if (selected->getIsCheckedIn())
    {
        std::cout << "[INFO] Reservation already checked in." << std::endl;
        return;
    }

    system.checkInPassenger(selected->getBookingId());
}

void ConsoleUI::handleReports()
{
    int choice;
    bool stayInMenu = true;

    while (stayInMenu)
    {
        std::cout << "\n--- REPORTS ---\n"
                  << "1. Maintenance Report\n"
                  << "2. User Activity Report\n"
                  << "3. Flight Report\n"
                  << "4. Back\n"
                  << "Choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                system.generateMaintenanceReport();
                break;
            case 2:
                system.generateUserActivityReport();
                break;
            case 3:
                system.generateFlightReport();
                break;
            case 4:
                stayInMenu = false;
                break;
            default:
                std::cout << "[ERROR] Invalid choice.\n";
                break;
        }
    }
}

