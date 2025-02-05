#pragma once

namespace unit
{
	enum weight
	{
		oz = 0,
		lb,
		kg,
		jin,
		g
	};

	enum volume
	{
		floz = 0,
		cup,
		gal,
		ml,
		l
	};

	// A list of names for the weight units
	const std::string weight_unit_names[] = { "oz","lb","kg","jin","g" };

	// A list of names for the volume units
	const std::string volume_unit_names[] = { "floz","cup","gal","ml","l" };

	// A list of descriptions for the weight units
	const std::string weight_unit_descriptions[] = {
		"Ounce (US weight unit)",			// oz
		"Pound (US weight unit)",			// lb
		"Kilogram (metric weight unit)",	// kg
		"Jin (Chinese weight unit)",		// jin
		"Gram (metric weight unit)"			// g
	};

	// A list of descriptions for the volume units
	const std::string volume_unit_descriptions[] = {
		"Fluid ounce (US volume unit)",		// floz
		"Cup (US volume unit)",				// cup
		"Gallon (US volume unit)",			// gal
		"Milliliter (metric volume unit)",	// ml
		"Liter (metric volume unit)"		// l
	};

	// A table of conversion rates for weight units (With the help from DeepSeek R1)
	const double weight_units_rate_table[5][5] = {
		// from: to: oz          lb           kg              jin            g
		/* oz   */ { 1.0,        0.0625,      0.028349523125, 0.05669904625, 28.349523125 },
		/* lb   */ { 16.0,       1.0,         0.45359237,     0.90718474,    453.59237 },
		/* kg   */ { 35.27396195,2.20462262,  1.0,            2.0,           1000.0 },
		/* jin  */ { 17.63698097,1.10231131,  0.5,            1.0,           500.0 },
		/* g    */ { 0.03527396, 0.002204622, 0.001,          0.002,         1.0 }
	};

	// A table of conversion rates for volume units (With the help from DeepSeek R1)
	const double volume_units_rate_table[5][5] = {
		// from: to: floz         cup         gal          ml           l
		/* floz */ { 1.0,         0.125,      0.0078125,   29.57352956, 0.02957352956 },
		/* cup  */ { 8.0,         1.0,        0.0625,      236.5882365, 0.2365882365 },
		/* gal  */ { 128.0,       16.0,       1.0,         3785.411784, 3.785411784 },
		/* ml   */ { 0.03381402,  0.00422675, 0.000264172, 1.0,         0.001 },
		/* l    */ { 33.8140227,  4.22675284, 0.264172052, 1000.0,      1.0 }
	};

	// Print units
	void print_units(const std::string* unit_names, const std::string* unit_descriptions);

	// Print all supported weight units
	void print_weight_units();

	// Print all supported volume units
	void print_volume_units();

	// Convert one weight unit to another
	double convert_units(const double value, const weight from, const weight to);

	// Convert one volume unit to another
	double convert_units(const double value, const volume from, const volume to);

	// Input a unit, retry until a valid unit is inputted
	bool input_unit(const std::string prompt, int& unit);

	// Input a weight unit, retry until a valid weight unit is inputted
	weight input_weight_unit(const std::string prompt);

	// Input a volume unit, retry until a valid volume unit is inputted
	volume input_volume_unit(const std::string prompt);
}
