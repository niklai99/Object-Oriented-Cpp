#include "EventReadFromFile.h"

#include "Event.h"

#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name.c_str(), ios::binary );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event
const Event* EventReadFromFile::readFile() {
	// variables to store data
	Event *ev;
	int n_ev=0;
	int n_p=0;
	double x=0;
	double y=0;
	double z=0;

	if( !(*file >> n_ev) ) return nullptr;

	// store event data
	*file >> x >> y >> z;
	ev=new Event(n_ev,x,y,z);

	*file >> n_p;
	// loop over particles and read momentums
	int i=0;
	int charge=0;
	float p_x=0;
	float p_y=0;
	float p_z=0;
	for(i=0; i < n_p; i++)
	{
		*file >> charge >> p_x >> p_y >> p_z;
		ev->add(charge, p_x, p_y, p_z);
	}

	return ev;

}

