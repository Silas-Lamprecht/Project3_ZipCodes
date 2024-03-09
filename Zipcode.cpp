#include "Zipcode.h"

/*!
 * \file Zipcode.cpp
 * \brief Implementation file for the Zipcode class
 */

/*!
 * \brief Default constructor for the Zipcode class.
 * Initializes the Zipcode object by calling the Clear() method.
 */
Zipcode::Zipcode() {
    Clear();
}

/*!
 * \brief Clears all fields of the Zipcode object.
 */
void Zipcode::Clear() {
    // Set each field to an empty string or 0
    zip[0] = 0;
    place[0] = 0;
    state[0] = 0;
    county[0] = 0;
    latitude[0] = 0;
    longitude[0] = 0;
}

/*!
 * \brief Packs the fields of the Zipcode object into the provided buffer.
 * \param Buffer The IOBuffer to pack the fields into.
 * \return TRUE if packing succeeds, FALSE otherwise.
 */
int Zipcode::Pack(IOBuffer& Buffer) const {
    int numBytes;
    Buffer.Clear();
    numBytes = Buffer.Pack(zip);
    if (numBytes == -1) return FALSE;
    numBytes = Buffer.Pack(place);
    if (numBytes == -1) return FALSE;
    numBytes = Buffer.Pack(state);
    if (numBytes == -1) return FALSE;
    numBytes = Buffer.Pack(county);
    if (numBytes == -1) return FALSE;
    numBytes = Buffer.Pack(latitude);
    if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(longitude);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

/*!
 * \brief Unpacks the fields of the Zipcode object from the provided buffer.
 * \param Buffer The IOBuffer to unpack the fields from.
 * \return TRUE if unpacking succeeds, FALSE otherwise.
 */
int Zipcode::Unpack(IOBuffer& Buffer) {
    Clear();
    int numBytes;
    numBytes = Buffer.Unpack(zip);
    if (numBytes == -1) return FALSE;
    zip[numBytes] = 0;
    numBytes = Buffer.Unpack(place);
    if (numBytes == -1) return FALSE;
    place[numBytes] = 0;
    numBytes = Buffer.Unpack(county);
    if (numBytes == -1) return FALSE;
    county[numBytes] = 0;
    numBytes = Buffer.Unpack(latitude);
    if (numBytes == -1) return FALSE;
    latitude[numBytes] = 0;
    numBytes = Buffer.Unpack(longitude);
    if (numBytes == -1) return FALSE;
    longitude[numBytes] = 0;
    return TRUE;
}

/*!
 * \brief Initializes a FixedFieldBuffer to be used for packing Zipcode objects.
 * \param Buffer The FixedFieldBuffer to initialize.
 * \return TRUE if initialization succeeds, FALSE otherwise.
 */
int Zipcode::InitBuffer(FixedFieldBuffer& Buffer) {
    int result;
    result = Buffer.AddField(5);
    result = result && Buffer.AddField(23);
    result = result && Buffer.AddField(2);
    result = result && Buffer.AddField(15);
    result = result && Buffer.AddField(9);
    result = result && Buffer.AddField(9);
    return result;
}

/*!
 * \brief Initializes a DelimFieldBuffer to be used for packing Zipcode objects.
 * \param Buffer The DelimFieldBuffer to initialize.
 * \return TRUE if initialization succeeds, FALSE otherwise.
 */
int Zipcode::InitBuffer(DelimFieldBuffer& Buffer) {
    return TRUE;
}

/*!
 * \brief Initializes a LengthFieldBuffer to be used for packing Zipcode objects.
 * \param Buffer The LengthFieldBuffer to initialize.
 * \return TRUE if initialization succeeds, FALSE otherwise.
 */
int Zipcode::InitBuffer(LengthFieldBuffer& Buffer) {
    return TRUE;
}

/*!
 * \brief Prints the zipcode information to the specified output stream.
 * \param stream The output stream to which the zipcode information will be printed.
 * \param label Optional label to prepend to the output. Defaults to nullptr.
 */
void Zipcode::Print(ostream& stream, char* label) const {
    if (label == 0) stream<< "Zipcode:";
    else stream << label;
    stream << "\n\t zip '" << zip << "'\n"
        << "\tplace '" << place << "'\n"
        << "\t   state '" << state << "'\n"
        << "\tcounty '" << county << "'\n"
        << "\tlongitude '" << longitude << "'\n"
		<< "\tlatitude '" << latitude << "'\n";
}