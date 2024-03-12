//
// Created by silas on 3/11/2024.
//

#include "stateExtremeSort.h"
// Function to compare coordinates and update the extremities
void stateExtremeSort::updateExtremities(const stateExtremeSort::coordinates& current, stateExtremeSort::state& currentState) {
    if (current.longitude < currentState.easternmost)
        currentState.easternmost = current.longitude;
    if (current.longitude > currentState.westernmost)
        currentState.westernmost = current.longitude;
    if (current.latitude > currentState.northernmost)
        currentState.northernmost = current.latitude;
    if (current.latitude < currentState.southernmost)
        currentState.southernmost = current.latitude;
};
bool stateExtremeSort::hasSameName(const std::vector<stateExtremeSort::state>& vec, const std::string& name) {
    for (const auto& item : vec) {
        if (item.name == name) {
            return true; // Found a match
        }
    }
    return false; // No match found
}

void stateExtremeSort::findExtremiries(){
    zipCodeBuffer Buffer;
    Buffer.readFile();
    for (size_t i = 0; i < Buffer.zipList.size(); i++){
        //std::cout << "entered" << std::endl;
        /*
        std::cout << Buffer.zipList[i].zip << std::endl;
        std::cout << zipList[i].name << std::endl;
        std::cout << zipList[i].stateName<< std::endl;
        std::cout << zipList[i].county << std::endl;
        std::cout << zipList[i].latitude << std::endl;
        std::cout << zipList[i].longitude << std::endl;
        */
        state currState;
        coordinates currCords{};
        currCords.latitude = Buffer.zipList[i].latitude;
        currCords.longitude = Buffer.zipList[i].longitude;
        if(!(stateExtremeSort::hasSameName(stateExtremeSort::states, Buffer.zipList[i].stateName))){
            currState.name = Buffer.zipList[i].stateName;
            currState.easternmost = Buffer.zipList[i].longitude;
            currState.westernmost = Buffer.zipList[i].longitude;
            currState.northernmost = Buffer.zipList[i].latitude;
            currState.southernmost = Buffer.zipList[i].latitude;
            /*
            std::cout << currState.name<< std::endl;
            std::cout << currState.easternmost << std::endl;
            std::cout << currState.westernmost << std::endl;
            std::cout << currState.northernmost << std::endl;
            std::cout << currState.southernmost << std::endl;
            */
            stateExtremeSort::states.push_back(currState);

        }
        else{
            std::string target = Buffer.zipList[i].stateName;
            for (auto& state : states) {
                if (state.name == target) {
                    /*
                    std::cout << "--Cords--" << std::endl;
                    std::cout << currCords.latitude << std::endl;
                    std::cout << currCords.longitude << std::endl;
                    std::cout << "State" << std::endl;
                    std::cout << state.name << std::endl;
                    std::cout << state.easternmost << std::endl;
                    std::cout << state.westernmost << std::endl;
                    std::cout << state.northernmost << std::endl;
                    std::cout << state.southernmost << std::endl;
                    std::cout << "---Changing" << std::endl;
                    */
                    updateExtremities(currCords,state);
                    /*
                    std::cout << state.name << std::endl;
                    std::cout << state.easternmost << std::endl;
                    std::cout << state.westernmost << std::endl;
                    std::cout << state.northernmost << std::endl;
                    std::cout << state.southernmost << std::endl;
                    std::cout << "Changed---" << std::endl;
                     */

                }
            }
        }
    }
    std::sort(states.begin(), states.end(), state::compareByName);
    /*
    for (size_t i = 0; i < stateExtremeSort::states.size(); i++){
        std::cout << states[i].name << std::endl;
    }
    */

}