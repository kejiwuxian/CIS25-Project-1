# CIS25 Project 1

This repository contains the source code for CIS25 Project 1.

Unit Price Calculator.  
A program that calculates a product's unit price in another weight unit and currency.  
It prompts users to enter the product's net weight, weight unit, price, currency, target weight unit, and target currency.  
It then fetches the current currency conversion rate from an API[^1] and calculates the unit price in the target weight unit and target currency.

Implement error checking to validate user inputs for net weight, weight unit, price, and currency.  
Ensure that inputs for weight units and currencies are valid and supported.  
If invalid data is entered, the program will prompt the user to correct the input.  
convert_units(weight, unit_from, unit_to): Converts the weight from one unit to another.  
calculate_unit_price(weight, price, conversion_rate): Calculates the unit price based on the converted weight and currency rate.  
Integrate a main loop that allows the user to perform multiple conversions during a single program run.  
After each conversion, the program will ask if the user wishes to perform another conversion.

[^1]: Free Currency Exchange Rates API [exchange-api](https://github.com/fawazahmed0/exchange-api).