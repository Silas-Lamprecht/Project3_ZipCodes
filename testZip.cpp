#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <limits> 
#include <vector>
#include "Zipcode.h"

using namespace std;

/**
 * @brief Reads data from a CSV file containing zip code information.
 * 
 * @param filename The name of the file to read.
 * @return vector<Zipcode> A vector containing Zipcode objects read from the file.
 */
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

/**
 * @brief Comparator function to sort Zipcode objects by state.
 * 
 * @param a First Zipcode object to compare.
 * @param b Second Zipcode object to compare.
 * @return bool True if the state of 'a' is less than the state of 'b', false otherwise.
 */
bool compareByState(const Zipcode& a, const Zipcode& b) {
    return std::string(a.getState()) < std::string(b.getState());
}

/**
 * @brief Finds the extreme coordinates (longitude and latitude) for each state.
 * 
 * @param zipcodes Vector of Zipcode objects.
 * @return map<string, pair<pair<string, string>, pair<string, string> > > Map containing extreme coordinates for each state.
 */
map<string, pair<pair<string, string>, pair<string, string> > > findExtremeCoordinates(const vector<Zipcode>& zipcodes) {
    map<string, pair<pair<string, string>, pair<string, string> > > extremeCoordinates; // Map to store extreme coordinates for each state

    for (size_t i = 0; i < zipcodes.size(); ++i) {
        const string& currentState = zipcodes[i].getState();

        if (extremeCoordinates.find(currentState) == extremeCoordinates.end()) {
            extremeCoordinates[currentState] = make_pair(make_pair("", ""), make_pair("", ""));
        }


        pair<pair<string, string>, pair<string, string> >& stateCoords = extremeCoordinates[currentState];
        if (stateCoords.first.first.empty() || zipcodes[i].getLongitude() < stateCoords.first.first) {
            stateCoords.first.first = zipcodes[i].getZip();
        }
        if (stateCoords.second.first.empty() || zipcodes[i].getLongitude() > stateCoords.second.first) {
            stateCoords.second.first = zipcodes[i].getZip();
        }
        if (stateCoords.first.second.empty() || zipcodes[i].getLatitude() < stateCoords.first.second) {
            stateCoords.first.second = zipcodes[i].getZip();
        }
        if (stateCoords.second.second.empty() || zipcodes[i].getLatitude() > stateCoords.second.second) {
            stateCoords.second.second = zipcodes[i].getZip();
        }
    }

    return extremeCoordinates;
}

/**
 * @brief Main function to read data from file, find extreme coordinates, and output in table format.
 * 
 * @return int Exit status.
 */
int main() {
    // Read data from file
    vector<Zipcode> zipcodes = readDataFromFile("us_postal_codes.csv");

    // Sort zipcodes by state
	std::sort(zipcodes.begin(), zipcodes.end(), compareByState);

    // Find extreme coordinates for each state
	map<string, pair<pair<string, string>, pair<string, string> > > extremeCoords = findExtremeCoordinates(zipcodes);


	map<string, pair<pair<string, string>, pair<string, string> > >::const_iterator it = extremeCoords.begin();


	++it; // Skip the first element
	
	// Output table header
	cout << "State"
         << setw(20) << "Easternmost Zipcode"
         << setw(20) << "Westernmost Zipcode"
         << setw(20) << "Southernmost Zipcode"
         << setw(20) << "Northernmost Zipcode" << endl;

	// Output extreme coordinates for each state
	for (; it != extremeCoords.end(); ++it) {
		if(it->first == "CouLat") // Skip placeholder state
			++it;
		cout << left << setw(20) << it->first
             << setw(20) << it->second.first.first
             << setw(20) << it->second.second.first
             << setw(20) << it->second.first.second
             << setw(20) << it->second.second.second << endl;
	}
	return 0;
}
