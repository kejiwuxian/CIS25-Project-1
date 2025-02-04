#include <iostream>
#include <iomanip>

#ifdef _WIN32 // Windows MSVC
#include <windows.h>
#define popen _popen
#define pclose _pclose
#else // Linux, MacOS
#include <stdio.h>
#endif

using namespace std;

string make_http_request(const string& url) {
	// Make http request by executing curl command
	FILE* pipe = popen(("curl -s \"" + url + "\"").c_str(), "r");
    char* buf = static_cast<char*>(malloc(1024));
    string res;

	if (!pipe)
	{
		return "Error: Failed to execute curl command";
	}
	if (!buf)
	{
		return "Error: Failed to allocate memory";
	}

    while (fgets(buf, 1024, pipe) != nullptr) res += buf;

    pclose(pipe);
    return res;
}

const string exchange_api_base = "https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/";

string get_supported_currencies()
{
	return make_http_request(exchange_api_base + "currencies.min.json");
}

void print_supported_currencies(const string supported_currencies)
{
	size_t i = supported_currencies.find("\"");
	while (i >= 0 && i < supported_currencies.length())
	{
		size_t sep = supported_currencies.find(":", i);
		cout << left << setw(8) << supported_currencies.substr(i + 1, sep - i - 2);
		i = supported_currencies.find("\"", sep + 2);
		cout << supported_currencies.substr(sep + 2, i - sep - 2) << endl;
		i += 2;
	}
}

bool is_currency_supported(const string currency, const string supported_currencies)
{
	return supported_currencies.find("\"" + currency + "\":") >= 0;
}

double get_exchange_rate(const string from, const string to)
{
	string res = make_http_request(exchange_api_base + "currencies/" + from + ".min.json");
	size_t s = res.find("\"" + to + "\":");
	s += to.length() + 3;
	size_t e = res.find(",", s);
	return atof(res.substr(s, e - s).c_str());
}

enum units
{
	oz = 0,
	lb,
	kg,
	g
};

const double units_conversion_table[4][4] =
{
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0}
};

double convertUnits(double weight, units unit_from, units unit_to)
{
	return weight * units_conversion_table[unit_from][unit_to];
}

double calculateUnitPrice(double weight, double price, double exchange_rate)
{
	return price / weight * exchange_rate;
}

int main()
{
	string currencies = get_supported_currencies();

	print_supported_currencies(currencies);

	cout << boolalpha << is_currency_supported("cny", currencies) << endl;

	cout << get_exchange_rate("usd", "cny") << endl;

	return 0;
}
