#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <limits> 
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

map<string, pair<pair<string, string>, pair<string, string> > > findExtremeCoordinates(const vector<Zipcode>& zipcodes) {
    map<string, pair<pair<string, string>, pair<string, string> > > extremeCoordinates; // Map to store extreme coordinates for each state

    // Iterate through the zipcodes
    for (size_t i = 0; i < zipcodes.size(); ++i) {
        const string& currentState = zipcodes[i].getState();

        // If the state is not already present in the map, initialize its extreme coordinates
        if (extremeCoordinates.find(currentState) == extremeCoordinates.end()) {
            extremeCoordinates[currentState] = make_pair(make_pair("", ""), make_pair("", ""));
        }

        // Update the extreme coordinates if necessary
        pair<pair<string, string>, pair<string, string> >& stateCoords = extremeCoordinates[currentState];
        if (stateCoords.first.first.empty() || zipcodes[i].getLongitude() < stateCoords.first.first) {
            stateCoords.first.first = zipcodes[i].getLongitude();
        }
        if (stateCoords.second.first.empty() || zipcodes[i].getLongitude() > stateCoords.second.first) {
            stateCoords.second.first = zipcodes[i].getLongitude();
        }
        if (stateCoords.first.second.empty() || zipcodes[i].getLatitude() < stateCoords.first.second) {
            stateCoords.first.second = zipcodes[i].getLatitude();
        }
        if (stateCoords.second.second.empty() || zipcodes[i].getLatitude() > stateCoords.second.second) {
            stateCoords.second.second = zipcodes[i].getLatitude();
        }
    }

    return extremeCoordinates;
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
	map<string, pair<pair<string, string>, pair<string, string> > > extremeCoords = findExtremeCoordinates(zipcodes);

// Output the extreme coordinates for each state
	for (map<string, pair<pair<string, string>, pair<string, string> > >::const_iterator it = extremeCoords.begin(); it != extremeCoords.end(); ++it) {
		cout << "State: " << it->first << endl;
		cout << "Least Longitude: " << it->second.first.first << ", Greatest Longitude: " << it->second.second.first << endl;
		cout << "Least Latitude: " << it->second.first.second << ", Greatest Latitude: " << it->second.second.second << endl;
		cout << endl;
	}
	printZipcodes(zipcodes);
    return 0;

}
