#include <fstream>
#include <iomanip>
#include "iobuffer.h"
#include "buffile.h"
#include "fixfld.h"
#include "length.h"
#include "Zipcode.h" // Include the Zipcode class header file

using namespace std;

// Declare instances of the Zipcode class
Zipcode JohnAmes;
Zipcode AlanMason;
Zipcode GARiccardi;
Zipcode Padded;

/**
 * @brief Test the buffer with Zipcode objects.
 * 
 * @tparam IOB Type of IOBuffer
 * @param Buff IOBuffer object
 * @param myfile Filename for storing buffer contents
 */
template <class IOB>
void testBuffer(IOB& Buff, char* myfile) {
    Zipcode zipcode;
    int result;
    int recaddr1, recaddr2, recaddr3, recaddr4;

    // Test writing
    BufferFile TestOut(Buff);
    result = TestOut.Create(myfile, ios::out);
    cout << "create file " << result << endl;
    if (!result) {
        cout << "Unable to create file " << myfile << endl;
        return;
    }
    JohnAmes.Pack(Buff);
    recaddr1 = TestOut.Write();
    cout << "write at " << recaddr1 << endl;
    AlanMason.Pack(Buff);
    recaddr2 = TestOut.Write();
    cout << "write at " << recaddr2 << endl;
    GARiccardi.Pack(Buff);
    recaddr3 = TestOut.Write();
    cout << "write at " << recaddr3 << endl;
    GARiccardi.Pack(Buff);
    recaddr4 = TestOut.Write();
    cout << "write at " << recaddr4 << endl;
    TestOut.Close();

    // test reading
    BufferFile TestIn(Buff);
    TestIn.Open(myfile, ios::in);
    TestIn.Read(recaddr3);
    zipcode.Unpack(Buff);
    zipcode.Print(cout);
    TestIn.Read(recaddr2);
    zipcode.Unpack(Buff);
    zipcode.Print(cout);
    TestIn.Read(recaddr1);
    zipcode.Unpack(Buff);
    zipcode.Print(cout);
    TestIn.Read(recaddr4);
    zipcode.Unpack(Buff);
    zipcode.Print(cout);
    result = TestIn.Read(recaddr4 * 2);
    if (result != -1)
        cout << "Read past end of file! Error." << endl;
    else
        cout << "Read past end of file failed! Correct." << endl;
}

/**
 * @brief Initialize Student objects.
 */
void InitZipcode() {
    cout << "Initializing 3 Zipcodes" << endl;
    JohnAmes.setZip("1234");
    JohnAmes.setPlace("John Valley (city)");
    JohnAmes.setState("MN");
    JohnAmes.setCounty("Maple");
    JohnAmes.setLatitude("46.3475");
    JohnAmes.setLongitude("-56.8675");
    JohnAmes.Print(cout);
    AlanMason.setZip("5875");
    AlanMason.setPlace("Mason Valley (city)");
	AlanMason.setState("NY");
	AlanMason.setCounty("AppleGril");
    AlanMason.setLatitude("98.7645");
    AlanMason.setLongitude("-23.1245");;
    AlanMason.Print(cout);
    GARiccardi.setZip("26542");
    GARiccardi.setPlace("Ilios");
    GARiccardi.setState("OH");
    GARiccardi.setCounty("YoutVille");
    GARiccardi.setLatitude("89.1295");
    GARiccardi.setLongitude("-87.8675");
    GARiccardi.Print(cout);
}

/**
 * @brief Test the FixedFieldBuffer.
 */
void testFixedField ()
{
    cout << "Testing Fixed Field Buffer" << endl;
    FixedFieldBuffer Buff (6);
    Zipcode::InitBuffer(Buff);
    char filename[] = "fixfile.dat";
    testBuffer(Buff, filename);
}

/**
 * @brief Test the LengthFieldBuffer.
 */
void testLength ()
{
    cout << "\nTesting LengthTextBuffer" << endl;
    LengthFieldBuffer Buff;
    Zipcode::InitBuffer(Buff);
    char filename[] = "lenfile.dat";
    testBuffer(Buff, filename);
}

/**
 * @brief Test the DelimFieldBuffer.
 */
void testDelim ()
{
    cout << "\nTesting DelimTextBuffer" << endl;
    DelimFieldBuffer::SetDefaultDelim('|');
    DelimFieldBuffer Buff;
    Zipcode::InitBuffer(Buff);
    char filename[] = "delfile.dat";
    testBuffer(Buff, filename);
}

/**
 * @brief Main function.
 */
int main(int argc, char** argv) {
    InitZipcode();
    testFixedField();
    testLength();
    testDelim();
}