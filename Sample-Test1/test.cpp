#include "pch.h"
#include "../Project1/Customer.cpp";
#include "../Project1/Rental.cpp";
#include "../Project1/Movie.cpp";

const string NAME = string("NAME_NOT_IMPORTANT");
const string TITLE = string("TITLE_NOT_IMPORTANT");

class CustomerFixture : public testing::Test
{
public:
    Customer customer = Customer(NAME);

    Rental createRentalFor(int daysRented, int priceCode)
    {
        Movie movie = Movie(TITLE, priceCode);
        Rental rental = Rental(movie, daysRented);

        return rental;
    }
};

TEST_F(CustomerFixture, StatementForNoRental)
{
    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("Amount owed is 0.0\n")
        + string("You earned 0 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForRegularMovieRentalForLessThan3Days)
{
    customer.addRental(createRentalFor(2, Movie::REGULAR));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t2.0\n")
        + string("Amount owed is 2.0\n")
        + string("You earned 1 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForRegularMovieRentalForMoreThan2Days)
{
    customer.addRental(createRentalFor(3, Movie::REGULAR));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t3.5\n")
        + string("Amount owed is 3.5\n")
        + string("You earned 1 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForNewReleaseMovie)
{
    customer.addRental(createRentalFor(1, Movie::NEW_RELEASE));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t3.0\n")
        + string("Amount owed is 3.0\n")
        + string("You earned 1 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForChildrensMovieRentalMoreThan3Days)
{
    customer.addRental(createRentalFor(4, Movie::CHILDRENS));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t3.0\n")
        + string("Amount owed is 3.0\n")
        + string("You earned 1 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForChildrensMovieRentalMoreThan4Days)
{
    customer.addRental(createRentalFor(3, Movie::CHILDRENS));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t1.5\n")
        + string("Amount owed is 1.5\n")
        + string("You earned 1 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForNewReleaseMovieRentalMoreThan1Day)
{
    customer.addRental(createRentalFor(2, Movie::NEW_RELEASE));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t6.0\n")
        + string("Amount owed is 6.0\n")
        + string("You earned 2 frequent renter points"));
}

TEST_F(CustomerFixture, StatementForFewMovieRental)
{
    Movie regularMovie = Movie(TITLE, Movie::REGULAR);
    Movie newReleaseMovie = Movie(TITLE, Movie::NEW_RELEASE);
    Movie childrensMovie = Movie(TITLE, Movie::CHILDRENS);
    customer.addRental(Rental(regularMovie, 1));
    customer.addRental(Rental(newReleaseMovie, 4));
    customer.addRental(Rental(childrensMovie, 4));

    EXPECT_EQ(customer.statement(),
        string("Rental Record for NAME_NOT_IMPORTANT\n")
        + string("\tTITLE_NOT_IMPORTANT\t2.0\n")
        + string("\tTITLE_NOT_IMPORTANT\t12.0\n")
        + string("\tTITLE_NOT_IMPORTANT\t3.0\n")
        + string("Amount owed is 17.0\n")
        + string("You earned 4 frequent renter points"));
}