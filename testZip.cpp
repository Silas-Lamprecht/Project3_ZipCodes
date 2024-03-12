#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Zipcode.h"

using namespace std;

vector<Zipcode> readDataFromFile(const string& filename) {
    vector<Zipcode> zipcodes;
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return zipcodes;
    }
	
	DelimFieldBuffer buffer;
    Zipcode::InitBuffer(buffer);
	
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string zip, place, state, county, latitude, longitude;
        getline(ss, zip, ',');
        getline(ss, place, ',');
        getline(ss, state, ',');
        getline(ss, county, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        Zipcode zipcode;
        zipcode.setZip(zip.c_str());
        zipcode.setPlace(place.c_str());
        zipcode.setState(state.c_str());
        zipcode.setCounty(county.c_str());
        zipcode.setLatitude(latitude.c_str());
        zipcode.setLongitude(longitude.c_str());
		
		zipcode.Pack(buffer);
        zipcodes.push_back(zipcode);
    }
    file.close();
    return zipcodes;
}

bool compareByState(const Zipcode& a, const Zipcode& b) {
    return std::string(a.getState()) < std::string(b.getState());
}


void printZipcodes(const vector<Zipcode>& zipcodes) {
    // Initialize iterator to the beginning of the vector
    vector<Zipcode>::const_iterator it = zipcodes.begin();
    
    // Iterate over the vector until the end is reached
    while (it != zipcodes.end()) {
        const Zipcode& zipcode = *it; // Dereference iterator to access Zipcode object
        
        // Print Zipcode information
        cout << "Zip: " << zipcode.getZip() << ", Place: " << zipcode.getPlace() << ", State: " << zipcode.getState() << ", County: " << zipcode.getCounty() << ", Latitude: " << zipcode.getLatitude() << ", Longitude: " << zipcode.getLongitude() << endl;
        
        // Move iterator to the next element
        ++it;
    }
}

int main() {
    vector<Zipcode> zipcodes = readDataFromFile("us_postal_codes.csv");
    // Call printZipcodes function to print Zipcode information
	std::sort(zipcodes.begin(), zipcodes.end(), compareByState);
    printZipcodes(zipcodes);
    return 0;
}
