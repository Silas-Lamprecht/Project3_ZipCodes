//
// Created by silas on 3/9/2024.
//

#ifndef UNTITLED_ZIPCODEBUFFER_H
#define UNTITLED_ZIPCODEBUFFER_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
class zipCodeBuffer {
public:
    struct zipCodeRecord{
        int zip;
        std::string name;
        std::string stateName;
        std::string county;
        double latitude;
        double longitude;
    };
    std::vector<zipCodeRecord> zipList;
    void readFile();

};


#endif //UNTITLED_ZIPCODEBUFFER_H
