#include "salestransaction.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

SalesTransaction::SalesTransaction()
    : transactionID(""), productID(""), quantity(0), salePrice(0.0),
      totalAmount(0.0), transactionDate(""), transactionType("Sale"), 
      discountApplied(0.0) {
}

SalesTransaction::SalesTransaction(const std::string& transID, const std::string& prodID,
                                   int qty, double price, const std::string& date,
                                   const std::string& type)
    : transactionID(transID), productID(prodID), quantity(qty), salePrice(price),
      transactionDate(date), transactionType(type), discountApplied(0.0) {
    calculateTotalAmount();
}

SalesTransaction::~SalesTransaction() {
}

std::string SalesTransaction::getTransactionID() const { return transactionID; }
std::string SalesTransaction::getProductID() const { return productID; }
int SalesTransaction::getQuantity() const { return quantity; }
double SalesTransaction::getSalePrice() const { return salePrice; }
double SalesTransaction::getTotalAmount() const { return totalAmount; }
std::string SalesTransaction::getTransactionDate() const { return transactionDate; }
std::string SalesTransaction::getTransactionType() const { return transactionType; }
double SalesTransaction::getDiscountApplied() const { return discountApplied; }

void SalesTransaction::setQuantity(int qty) { 
    quantity = qty;
    calculateTotalAmount();
}

void SalesTransaction::setSalePrice(double price) { 
    salePrice = price;
    calculateTotalAmount();
}

void SalesTransaction::setDiscountApplied(double discount) { 
    if (discount >= 0.0 && discount <= 1.0) {
        discountApplied = discount;
        calculateTotalAmount();
    }
}

double SalesTransaction::calculateProfit(double costPrice) const {
    double revenue = totalAmount;
    double cost = costPrice * quantity;
    return revenue - cost;
}

void SalesTransaction::applyDiscount(double discountPercent) {
    if (discountPercent > 0.0 && discountPercent <= 100.0) {
        discountApplied = discountPercent / 100.0;
        calculateTotalAmount();
    }
}

void SalesTransaction::calculateTotalAmount() {
    double amount = salePrice * quantity;
    totalAmount = amount * (1.0 - discountApplied);
}

std::string SalesTransaction::toCSVString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << transactionID << "," << productID << "," << quantity << ","
        << salePrice << "," << totalAmount << "," << transactionDate << ","
        << transactionType;
    return oss.str();
}

void SalesTransaction::loadFromCSVString(const std::string& line) {
    std::istringstream iss(line);
    std::string field;
    
    std::getline(iss, transactionID, ',');
    std::getline(iss, productID, ',');
    
    std::getline(iss, field, ',');
    quantity = atoi(field.c_str());
    
    std::getline(iss, field, ',');
    salePrice = atof(field.c_str());
    
    std::getline(iss, field, ',');
    totalAmount = atof(field.c_str());
    
    std::getline(iss, transactionDate, ',');
    std::getline(iss, transactionType, ',');
    
    discountApplied = 0.0;
}

void SalesTransaction::displayInfo() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n--- Transaction Information ---\n";
    std::cout << "Transaction ID: " << transactionID << "\n";
    std::cout << "Product ID: " << productID << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Sale Price per unit: Rs. " << salePrice << "\n";
    std::cout << "Total Amount: Rs. " << totalAmount << "\n";
    std::cout << "Date: " << transactionDate << "\n";
    std::cout << "Type: " << transactionType << "\n";
    if (discountApplied > 0.0) {
        std::cout << "Discount Applied: " << (discountApplied * 100.0) << "%\n";
    }
}

std::string SalesTransaction::generateTransactionID() {
    static int counter = 1;
    std::ostringstream oss;
    oss << "T" << counter++;
    return oss.str();
}

std::string SalesTransaction::getCurrentDate() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    
    char buffer[11];  // "DD-MM-YYYY\0"
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
    return std::string(buffer);
}
