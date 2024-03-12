/*
#include <iostream>
#include <map>
#include <limits>
#include <iomanip>
*/
#include <iomanip>
#include "stateExtremeSort.h"
// Structure to hold geographic coordinates

int main() {
    //generateTable("us_postal_codes.csv");
    stateExtremeSort stateSort;
    stateSort.findExtremiries();
    std::cout << std::left << std::setw(10) << "State" << std::setw(20) << "Easternmost" << std::setw(20) << "Westernmost" << std::setw(20) << "Northernmost" << std::setw(20) << "Southernmost" << std::endl;

    // Print table content
    for (const auto& state : stateSort.states) {
        std::cout << std::left << std::setw(10) << state.name << std::setw(20) << state.easternmost << std::setw(20) << state.westernmost << std::setw(20) << state.northernmost << std::setw(20) << state.southernmost << std::endl;
    }
    return 0;
}
