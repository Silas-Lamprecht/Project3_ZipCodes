//
// Created by silas on 3/11/2024.
//

#ifndef UNTITLED_STATEEXTREMESORT_H
#define UNTITLED_STATEEXTREMESORT_H
#include "zipCodeBuffer.h"

class stateExtremeSort {
public:
    struct coordinates {
        double latitude;
        double longitude;
    };
    struct state{
        std::string name;
        double easternmost = 0;
        double westernmost = 0;
        double northernmost = 0;
        double southernmost = 0;
        static bool compareByName(const state& a, const state& b){
            return a.name < b.name;
        }
    };
    void updateExtremities(const coordinates& current, state& currentState);
    void findExtremiries();
    std::vector<state> states;
    bool hasSameName(const std::vector<state>& vec, const std::string& name);
};


#endif //UNTITLED_STATEEXTREMESORT_H
