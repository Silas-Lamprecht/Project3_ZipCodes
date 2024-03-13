#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
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
    map<string, pair<pair<string, string>, pair<string, string> > > extremeCoordinates;

    for (size_t i = 0; i < zipcodes.size(); ++i) {
        const string& currentState = zipcodes[i].getState();

        if (extremeCoordinates.find(currentState) == extremeCoordinates.end()) {
            extremeCoordinates[currentState] = make_pair(make_pair("", ""), make_pair("", ""));
        }

        pair<pair<string, string>, pair<string, string> >& stateCoords = extremeCoordinates[currentState];
        if (stateCoords.first.first.empty() || zipcodes[i].getLongitude() < stateCoords.first.first) {
            stateCoords.first.first = zipcodes[i].getPlace();
        }
        if (stateCoords.second.first.empty() || zipcodes[i].getLongitude() > stateCoords.second.first) {
            stateCoords.second.first = zipcodes[i].getPlace();
        }
        if (stateCoords.first.second.empty() || zipcodes[i].getLatitude() < stateCoords.first.second) {
            stateCoords.first.second = zipcodes[i].getPlace();
        }
        if (stateCoords.second.second.empty() || zipcodes[i].getLatitude() > stateCoords.second.second) {
            stateCoords.second.second = zipcodes[i].getPlace();
        }
    }

    return extremeCoordinates;
}

int main() {
    vector<Zipcode> zipcodes = readDataFromFile("us_postal_codes.csv");
	std::sort(zipcodes.begin(), zipcodes.end(), compareByState);
	map<string, pair<pair<string, string>, pair<string, string> > > extremeCoords = findExtremeCoordinates(zipcodes);

	map<string, pair<pair<string, string>, pair<string, string> > >::const_iterator it = extremeCoords.begin();

	++it;
	cout << "State"
     << setw(20) << "Easternmost Place"
     << setw(20) << "Westernmost Place"
     << setw(20) << "Southernmost Place"
     << setw(20) << "Northernmost Place" << endl;

	for (; it != extremeCoords.end(); ++it) {
		if(it->first == "CouLat")
			++it;
		cout << left << setw(20) << it->first
         << setw(20) << it->second.first.first
         << setw(20) << it->second.second.first
         << setw(20) << it->second.first.second
         << setw(20) << it->second.second.second << endl;
	}

}
