#pragma once

#include <vector>

namespace currency
{
	// Base url for the exchange API
	const std::string exchange_api_base = "https://latest.currency-api.pages.dev/v1/";

	// A list of names for the supported currencies
	extern std::vector<std::string> currency_names;

	// A list of descriptions for the supported currencies
	extern std::vector<std::string> currency_descriptions;

	// Get all supported currencies and initialize currency_names and currency_descriptions
	std::vector<std::string>& get_currencies();

	// Print all supported currencies
	void print_currencies();

	// Print all names of supported currencies
	void print_currency_names();

	// Check if the currency is supported
	bool is_supported_currency(const std::string currency);

	// Get the exchange rate between two currencies
	double get_exchange_rate(const std::string from, const std::string to);

	// Convert one currency to another
	double convert_currencies(const double value, const std::string from, const std::string to);

	// Input a currency, retry until a valid currency is inputted
	std::string input_currency(const std::string prompt);
}
