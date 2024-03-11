//
// Created by silas on 3/9/2024.
//

#include "zipCodeBuffer.h"
void zipCodeBuffer::readFile() {
    // Open the file
    std::ifstream file;
    file.open((R"(C:\Users\silas\CLionProjects\untitled\us_postal_codes.csv)"));
    // Check if the file is opened successfully
    /*
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        //return 1;
    }
    */
    // Read the file line by line
    std::string line;
    int count = 1;
    while (std::getline(file, line)) {
        // Process the line here

        zipCodeRecord newRecord;
        std::stringstream ss(line);
        std::string zipSubstring;
        std::string nameSubString;
        std::string stateSubString;
        std::string countySubString;
        std::string latSubString;
        std::string longSubString;
        getline(ss, zipSubstring, ',');
        getline(ss,nameSubString, ',');
        getline(ss,stateSubString, ',');
        getline(ss,countySubString, ',');
        getline(ss,latSubString, ',');
        getline(ss,longSubString, ',');

        try{
            newRecord.zip = stoi(zipSubstring);
            //std::cout << newRecord.zip << std::endl;
        }

        catch (const std::invalid_argument& e) {
            std::cerr << "Error" << std::endl;
        };

        newRecord.name = nameSubString;
        newRecord.stateName = stateSubString;
        newRecord.county = countySubString;
        newRecord.latitude = stod(latSubString);
        newRecord.longitude = stod(longSubString);
        zipCodeBuffer::zipList.push_back(newRecord);
    }
    for (size_t i = 0; i < zipList.size(); i++){
        //std::cout << "entered" << std::endl;
        std::cout << zipList[i].zip << std::endl;
        std::cout << zipList[i].name << std::endl;
        std::cout << zipList[i].stateName<< std::endl;
        std::cout << zipList[i].county << std::endl;
        std::cout << zipList[i].latitude << std::endl;
        std::cout << zipList[i].longitude << std::endl;
    }
    // Close the file
    file.close();

    //return 0;
}