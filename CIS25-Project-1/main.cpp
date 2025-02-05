#include <iostream>
#include <iomanip>
#include <string>	// For getline

#include "currency.hpp"
#include "unit.hpp"
#include "util.hpp"

using namespace std;

double calculate_unit_price(double value, double price, double exchange_rate)
{
	return price / value * exchange_rate;
}

int main()
{
	try
	{
		currency::get_currencies();

		//currency::print_currencies();

		//unit::print_weight_units();
		//unit::print_volume_units();

		//cout << boolalpha << currency::is_supported_currency("cny") << endl;

		//cout << currency::get_exchange_rate("usd", "cny") << endl;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	cout << currency::input_currency("Please enter the target currency: ") << endl;

	int unit;

	if (unit::input_unit("Please enter the target unit: ", unit))
	{
		cout << "Weight unit: " << unit::weight_unit_names[unit] << endl;
	}
	else
	{
		cout << "Volume unit: " << unit::volume_unit_names[unit] << endl;
	}

	while (true)
	{
		string input;
		util::clear_console();
		cout << "Main Menu:" << endl;
		getline(cin, input);
		util::to_lower(input);

		if (input.length() == 1)
		{
			break;
		}
	}

	return 0;
}
