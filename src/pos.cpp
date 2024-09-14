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

void Pos::removeItem(std::string itemNumber) {
    auto position = std::find(_itemsInCart.begin(), _itemsInCart.end(), itemNumber);
    if (position != _itemsInCart.end()) {
        _itemsInCart.erase(position);
    }
}

void Pos::emptyCart() {
    _itemsInCart.clear();
}

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

double Pos::getTodaysTotal() {
    adjustPricing();
    return _todaysTotal;
}

/**
 * @brief Before the total is shown call this function to adjust pricing
 * based on specific rules.
 * 
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