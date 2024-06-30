#pragma once
#include "Movie.cpp";

class Rental
{
public:
	Rental(Movie& movie, int days_rented)
		: movie(movie),
		daysRented(days_rented)
	{
	}

	int getDaysRented()
	{
		return daysRented;
	}

	Movie getMovie()
	{
		return movie;
	}

	double getCharge(void)
	{
		return getMovie().getChargeFor(getDaysRented());
	}

private:
	Movie movie;
	int daysRented;
};
