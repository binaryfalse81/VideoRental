#pragma once

#include <vector>
#include "Movie.cpp"
#include "Rental.cpp"

class Customer {

private:
    string name;
    vector<Rental> rentals;

    string to_string_with_short_precision(double tar)
    {
        char buf[20] = { 0 };
        sprintf_s(buf, sizeof(buf), "%.1f", tar);
        return string(buf);
    }

public:
    Customer(const string& name) : name(name) {}

    void addRental(Rental arg)
    {
        rentals.push_back(arg);
    }

    string getName()
    {
        return name;
    }

    string statement()
    {
        string result = getStatementHeader();
        result += getRentalLineReport();
        result += getStatementFooter();

        return result;
    }

    string getStatementFooter(void)
    {
        string result;
        result += "Amount owed is " + to_string_with_short_precision(getTotalAmount()) + "\n";
        result += "You earned " + std::to_string(getFrequentRenterPonints()) + " frequent renter points";

        return result;
    }

    string getStatementHeader(void)
    {
        return "Rental Record for " + getName() + "\n";
    }

    string getRentalLineReport(void)
    {
        string result;
        for (Rental each : rentals)
        {
            result += "\t" + each.getMovie().getTitle() + "\t";
            result += to_string_with_short_precision(each.getCharge()) + "\n";
        }

        return result;
    }

    int getFrequentRenterPonints(void)
    {
        int frequentRenterPoints = 0;

        for (Rental each : rentals)
        {
            frequentRenterPoints += each.getMovie().getFrequentRenterPonintsFor(each.getDaysRented());
        }

        return frequentRenterPoints;
    }

    double getTotalAmount(void)
    {
        double totalAmount = 0;

        for (Rental each : rentals)
        {
            totalAmount += each.getCharge();
        }

        return totalAmount;
    }
};
