 #include "Payment.hpp"

// ************ Rule of 5 *******************


Payment::Payment(std::string txID, double amt, PaymentMethod payMethod, std::string time)
    : transactionID(std::move(txID)),
      amount(amt >= 0.0 ? amt : 0.0), // Prevents negative payments
      method(payMethod),
      status(PaymentStatus::Pending),                
      timestamp(std::move(time))
{}


Payment::Payment(const Payment& other)
{
    this->transactionID = other.transactionID;
    this->amount = other.amount;
    this->method = other.method;
    this->status = other.status;
    this->timestamp = other.timestamp;
}


Payment& Payment::operator=(const Payment& other)
{
    if (this != &other)
    {
        this->transactionID = other.transactionID;
        this->amount = other.amount;
        this->method = other.method;
        this->status = other.status;
        this->timestamp = other.timestamp;
    }
    return *this;
}


Payment::~Payment() {}


// ************ GETTERS *************************

std::string Payment::getTransactionID() const 
{
    return this->transactionID;
}

double Payment::getAmount() const 
{
    return this->amount;
}

PaymentMethod Payment::getMethod() const 
{
    return this->method;
}

std::string Payment::getTimestamp() const 
{
    return this->timestamp;
}

PaymentStatus Payment::getStatus() const 
{
    return this->status;
}

//Returns string instead of PaymentStatus
std::string Payment::getStatusString() const 
{
    switch (this->status) {
        case PaymentStatus::Pending:   return "Pending";
        case PaymentStatus::Completed: return "Completed";
        case PaymentStatus::Failed:    return "Failed";
        case PaymentStatus::Refunded:  return "Refunded";
        default:                       return "Unknown";
    }
}

//Returns string 
std::string Payment::getMethodString() const 
{
    switch (this->method) {
        case CreditCard:    return "Credit Card";
        case DebitCard:     return "Debit Card";
        case PayPal:        return "PayPal";
        case LoyaltyPoints: return "Loyalty Points";
        case Cash:          return "Cash";
        default:            return "Unknown";
    }
}


// ************ SETTERS *************************

void Payment::setTransactionID(const std::string& txID) 
{
    this->transactionID = txID;
}

void Payment::setAmount(double amt) 
{
    if (amt >= 0.0) {
        this->amount = amt;
    }
}

void Payment::setMethod(PaymentMethod payMethod) 
{
    this->method = payMethod;
}

void Payment::setStatus(PaymentStatus newStatus) 
{
    this->status = newStatus;
}

void Payment::setTimestamp(const std::string& time) 
{
    this->timestamp = time;
}


//************ Class Specific Functions *************************

bool Payment::processPayment() 
{
    if (this->status == PaymentStatus::Completed) 
    {
        std::cout << "[INFO] Transaction " << this->transactionID << " has already been paid." << std::endl;
        return false;
    }

    std::cout << "Attempting to charge $" << this->amount << " via " << this->getMethodString() << "..." << std::endl;
    
    // Simulating a 100% successful charge for now
    bool paymentSuccessful = true; 

    if (paymentSuccessful) 
    {
        this->status = PaymentStatus::Completed;
        std::cout << "[SUCCESS] Payment of $" << this->amount << " completed." << std::endl;
        return true;
    } 
    else 
    {
        this->status = PaymentStatus::Failed;
        std::cout << "[ERROR] Payment was declined or failed to process." << std::endl;
        return false;
    }
}

// What it does: Reverses a completed charge
bool Payment::processRefund() 
{
    if (this->status != PaymentStatus::Completed) 
    {
        std::cout << "[ERROR] Cannot refund transaction " << this->transactionID << ". Status is: " << this->getStatusString() << "." << std::endl;
        return false;
    }

    std::cout << "Processing refund of $" << this->amount << " to " << this->getMethodString() << "..." << std::endl;
    this->status = PaymentStatus::Refunded;
    std::cout << "[SUCCESS] Refund completed successfully." << std::endl;
    return true;
}


void Payment::displayReceipt() const 
{
    std::cout << "\n=============================================" << std::endl;
    std::cout << "               PAYMENT RECEIPT               " << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Transaction ID:  " << this->transactionID << std::endl;
    std::cout << "Date/Time:       " << this->timestamp << std::endl;
    std::cout << "Payment Method:  " << this->getMethodString() << std::endl;
    std::cout << "Amount:          $" << this->amount << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Status:          " << this->getStatusString() << std::endl;
    std::cout << "=============================================\n" << std::endl;
}