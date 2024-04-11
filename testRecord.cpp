#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "recfile.h"
#include "Zipcode.h"

using namespace std;

// Function to create the primary key index and write it to a file
void createAndWriteIndex(const vector<Zipcode>& zipcodes) {
    FixedFieldBuffer buffer(7); // Assuming FixedFieldBuffer is used
    Zipcode::InitBuffer(buffer);

    // Open the index file for writing
    RecordFile<Zipcode> indexFile(buffer);
    if (!indexFile.Create("index.dat", ios::out)) {
        cerr << "Error: Unable to create index file." << endl;
        return;
    }

    // Write each Zipcode record to the index file
	for (size_t i = 0; i < zipcodes.size(); ++i) {
        const Zipcode& zipcode = zipcodes[i];
        if (!indexFile.Append(zipcode)) {
            cerr << "Error: Failed to append record to index file." << endl;
            indexFile.Close();
            return;
        }
    }

    // Close the index file
    indexFile.Close();
}
// Function to read the primary key index from the file into RAM
void readIndexFromFile(std::vector<Zipcode>& index) {
    std::ifstream infile("index.txt"); // Open the index file for reading
    if (!infile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(infile, line)) { // Read each line from the file
        Zipcode temp; // Create a temporary Zipcode object
        // Parse the line and set attributes of the Zipcode object accordingly
        // Example: If each line contains zip code, place, state, county, latitude, and longitude separated by spaces
        std::istringstream iss(line);
        std::string zip, place, state, county, latitude, longitude;
        if (iss >> zip >> place >> state >> county >> latitude >> longitude) {
            temp.setZip(zip.c_str());
            temp.setPlace(place.c_str());
            temp.setState(state.c_str());
            temp.setCounty(county.c_str());
            temp.setLatitude(latitude.c_str());
            temp.setLongitude(longitude.c_str());
            index.push_back(temp); // Add the Zipcode object to the index vector
        } else {
            std::cerr << "Error: Invalid format in file." << std::endl;
        }
    }

    infile.close(); // Close the file after reading
}

// Function to search for a Zip Code in the index
bool searchIndex(const std::string& zipCode, const std::vector<Zipcode>& index) {
    // Iterate through the index vector to find the matching zip code
    for (std::vector<Zipcode>::const_iterator it = index.begin(); it != index.end(); ++it) {
        const Zipcode& entry = *it;
        if (entry.getZip() == zipCode) { // Assuming getZip() method returns the zip code
            return true; // Zip code found
        }
    }
    return false; // Zip code not found
}

void displayZipCodeRecord(const Zipcode& zipcode) {
    // Display Zip Code record details
    std::cout << "Zip Code: " << zipcode.getZip() << std::endl;
    std::cout << "Place: " << zipcode.getPlace() << std::endl;
    std::cout << "State: " << zipcode.getState() << std::endl;
    std::cout << "County: " << zipcode.getCounty() << std::endl;
    std::cout << "Latitude: " << zipcode.getLatitude() << std::endl;
    std::cout << "Longitude: " << zipcode.getLongitude() << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " -Z<ZipCode1> -Z<ZipCode2> ..." << endl;
        return 1;
    }

    vector<string> zipCodesToSearch;
    vector<Zipcode> primaryKeyIndex;

    // Parse command line arguments to get Zip Codes to search
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg.substr(0, 2) == "-Z") {
            zipCodesToSearch.push_back(arg.substr(2));
        }
    }

    // Read primary key index from file into RAM
    readIndexFromFile(primaryKeyIndex);

    // Search for each Zip Code in the index
    for (std::vector<std::string>::const_iterator it = zipCodesToSearch.begin(); it != zipCodesToSearch.end(); ++it) {
		const std::string& zipCode = *it;
		if (searchIndex(zipCode, primaryKeyIndex)) {
			cout << "Zip Code " << zipCode << " found in index. Details:" << endl;
		}
		else {
        cout << "Zip Code " << zipCode << " not found in index." << endl;
		}
	}
    return 0;
}