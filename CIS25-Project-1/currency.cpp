#include <iostream>
#include <iomanip>
#include <string>	// For getline

#include <stdexcept>// For runtime_error

#include "currency.hpp"
#include "util.hpp"

using namespace std;

namespace currency
{
	vector<string> currency_names;

	vector<string> currency_descriptions;

	vector<string>& get_currencies()
	{
		string res = util::make_http_request(exchange_api_base + "currencies.min.json");

		if (res.length() == 0)
			throw runtime_error("Error: Failed to fetch currencies, please check your internet connection");

		currency_names.clear();
		currency_descriptions.clear();

		size_t i = res.find("\"");
		while (i >= 0 && i < res.length())
		{
			size_t sep = res.find(":", i);
			currency_names.push_back(res.substr(i + 1, sep - i - 2));
			i = res.find("\"", sep + 2);
			currency_descriptions.push_back(res.substr(sep + 2, i - sep - 2));
			i += 2;
		}

		return currency_names;
	}

	void print_currencies()
	{
		cout << "Supported currencies:" << endl;
		size_t count = currency_names.size();
		for (size_t i = 0;i < count;i++)
		{
			cout << "\t" << left << setw(8) << currency_names[i];
			cout << currency_descriptions[i] << endl;
		}
		cout << endl;
	}

	void print_currency_names()
	{
		cout << "Supported currencies:" << endl;
		int i = 0;
		for (string name : currency_names)
		{
			cout << left << setw(8) << name;
			if (++i % 15 == 0)cout << endl;
		}
		cout << endl;
	}

	bool is_supported_currency(const string currency)
	{
		for (string name : currency_names)
			if (currency == name) return true;
		return false;
	}

	double get_exchange_rate(const string from, const string to)
	{
		string res = util::make_http_request(exchange_api_base + "currencies/" + from + ".min.json");

		if (res.length() == 0)
			throw runtime_error("Error: Failed to fetch exchange rate, please check your internet connection");

		size_t s = res.find("\"" + to + "\":");
		s += to.length() + 3;
		size_t e = res.find(",", s);
		return atof(res.substr(s, e - s).c_str());
	}

	double convert_currencies(const double value, const string from, const string to)
	{
		return value * get_exchange_rate(from, to);
	}

	string input_currency(const string prompt)
	{
		string input;
		do
		{
			util::clear_console();
			print_currency_names();
			cout << prompt;
			getline(cin, input);
			util::to_lower(input);
		} while (!is_supported_currency(input));
		return input;
	}
}
