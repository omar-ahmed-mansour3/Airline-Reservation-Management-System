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

void ConsoleUI::handleLogin() {
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

void ConsoleUI::handleRegistration() {
    std::string username, password, fullName;
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
    
    std::cout << "Enter Full Name (No spaces): \n";
    std::cin >> fullName;

    std::cout << "Select Role (1: Passenger, 2: Booking Agent, 3: Admin): \n";
    std::cin >> roleChoice;

    std::shared_ptr<User> newUser = nullptr;

    if (roleChoice == 1) 
    {
        newUser = std::make_shared<Passenger>(0, username, password, fullName, "N/A", "N/A", "N/A");
    } 
    else if (roleChoice == 2) 
    {
        newUser = std::make_shared<BookingAdmin>(0, username, password, fullName, "N/A", "N/A");
    } 
    else if (roleChoice == 3) 
    {
        newUser = std::make_shared<Administrators>(0, username, password, fullName, "N/A", "N/A");
    } 
    else 
    {
        std::cout << "\n[ERROR] Invalid role selection. Registration aborted.\n";
        return; 
    }

    system.registerNewUser(newUser);


    this->loggedInUser = newUser;

    std::cout << "\n[SUCCESS] Registration complete! Welcome, " << loggedInUser->getFullName() << "!\n";


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
                  << "4. Modify or Cancel a Reservation\n"
                  << "5. Perform Online Check-In\n"
                  << "6. Logout" << std::endl;
        
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                this->loggedInUser->showProfile();
                break;
            case 2:
                // TODO: system.searchAvailableFlights(...)
                break;
            case 3:
                // TODO: system.processNewBooking(...)
                break;
            case 4:
                // TODO: modify/cancel logic
                break;
            case 5:
                // TODO: check-in logic
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
                  << "6. View Operational & Financial Reports\n"
                  << "7. Logout & Exit System" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
            case 1:
                this->loggedInUser->showProfile(); 
                break;
            case 2: // Manage Users
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
            case 6: // View Reports
                break;
            case 7: // Logout
                std::cout << "\n[SUCCESS] Master Admin console locked. Logged out safely." << std::endl;
                this->loggedInUser = nullptr;
                stayLoggedIn = false;
                break;
            default:
                std::cout << "\n[ERROR] Invalid choice! Please select a valid option (1-7)." << std::endl;
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
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
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
              << "5. Back" << std::endl;
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
            10, 6  // default rows and columns
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
        std::cout << "Total Seats: ";  std::cin >> seats;

        auto aircraft = std::make_shared<Aircraft>(
            id, model, seats, true, std::vector<Maintenance>{}
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