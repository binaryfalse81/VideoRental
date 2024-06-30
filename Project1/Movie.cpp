#pragma once
#include <string>

using namespace std;

class Movie
{
public:
	static const int CHILDRENS = 2;
	static const int NEW_RELEASE = 1;
	static const int REGULAR = 0;

	Movie(const string& title, int price_code)
		: title(title),
		priceCode(price_code)
	{
	}

	int getPriceCode()
	{
		return priceCode;
	}

	void setPriceCode(int price_code)
	{
		priceCode = price_code;
	}

	string getTitle()
	{
		return title;
	}

	double getChargeFor(int daysRented)
	{
		double thisAmount = 0;
		switch (getPriceCode())
		{
		case Movie::REGULAR:
			thisAmount = GetPrice(2, daysRented, 2, 1.5);
			break;
		case Movie::NEW_RELEASE:
			thisAmount = GetPrice(0, daysRented, 0, 3);
			break;
		case Movie::CHILDRENS:
			thisAmount = GetPrice(1.5, daysRented, 3, 1.5);
			break;
		}
		return thisAmount;
	}

	double GetPrice(double nBaseFee, int nDaysRented, int nDefaultRentDays, double nLateFeeMult)
	{
		double nPrice = 0;

		nPrice += nBaseFee;

		if (nDaysRented > nDefaultRentDays)
		{
			nPrice += (nDaysRented - nDefaultRentDays) * nLateFeeMult;
		}

		return nPrice;
	}

	int getFrequentRenterPonintsFor(int daysRented)
	{
		if (getPriceCode() == Movie::NEW_RELEASE && daysRented > 1)
		{
			return 2;
		}
		return 1;
	}
private:
	string title;
	int priceCode;
};
