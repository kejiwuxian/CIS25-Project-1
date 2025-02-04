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
	// Make http request by executing curl command so I don't have to write sockets and link openssl for https
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

string get_currencies()
{
	return make_http_request(exchange_api_base + "currencies.min.json");
}

void print_currencies(const string currencies)
{
	size_t i = currencies.find("\"");
	while (i >= 0 && i < currencies.length())
	{
		size_t sep = currencies.find(":", i);
		cout << left << setw(8) << currencies.substr(i + 1, sep - i - 2);
		i = currencies.find("\"", sep + 2);
		cout << currencies.substr(sep + 2, i - sep - 2) << endl;
		i += 2;
	}
}

bool is_currency_supported(const string currency, const string currencies)
{
	return currencies.find("\"" + currency + "\":") >= 0;
}

double get_exchange_rate(const string from, const string to)
{
	string res = make_http_request(exchange_api_base + "currencies/" + from + ".min.json");
	size_t s = res.find("\"" + to + "\":");
	s += to.length() + 3;
	size_t e = res.find(",", s);
	return atof(res.substr(s, e - s).c_str());
}

const string weight_unit_names[] = { "oz","lb","kg","jin","g" };
const string volume_unit_names[] = { "floz","cup","gal","ml","l" };
const string weight_unit_descriptions[] = {
	"Ounce (US weight unit)",			// oz
	"Pound (US weight unit)",			// lb
	"Kilogram (metric weight unit)",	// kg
	"Jin (Chinese weight unit)",		// jin
	"Gram (metric weight unit)"			// g
};
const string volume_unit_descriptions[] = {
	"Fluid ounce (US volume unit)",		// floz
	"Cup (US volume unit)",				// cup
	"Gallon (US volume unit)",			// gal
	"Milliliter (metric volume unit)",	// ml
	"Liter (metric volume unit)"		// l
};

// With the help from DeepSeek R1
// Conversion rates for weight units (row unit to column unit)
const double weight_units_rate_table[5][5] = {
	// from: to: oz          lb           kg              jin            g
	/* oz   */ { 1.0,        0.0625,      0.028349523125, 0.05669904625, 28.349523125 },
	/* lb   */ { 16.0,       1.0,         0.45359237,     0.90718474,    453.59237 },
	/* kg   */ { 35.27396195,2.20462262,  1.0,            2.0,           1000.0 },
	/* jin  */ { 17.63698097,1.10231131,  0.5,            1.0,           500.0 },
	/* g    */ { 0.03527396, 0.002204622, 0.001,          0.002,         1.0 }
};
// Conversion rates for volume units (row unit to column unit)
const double volume_units_rate_table[5][5] = {
	// from: to: floz         cup         gal          ml           l
	/* floz */ { 1.0,         0.125,      0.0078125,   29.57352956, 0.02957352956 },
	/* cup  */ { 8.0,         1.0,        0.0625,      236.5882365, 0.2365882365 },
	/* gal  */ { 128.0,       16.0,       1.0,         3785.411784, 3.785411784 },
	/* ml   */ { 0.03381402,  0.00422675, 0.000264172, 1.0,         0.001 },
	/* l    */ { 33.8140227,  4.22675284, 0.264172052, 1000.0,      1.0 }
};

void print_units(const string* unit_names, const string* unit_descriptions)
{
	for (int i = 0;i < 5;i++)
		cout << left << setw(8) << unit_names[i] << unit_descriptions[i] << endl;
}

double convert_units(double value, int from, int to, const double *table[5])
{
	return value * table[from][to];
}

double calculate_unit_price(double value, double price, double exchange_rate)
{
	return price / value * exchange_rate;
}

int main()
{
	string currencies = get_currencies();

	print_currencies(currencies);

	cout << boolalpha << is_currency_supported("cny", currencies) << endl;

	cout << get_exchange_rate("usd", "cny") << endl;

	print_units(weight_unit_names, weight_unit_descriptions);
	print_units(volume_unit_names, volume_unit_descriptions);

	return 0;
}
