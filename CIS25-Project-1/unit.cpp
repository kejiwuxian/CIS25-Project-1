#include <iostream>
#include <iomanip>
#include <string>	// For getline

#include "unit.hpp"
#include "util.hpp"

using namespace std;

namespace unit
{
	void print_units(const string* unit_names, const string* unit_descriptions)
	{
		for (int i = 0;i < 5;i++)
			cout << "\t" << left << setw(8) << unit_names[i] << unit_descriptions[i] << endl;
	}

	void print_weight_units()
	{
		cout << "Supported weight units:" << endl;
		print_units(weight_unit_names, weight_unit_descriptions);
		cout << endl;
	}

	void print_volume_units()
	{
		cout << "Supported volume units:" << endl;
		print_units(volume_unit_names, volume_unit_descriptions);
		cout << endl;
	}

	double convert_units(const double value, const weight from, const weight to)
	{
		return value * weight_units_rate_table[from][to];
	}

	double convert_units(const double value, const volume from, const volume to)
	{
		return value * volume_units_rate_table[from][to];
	}

	bool input_unit(const std::string prompt, int& unit)
	{
		while (true)
		{
			util::clear_console();
			print_weight_units();
			print_volume_units();
			string input;
			cout << prompt;
			getline(cin, input);
			util::to_lower(input);
			for (int i = 0;i < 5;i++)
			{
				if (input == weight_unit_names[i])
				{
					unit = i;
					return true;
				}
				if (input == volume_unit_names[i])
				{
					unit = i;
					return false;
				}
			}
		}
	}

	weight input_weight_unit(const std::string prompt)
	{
		while (true)
		{
			util::clear_console();
			print_weight_units();
			string input;
			cout << prompt;
			getline(cin, input);
			util::to_lower(input);
			for (int i = 0;i < 5;i++)
				if (input == weight_unit_names[i])
					return static_cast<weight>(i);
		}
	}

	volume input_volume_unit(const std::string prompt)
	{
		while (true)
		{
			util::clear_console();
			print_volume_units();
			string input;
			cout << prompt;
			getline(cin, input);
			util::to_lower(input);
			for (int i = 0;i < 5;i++)
				if (input == volume_unit_names[i])
					return static_cast<volume>(i);
		}
	}
}
