# define out /*
g++ -std=c++0x -rdynamic -Wall -s -O2 -o test $0 untyped.cpp; exit $?
# define out */
/*           UnTyped C++ (Version 0.1 - 2012/07)
    <https://github.com/peychart/Untyped-cpp>

    Copyright (C) 2012  -  peychart

    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this program.
    If not, see <http://www.gnu.org/licenses/>.

    Details of this licence are available online under:
                        http://www.gnu.org/licenses/gpl-3.0.html
*/
#include <fstream>
#include <sstream>
#include "untyped.h"

using namespace UnTyped;

int main() {
//	std::cout << "Error on declare: " << "(" << myType.errNo() << ") - " << myType.errString() << std::endl; break;
//	std::cout << "Error on create : " << "(" << myType.errNo() << ") - " << myType.errString() << std::endl; break;
//	std::cout << "Error on save   : " << "(" << myType.errNo() << ") - " << myType.errString() << std::endl; break;

//	std::list<std::string>	accessorList = {"%a", "%A", "%b", "%B", "%c", "%d", "%H", "%I", "%j", "%m", "%M", "%p", "%s", "%S", "%U", "%w", "%W", "%x", "%X", "%y", "%Y", "%Z"};
//	for( auto i: accessorList )
//		myType.setAccessor( i );


	std::ofstream		outfile("/tmp/serialize.db", std::ifstream::trunc|std::ifstream::binary);
	std::ifstream		infile ("/tmp/serialize.db", std::ofstream::binary);
	std::stringstream	myStream( std::stringstream::in | std::stringstream::out );
	untyped			mydata;

	// Types management:
	int		i = untyped( 96 ), j = untyped( 'a' );
	char		c = untyped( 'a' ), d = untyped( 98 );
	std::cout << "i = " << i << ", j = " << j << ", c = \"" << c << "\", d = \"" << d << "\"" <<std::endl;
	mydata.assign( "I am not upper case...");
	std::cout << mydata.c_str() << std::endl;

	char *pt = reinterpret_cast<char*>( (void*)mydata );
	for( size_t i=mydata.size(); i--; pt++ )
		*pt = toupper( *pt );
	std::cout << mydata.erase( mydata.indexOf( "NOT " ), 4 ).c_str() << std::endl;

	mydata.clear();
	// Multi-dimentional + serialization:
	mydata[""]   = "object_name";
	mydata["p1"] = "Property-1";
	mydata["p2"] = "Property-2";
	mydata["p3"] = "Property-3";
	mydata       = "Value-1";
	mydata[1]    = "Value-2";
	mydata[2]    = "Value-3";
	mydata[3]    = "Value-4";
	mydata[3][1] = "Value-4.1";
	mydata[3][2] = "Value-4.2";
	mydata[3][2][1]="Value-4.2.1";
	mydata[3][2][1][1]="Value-4.2.1.1";

	std::cout << std::endl << "Serialization:" << std::endl;
	std::cout << mydata.serialize( outfile ).serialize( myStream ) << std::endl;
	( untyped("This is a te") + "st..." ).serialize( outfile ).serialize( myStream );
	( untyped( 'B' )+ (char)('a' - 'A') ).serialize( outfile ).serialize( myStream );
	( untyped(2354) + 4 )( outfile ).serialize( myStream );
	( untyped(6.594) / 2.1 )( outfile ).serialize( myStream );
	( untyped(false) + true )( outfile )( *(std::ostream*)&myStream );

	std::cout << outfile.tellp() << " octets are serialized in file..." << std::endl;
	std::cout << myStream.tellp() << " octets are serialized in stream..." << std::endl;

	// Write in file:
	outfile.flush();
	myStream.flush();
	mydata.clear();

	// Data deserialization:
/*	mydata( infile );
	mydata( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata[3]( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata[3][2]( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata[3][2][1]( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata.deserialize( myStream );
	mydata( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata[3]( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata[3][2]( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
	mydata[3][2][1]( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );
*/
	std::cout << std::endl << "> Deserialization:" << std::endl;

	std::cout << "from file:" << std::endl;
	std::cout << mydata.deserialize( infile ) << std::endl;
	std::cout << untyped().deserialize( infile ) << std::endl;
	std::cout << untyped( infile ) << std::endl;
	std::cout << untyped( infile ) << std::endl;
	std::cout << untyped()( infile ) << std::endl;
	std::cout << infile.tellg() << " octets are deserialized from file..." << std::endl;
	std::cout << "mydata[3][2][1][1]=" << mydata[3][2][1][1] << std::endl;
	std::cout << "mydata[3]=" << mydata[3] << std::endl;
	std::cout << "mydata[\"p1\"]=" << mydata["p1"] << std::endl << std::endl;
	mydata.clear();

	std::cout << "from stream:" << std::endl;
	std::cout << mydata.deserialize( myStream ) << std::endl;
	std::cout << untyped().deserialize( myStream ) << std::endl;
	std::cout << untyped( myStream ) << std::endl;
	std::cout << untyped( myStream ) << std::endl;
	std::cout << untyped( myStream ) << std::endl;
	std::cout << myStream.tellg() << " octets are deserialized from stream..." << std::endl;
	std::cout << "mydata[3]=" << mydata[3] << std::endl;
	std::cout << "mydata[\"p3\"]=" << mydata["p3"] << std::endl << std::endl;
	mydata.clear();
/*
	// Plugins:
	mydata.clear();
	mydata["format"] = "%y/%m/%d-%H:%M:%S";
	mydata( "/usr/local/lib/libgdbm++_defaultActors.so", "getDate" );
	mydata( "/usr/local/lib/libgdbm++_actors.so", "objectDisplay" );

	mydata += 24*60*60;
	mydata( "/usr/local/lib/libgdbm++_defaultActors.so", "getDate" );
	std::cout << "Tomorrow = " << mydata["from-format"] << std::endl;
*/
	return 0;
}

// About the man on the moon, I cannot say anything, but on the basic language, it seems that it may have existed...
