#include <fstream>
#include <iomanip>
#include <string.h>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "Zipcode.h"
#include "buffile.h"
#include "recfile.h"

using namespace std;

Zipcode zipcode1;
Zipcode zipcode2;

template <class IOB>
void testBuffer(IOB & Buff, const char* myfile) // Change the parameter type to const char*
{
    Zipcode zip; 
    int result; 
    int recaddr1, recaddr2;

    // Test writing
    RecordFile<Zipcode> TestOut(Buff);
    result = TestOut.Create(myfile, ios::out);
    cout << "create file "<<result<<endl;
    if (!result)
    {   
        cout << "Unable to create file "<<myfile<<endl; 
        return;
    }
        
    recaddr1 = TestOut.Write(zipcode1);
    cout << "write at "<<recaddr1<<endl;
    recaddr2 = TestOut.Write(zipcode2);
    cout << "write at "<<recaddr2<<endl;
    TestOut.Close();

    // test reading
    RecordFile<Zipcode> TestIn(Buff);
    TestIn.Open(myfile, ios::in);
    TestIn.Read(zip, recaddr1);
    zip.Print(cout, "First record:");
    TestIn.Read(zip, recaddr2);
    zip.Print(cout, "Second record:");
    result = TestIn.Read(zip, recaddr2*2);
    if (result != -1) 
        cout<<"Read past end of file! Error."<<endl;
    else 
        cout <<"Read past end of file failed! Correct."<<endl;
}


void InitZipcode()
{
	cout << "Initializing 3 Persons"<<endl;
	strcpy (zipcode1.length, "45");
	strcpy (zipcode1.zip, "54775");
	strcpy (zipcode1.place, "Maryton");
	strcpy (zipcode1.state, "MN");
	strcpy (zipcode1.county, "Stillwater");
	strcpy (zipcode1.latitude, "19.1002");
	strcpy (zipcode1.longitude, "-155.7258");
	zipcode1.Print (cout);
	strcpy (zipcode2.length, "64");
	strcpy (zipcode2.zip, "86542");
	strcpy (zipcode2.place, "Alantacia");
	strcpy (zipcode2.state, "OK");
	strcpy (zipcode2.county, "Hamilton");
	strcpy (zipcode2.latitude, "38.5816");
	strcpy (zipcode2.longitude, "-79.9754");
	zipcode2.Print (cout);
}

void testFixedField ()
{
	cout <<"Testing Fixed Field Buffer"<<endl;
	FixedFieldBuffer Buff(6);
	Zipcode::InitBuffer(Buff);
	testBuffer(Buff, "fixfile.dat");
}

void testLength ()
{
	cout << "\nTesting LengthTextBuffer"<<endl;
	LengthFieldBuffer Buff;
	Zipcode::InitBuffer(Buff);
	testBuffer(Buff, "lenfile.dat");
}

void testDelim ()
{
	cout << "\nTesting DelimTextBuffer"<<endl;
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer Buff;
	Zipcode::InitBuffer(Buff);
	testBuffer(Buff, "delfile.dat");
}

int main(int argc, char ** argv)
{
	InitZipcode();
	testFixedField();
	testLength();
	testDelim();
}
