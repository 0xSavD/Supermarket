#include "pos.h"
#include <algorithm>
#include <iostream>
#include <string>

Pos::Pos(int schema)
: _schemaType(schema)
{
    initializeSchemaSettings();
}

Pos::~Pos()
{
}

/**
 * Scans an item and adds it to the cart.
 * 
 * @param itemNumber The number of the item to be scanned.
 * 
 * @remarks This function validates if the item is valid for the schema. If the item is valid, it is added to the cart and the total price is updated accordingly. If the item is not valid, an error message is displayed.
 */
void Pos::scanItem(std::string itemNumber) {
    // Validate item is valid for the schema
    if (_itemDatabase.find(itemNumber) != _itemDatabase.end()){
        _itemsInCart.push_back(itemNumber);
        std::sort(_itemsInCart.begin(), _itemsInCart.end());
        _todaysTotal += _itemDatabase.at(itemNumber) * 100;
    } else {
        std::cout << "Sorry this item can not be purchased today." << std::endl;
    }
}

/**
 * @brief Removes an item from the cart.
 * 
 * This function removes the item with the specified item number from the cart.
 * If the item is found in the cart, it is removed; otherwise, nothing happens.
 * 
 * @param itemNumber The item number of the item to be removed.
 */
void Pos::removeItem(std::string itemNumber) {
    auto position = std::find(_itemsInCart.begin(), _itemsInCart.end(), itemNumber);
    if (position != _itemsInCart.end()) {
        _itemsInCart.erase(position);
    }
}

/**
 * @brief Empties the cart by removing all items.
 */
void Pos::emptyCart() {
    _itemsInCart.clear();
}

/**
 * @brief Initializes the schema settings for the Point of Sale (POS) system.
 * 
 * This function is responsible for loading the item database based on the selected schema type.
 * 
 * @note The item database is a map where the keys are item codes and the values are item prices.
 * 
 */
void Pos::initializeSchemaSettings() {
    // Load the item database
    switch (_schemaType) {
        case 1: // Default schema
        _itemDatabase["1983"] = 1.99; // Toothbrush
        _itemDatabase["8873"] = 2.49; // Milk
        _itemDatabase["0923"] = 15.49 + 1.43; // Wine + tax
        _itemDatabase["6732"] = 2.49; // Chips
        _itemDatabase["4900"] = 3.49; // Salsa
        break;

        // case 2: alternate scehma
    }
}

/**
 * @brief Retrieves the total amount of sales for the current day.
 *
 * This method first adjusts the pricing for any discounts or promotions, and then returns the total amount of sales for the day.
 *
 * @return The total amount of sales for the current day.
 */
double Pos::getTodaysTotal() {
    adjustPricing();
    return _todaysTotal;
}

/**
 * @brief Adjusts the pricing based on the schema settings.
 * 
 * This function adjusts the pricing based on the schema settings.
 * 
 * @note This function is called before the total is calculated.
 */
void Pos::adjustPricing(){
    // Function references
    int totalToothBrushes = std::count(_itemsInCart.begin(), _itemsInCart.end(), "1983");
    int totalMilk = std::count(_itemsInCart.begin(), _itemsInCart.end(), "8873");
    int totalSalsa = std::count(_itemsInCart.begin(), _itemsInCart.end(), "4900");
    int totalWine = std::count(_itemsInCart.begin(), _itemsInCart.end(), "0923");
    int totalChips = std::count(_itemsInCart.begin(), _itemsInCart.end(), "6732");

    // Buy two get one free - Toothbrush
    {
        int toothbrush = totalToothBrushes;
        while (toothbrush != 0) {
            if (toothbrush % 3 == 0) {
                _todaysTotal -= _itemDatabase.at("1983") * 100;
            }
            toothbrush--;
        }

    }

    // Bundle deal
    {
        int chips = totalChips;
        int salsa = totalSalsa;
        while (chips > 0 && salsa > 0) {
            _todaysTotal -= _itemDatabase.at("6732") * 100;
            _todaysTotal -= _itemDatabase.at("4900") * 100;
            _todaysTotal += 4.99 * 100;
            chips--;
            salsa--;
        }
    }
}