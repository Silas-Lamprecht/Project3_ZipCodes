// Zipcode.h
#ifndef	ZIPCODE_H
#define ZIPCODE_H

#include <iostream>
#include "fixfld.h"
#include "length.h"
#include "delim.h"

using namespace std;

/*!
 * \brief Zipcode Information.
 */
class Zipcode 
{
  public:
  
	// fields
	char zip [6]; /*!< Zipcode identifier */
	char place [24]; /*!< Zipcode first name */
	char state [3]; /*!< Zipcode last name */
	char county [16]; /*!< Zipcode address */
	char latitude[10]; /*!< Zipcode enrollment date */
	char longitude [10]; /*!< Zipcode enrollment date */

	
	/*!
    * \brief Default constructor.
    */
	Zipcode();
	
	//operations
	/*!
    * \brief Gets the Zipcode identifier.
    * \return The Zipcode identifier.
    */
	const char* getZip() const { return zip; }
	
	/*!
    * \brief Getter methods of the Zipcode.
    * \return Info about the Zipcode.
    */
    const char* getPlace() const { return place; }
    const char* getState() const { return state; }
    const char* getCounty() const { return county; }
    const char* getLatitude() const { return latitude; }
	const char* getLongitude() const { return longitude; }

	/*!
    * \brief Setter methods of the Zipcode.
    * \param item it is setting.
    */
    void setZip(const char* z) { strcpy(zip, z); }
    void setPlace(const char* p) { strcpy(place, p); }
    void setState(const char* s) { strcpy(state, s); }
    void setCounty(const char* c) { strcpy(county, c); }
    void setLatitude(const char* lat) { strcpy(latitude, lat); }
	void setLongitude(const char* lon) { strcpy(longitude, lon); }
	
	/*!
    * \brief DelimFieldBuffer.
    * \param Buffer The DelimFieldBuffer to initialize.
    * \return 1 if successful, 0 otherwise.
    */
	static int InitBuffer (DelimFieldBuffer &);
	
	/*!
    * \brief LengthFieldBuffer.
    * \param Buffer The LengthFieldBuffer to initialize.
    * \return 1 if successful, 0 otherwise.
    */
	static int InitBuffer (LengthFieldBuffer &);
	
	/*!
    * \brief FixedFieldBuffer.
    * \param Buffer The FixedFieldBuffer to initialize.
    * \return 1 if successful, 0 otherwise.
    */
	static int InitBuffer (FixedFieldBuffer &);
	
	/*!
    * \brief Clears all data members of the Zipcode object.
    */
	void Clear ();
	
	/*!
    * \brief Unpacks the Zipcode object.
    * \param Buffer IOBuffer containing the packed Zipcode object.
    * \return 1 if successful, 0 otherwise.
    */
	int Unpack (IOBuffer &);
	
	/*!
    * \brief Packs the Zipcode object.
    * \param Buffer IOBuffer containing the packed Zipcode object.
    * \return 1 if successful, 0 otherwise.
    */
	int Pack (IOBuffer &) const;
	
	/*!
	* \brief Prints the Zipcode information to the output stream.
	* \param stream Output stream to which the Zipcode information will be printed.
	* \param label.
	*/
	void Print (ostream &, char * label=0) const;
};
#include "Zipcode.cpp"
#endif
