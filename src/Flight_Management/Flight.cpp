#include "Flight.hpp"




//**********rule of 5***************** */
    //if u have seat map ready
    Flight::Flight( std::string flightNumber, std::string origin, std::string destination, std::string departureTime,
     double Price,double hoursFlying, FlightStatus status, std:: shared_ptr<Aircraft> assignedAircraft, 
     std:: vector< std::shared_ptr<CrewMember>>assignedCrew, std::vector<std::vector<std::string>>seatMap):
     flightNumber(flightNumber), origin(origin), destination(destination), departureTime(departureTime),
     Price(Price), hoursFlying(hoursFlying), status(status), assignedAircraft(assignedAircraft), assignedCrew(assignedCrew),seatMap(seatMap)
    {}

    // if you have the row and col but not the vector
     Flight::Flight( std::string flightNumber, std::string origin, std::string destination, std::string departureTime,
     double Price, double hoursFlying, FlightStatus status, std:: shared_ptr<Aircraft> assignedAircraft, 
     std:: vector< std::shared_ptr<CrewMember>>assignedCrew,int rows, int columnsPerRow  ):
     flightNumber(flightNumber), origin(origin), destination(destination), departureTime(departureTime),
     Price(Price), hoursFlying(hoursFlying), status(status), assignedAircraft(assignedAircraft), assignedCrew(assignedCrew),
     rows(rows), columnsPerRow(columnsPerRow)
    {
        this->seatMap.resize(rows, std::vector<std::string>(columnsPerRow, "O"));
    }
     

     
     

    Flight::Flight(const Flight& other)
    {
        this->flightNumber = other.flightNumber;
        this->origin = other.origin;
        this->destination = other.destination ;
        this->departureTime = other.departureTime ;
        this->Price = other.Price;
        this->hoursFlying = other.hoursFlying;
        this->status = other.status ;
        this->assignedAircraft = other.assignedAircraft ;
        this->assignedCrew = other.assignedCrew ;
        this->seatMap = other.seatMap;
    }
    Flight& Flight:: operator=(const Flight& other)
    {
        if(this != &other)
        {
            this->flightNumber = other.flightNumber;
            this->origin = other.origin;
            this->destination = other.destination ;
            this->departureTime = other.departureTime ;
            this->Price = other.Price;
            this->hoursFlying = other.hoursFlying;
            this->status = other.status ;
            this->assignedAircraft = other.assignedAircraft ;
            this->assignedCrew = other.assignedCrew ;
            this->seatMap = other.seatMap;
        }
        return *this;
    }

    Flight::~Flight(){}



//************** Getters ************** */

std::string Flight::getFlightNumber() const 
{
    return this->flightNumber;
}

std::string Flight::getOrigin() const 
{
    return this->origin;
}

std::string Flight::getDestination() const 
{
    return this->destination;
}

std::string Flight::getDepartureTime() const 
{
    return this->departureTime;
}

double Flight::getPrice() const 
{
    return this->Price;
}

double Flight::gethoursFlying() const
{
    return this->hoursFlying;
}

FlightStatus Flight::getFlightStatus() const 
{
    return this->status;
}

std::shared_ptr<Aircraft> Flight::getAssignedAircraft() const 
{
    return this->assignedAircraft;
}


const std::vector<std::shared_ptr<CrewMember>>& Flight::getAssignedCrew() const 
{
    return this->assignedCrew;
}

int Flight:: getRows() const 
{ return rows; }

int Flight:: getColumnsPerRow() const 
{ return columnsPerRow; }

const std::vector<std::vector<std::string>>& Flight::getSeatMap() const 
{
    return this->seatMap;
}


//************** Setters************** */

void Flight::setFlightNumber(const std::string& fNum) 
{
    this->flightNumber = fNum;
}

void Flight::setOrigin(const std::string& orig) 
{
    this->origin = orig;
}

void Flight::setDestination(const std::string& dest) 
{
    this->destination = dest;
}

void Flight::setDepartureTime(const std::string& dTime) 
{
    this->departureTime = dTime;
}

void Flight::setPrice(double price) 
{
    this->Price = price;
}

void Flight::sethoursFlying(double hoursFlying) 
{
    this->hoursFlying = hoursFlying;
}

void Flight::setFlightStatus(FlightStatus newStatus) 
{
    this->status = newStatus;
}

void Flight::setAssignedAircraft(std::shared_ptr<Aircraft> aircraft) 
{
    this->assignedAircraft = aircraft;
}

void Flight::setAssignedCrew(const std::vector<std::shared_ptr<CrewMember>>& crew) 
{
    this->assignedCrew = crew;
}

void Flight:: setRows(int rows)
{this->rows=rows;}

void Flight:: setcolPerRow(int col)
{this->columnsPerRow=col;}

void Flight::setSeatMap(const std::vector<std::vector<std::string>>& seats) 
{
    this->seatMap = seats;
}



//************class specific functions************************* */
/***general flight managment*/

bool Flight:: assignCrewMember(std::shared_ptr<CrewMember> crew)
{
    if(crew->isWithinLimits(this->hoursFlying)) 
    {
        this->assignedCrew.push_back(crew);
        return true;
    }
    return false;
}

void Flight:: updateFlightStatus( FlightStatus newStatus)
{
    this->status = newStatus;
}

void Flight::displayFlightDetails() const
{
    std::string statusStr;
    switch (this->status)
    {
        case Status::Scheduled:  statusStr = "Scheduled"; break;
        case Status::InProgress: statusStr = "In Progress"; break;
        case Status::Completed:  statusStr = "Completed"; break;
        default:                 statusStr = "Unknown"; break;
    }

    std::cout << "\n=============================================" << std::endl;
    std::cout << "  FLIGHT DETAILS: " << this->flightNumber << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Route:            " << this->origin << " -> " << this->destination << std::endl;
    std::cout << "Departure Time:   " << this->departureTime << std::endl;
    std::cout << "Flight Duration:  " << this->hoursFlying << " hours" << std::endl;
    std::cout << "Ticket Price:     $" << this->Price << std::endl;
    std::cout << "Flight Status:    " << statusStr << std::endl;
    
    std::cout << "Assigned Aircraft: ";
    if (this->assignedAircraft != nullptr) 
    {
        std::cout << this->assignedAircraft->getModel() << " (ID: " 
            << this->assignedAircraft->getAircraftID() << ")" << std::endl;
    } 
    else 
    {
        std::cout << "No Aircraft Assigned Yet" << std::endl;
    }
    std::cout << "Total Crew Count: " << this->assignedCrew.size() << std::endl;
    std::cout << "=============================================" << std::endl;
}

void Flight:: printCrewRoster() const
{
    for(auto member :this->assignedCrew)
    {
        std::cout<<"\n---Crew members---"<<std::endl;
        member->showStaffProfile() ;
        std::cout<<std::endl;
    }
    
}


void Flight::displayAvailableSeats() const 
{
    std::cout << "\n=== SEATING CHART FOR FLIGHT " << this->flightNumber << " ===\n";
    
    // 1. Generate the Column Alphabetic Labels Heade (A, B, C, D, E...)
    std::cout << "     "; 
    for (int col = 0; col < this->columnsPerRow; col++) 
    {
        char seatLetter = char('A' + col);
        std::cout << " " << seatLetter << "  ";
        
        //label spacing gap in the middle column index to show the aisle header
        if (col == (this->columnsPerRow / 2) - 1) 
        {
            std::cout << "     "; 
        }
    }
    std::cout << "\n-------------------------------------------------\n";

    int availableSeatsCount = 0; 
    int totalSeatsCount = (this->rows) * (this->columnsPerRow);

    //Loop through each row 
    for (int r = 0; r < this->rows; r++) 
    {
        // Pad row numbers '0' if single digit 
        if (r + 1 < 10) std::cout << "0";
        std::cout << (r + 1) << "  ";

        // Loop through columns 
        for (int c = 0; c < this->columnsPerRow; c++) 
        {
            std::cout << "[" << this->seatMap[r][c] << "]";
            
            // If the seat contains "O", it means it is vacant/open
            if (this->seatMap[r][c] == "O") 
            {
                availableSeatsCount++;
            }
            
            
            if (c == (this->columnsPerRow / 2) - 1) 
            {
                std::cout << " --- "; // Represents the central aisle path
            }
            else 
            {
                std::cout << " "; // Default space between adjacent seats
            }
        }
        std::cout << "\n"; // End of row line break
    }
    std::cout << "=================================================\n";
    
    std::cout << "Seats Available = " << availableSeatsCount << " / " << totalSeatsCount << std::endl;
}


bool Flight::reserveSeat(std::string seatNumber) 
{
    // Basic input safety check. example: "01A" >=3
    if (seatNumber.length() < 3) 
    {
        std::cout << "[ERROR] Invalid seat format. Please use a format like '01A' or '12C'." << std::endl;
        return false;
    }

    try 
    {
        //Parse out the row number (all characters except the last one)
        std::string rowPart = seatNumber.substr(0, seatNumber.length() - 1);
        int rowIndex = std::stoi(rowPart) - 1; // Convert to 0-indexed integer, also may throw exception

        //Parse out the column letter (the very last character)
        char colChar = std::toupper(seatNumber.back());
        int colIndex = colChar - 'A'; // a becomes 0, b becomes 1, etc

        //Boundary check: Make sure the seat actually exists 
        if (rowIndex < 0 || rowIndex >= this->rows || colIndex < 0 || colIndex >= this->columnsPerRow) 
        {
            std::cout << "[ERROR] Seat " << seatNumber << " does not exist on this flight." << std::endl;
            return false;
        }

        //Seat Availability Check
        if (this->seatMap[rowIndex][colIndex] == "X") 
        {
            std::cout << "[WARNING] Seat " << seatNumber << " is already occupied!" << std::endl;
            return false;
        }

        //book the seat
        this->seatMap[rowIndex][colIndex] = "X"; // Mark as Taken
        std::cout << "[SUCCESS] Seat " << seatNumber << " has been successfully reserved." << std::endl;
        return true;
    }
    catch (...) 
    {
        std::cout << "[ERROR] Critical parsing error. Please check your seat number format." << std::endl;
        return false;
    }
}

void Flight::releaseSeat(std::string seatNumber) 
{
    if (seatNumber.length() < 3) 
    {
        std::cout << "[ERROR] Invalid seat format. Use a format like '01A'." << std::endl;
        return;
    }

    try 
    {
        //Parse row and column indices
        std::string rowPart = seatNumber.substr(0, seatNumber.length() - 1);
        int rowIndex = std::stoi(rowPart) - 1;
        char colChar = std::toupper(seatNumber.back());
        int colIndex = colChar - 'A';

        //Boundary validation
        if (rowIndex < 0 || rowIndex >= this->rows || colIndex < 0 || colIndex >= this->columnsPerRow) 
        {
            std::cout << "[ERROR] Seat " << seatNumber << " does not exist on this flight." << std::endl;
            return;
        }

        //Cancellation check
        if (this->seatMap[rowIndex][colIndex] == "O") 
        {
            std::cout << "[INFO] Seat " << seatNumber << " is already vacant. No action needed." << std::endl;
            return;
        }

        //Un-book the seat
        this->seatMap[rowIndex][colIndex] = "O"; 
        std::cout << "[SUCCESS] Reservation canceled. Seat " << seatNumber << " is now available." << std::endl;
    }
    catch (...) 
    {
        std::cout << "[ERROR] Critical parsing error. Seat cancellation failed." << std::endl;
    }
}