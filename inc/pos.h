/**
 * @file pos.h
 * @author Dan 0xSavD
 * @brief Point of Sale (pos) header file for the entire class and methods
 * related to the pos system of the super market.
 * @version 1.0
 * @date 2024-09-13
 */

#pragma once

#include <map>
#include <string>
#include <vector>

class Pos {
    public:
    Pos(int schema);
    ~Pos();
    void scanItem(std::string itemNumber);
    void removeItem(std::string itemNumber);
    void emptyCart();
    double getTodaysTotal();

    private:
    void initializeSchemaSettings();
    void adjustPricing();


    // Members
    int _schemaType;
    double _todaysTotal;
    std::map<std::string, double> _itemDatabase;
    std::vector<std::string> _itemsInCart;

 };