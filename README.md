Javascript data in c++
=====================


Software:
---------

C++ source.

* Object that manages the standard types of c ++ in the std::vector and std::map structures.

Examples of use: serialization, json objects management, saving of memory contexts, manage configuration files, etc ... or, MQTT communications.

Here is a code that I wrote a few years ago, just for fun (and to learn c++) of an untyped object, standard C++ data container, now modified to handle serialization in format Json in my iot projects - this to replace the old libraries by manual reservation of memory spaces ... ;-)

Allows:

* use data similar to Javascript variables,
* binary (de)serialization in/from files or streams,
* json (de)serialization in/from files or streams,
* and, of course, a self-managed memory space (nothing more than a c++ flavor).


Below, examples of use (here, actual use -> https://github.com/peychart/WiFiPowerStrip/tree/master/Next-version):

	# define out /*
	g++ -std=c++0x -rdynamic -Wall -s -O2 -o test $0 untyped.cpp; exit $?
	# define out */
	# undef out
 
	#include "untyped.h"
	#include <list>		// if needed...
 
	int main() {			// ****** Intuitive syntax ******
 
	untyped	myJson('j');
	myJson.jsonMode();	// <-- JSON format management
 
	std::cout << myJson					<< std::endl;
	//-> 'j'		// <-- type char
 
	std::cout << ( myJson + 'A' - 'a' )			<< std::endl;
	//-> 'J'
 
	myJson = "aaaJaaa";
	std::cout << ( myJson + 's' + "on" - "aaa" - "aaa" )	<< std::endl;
	//-> "Json"		// <-- type string
 
	myJson.binaryMode();	// <-- BINARY format management
	std::cout << ( myJson + 's' + "on" - "aaa" - "aaa" )	<< std::endl;
	//-> Json		// <-- std::string
 
	myJson("								\
	{									\
	    \"name\":        \"Armstrong\",					\
	    \"firstname\":   \"Neil\",						\
	    \"birthday\":  { \"year\" : 1930, \"month\" : 8, \"day\": 5 },	\
	    \"profession\":[ \"pilot\", \"engineer\", \"astronaut\" ],		\
	    \"born in\":     \"Wapakoneta - Ohio\",				\
	    \"hobbies\": [							\
	        \"astronomy\",							\
	        \"X-15\",							\
	        \"First Man to Walk on the Moon\"				\
	    ]									\
	}									\
	");
	std::cout << myJson["birthday"]["year"] + 39 << std::endl;
	//-> 1969
 
 
				// ****** Implicit or explicit cast ******
 
	myJson = 31.4159e-1;		// <-- implicite double
	auto myDouble = myJson;
	std::cout << "myDouble   = " << myDouble		<< std::endl;
	//-> myDouble   = 3.14159	// <-- implicite double
 
	std::cout << "cast<float>= " << myDouble.value<float>()<< std::endl;
	//-> cast<float>= 3.14159	// <-- explicite float
 
	std::cout << "cast<int>  = " << myDouble.value<int>()	<< std::endl;
	//-> cast<int>  = 3		// <-- explicite int
 
	std::cout << "cast<bool> = " << myDouble.value<bool>()	<< std::endl;
	//-> cast<bool> = 1		// <-- explicite bool
	
 
 
			// ****** Automatic memory allocation, as close as needed ******
	myJson.clear();
	myJson[0]=10;
	myJson[1]=11;
	myJson[myJson.vector().size()]=12;
	myJson[myJson.vector().size()]=13;
 
	myJson.jsonMode();
	std::cout << myJson << std::endl;
	//-> [10,11,12,13]
 
	untyped tmp;
	tmp["array1"] = myJson;
	tmp["array2"] = myJson; tmp["array2"][3]=23;
	tmp["array3"] = myJson; tmp["array3"][2]=32;
	tmp["array4"] = myJson; tmp["array4"][1]=41;
	myJson = tmp; tmp.clear();
	std::cout << myJson << std::endl;
	//-> {"array1":[10,11,12,13],"array2":[10,11,12,23],"array3":[10,11,32,13],"array4":[10,41,12,13]}
 
	std::vector<std::string> myVector={ "s10","s11","s12","s13" };
	myJson = myVector;						// <-- From a std::vector...
	std::cout << myJson << std::endl;
	//-> ["s10","s11","s12","s13"]
 
	std::map<std::string,untyped> myMap={ {"myStr1",myVector}, {"myStr2",myVector}, {"myStr3",myVector} };
	myJson = myMap;							// <-- From a std::map...
	myJson += std::pair<std::string,untyped>{"myStr4",myVector};	// <-- From a std::pair...
	std::cout << myJson << std::endl;
	//-> {"myStr1":["s10","s11","s12","s13"],"myStr2":["s10","s11","s12","s13"],"myStr3":["s10","s11","s12","s13"],"myStr4":["s10","s11","s12","s13"]}

 
					// ****** Serialization ******
	myJson.clear();
	myJson["string"] = "abcdef";
	myJson["char"] = 'a';
	myJson["bool"] = true;
	myJson["int"] = 15;
	myJson["float"] = -3.14159;
	myJson["array"][3] = -13;
	myJson["array"][2] = -12;
	myJson["array"][1] = -11;
	myJson["array"][0] = -10;
	myJson["empty"] = untyped();
	std::cout << myJson << std::endl;
	//-> {"array":[-10,-11,-12,-13],"bool":true,"char":'a',"float":-3.14159,"empty":null,"int":15,"string":"abcdef"}
 
							// From a std::pair
	std::cout << untyped(std::pair<std::string,double>{"pi", 3.14159}).serializeJson() << std::endl;
	//-> {"pi":3.14159}
 
							// From a std::list, and others....
	myJson = std::list<int>{2,-1,-3,4};
	std::cout << myJson << std::endl << std::endl;
	//-> [2,-1,-3,4]
 
 
					// Deserialize from a std::stream:
 
	std::stringstream       myStream( std::stringstream::in | std::stringstream::out );

	myStream  << "{\"array\":[-10,-11,-12,-13], \"objectArray\" : [{\"o1\":false},{\"o2\":true} , {\"o3\":false}],\"bool\":true,\"char\":'a',\"double\":-3.14159,\"empty\":\"\",\"void\":null,\"int\":15,\"string\":\"abcdef\"}";
 
	std::cout << myJson.deserializeJson( myStream )  << std::endl;
	//-> {"array":[-10,-11,-12,-13],"bool":true,"char":'a',"double":-3.14159,"empty":"","int":15,"objectArray":[{"o1":false,"o2":true},{"o1":true,"o2":true},{"o1":true,"o2":false}],"string":"abcdef","void":null}
  
	std::cout << "My object 'myJson[\"objectArray\"][1][\"o2\"]' is: " << myJson["objectArray"][1]["o2"] << std::endl;
	//-> My object 'myJson["objectArray"][1]["o2"]' is: true
 
	std::cout << "My object 'myJson[\"objectArray\"][2][\"o2\"]' is: " << myJson["objectArray"][2]["o2"] << std::endl;
	//-> My object 'myJson["objectArray"][2]["o2"]' is: false
	//...
 
	myStream  << "{\"array\":[-10,-11,-12,-13], \"objectArray\" : [{\"o1\":false},{\"o2\":true} , {\"o3\":false}],\"bool\":true,\"char\":'a',\"double\":-3.14159,\"empty\":\"\",\"void\":null,\"int\":15,\"string\":\"abcdef\"}";
 
	std::cout << "My object 'objectArray' is: " << untyped()( myStream )["objectArray"] << std::endl;
	//-> My object 'objectArray' is: [{"o1":false,"o2":true},{"o1":true,"o2":true},{"o1":true,"o2":false}]
 
 
					// From a C string (or std::string)
	std::cout << myJson.deserializeJson("[0,1,2,3]") << std::endl;
	//-> [0,1,2,3]
 
					// <-- the same thing, with a short syntax...
	std::cout << myJson("[0,-1,-2,-3]")              << std::endl;
	//-> [0,-1,-2,-3]

	// *** WARNING *** --> Different from: untyped myJson("[0,-1,-2,-3]"), a simple initialisation from a C string ; so:
	{	untyped tmp( "[0,-1,-2,-3]" );			// <-- init with a C string
		std::cout << tmp << std::endl;			// <-- std::string
		//-> "[0,-1,-2,-3]"
		std::cout << tmp.string().at(1) << std::endl;	// <-- check
		//-> 0
		std::cout << "c_str()=" << tmp.c_str() << std::endl;
		//-> c_str()=[0,-1,-2,-3]
 
		tmp( tmp );					// <-- deserialisation from a std::string...
 
		std::cout << tmp << std::endl;			// <-- std::vector
		//-> [0,-1,-2,-3]
		std::cout << tmp.vector().at(1) << std::endl;	// <-- check
		//-> -1
		std::cout << "Here: c_str()=" << tmp.c_str() << std::endl;
		//-> Here: c_str()=
		std::cout << "but: serializeJson().c_str()=" << tmp.serializeJson().c_str() << std::endl;
		//-> but: serializeJson().c_str()=[0,-1,-2,-3]
	}
 
 
					// From std::string to std::stream
	untyped().deserializeJson("[ 4 ,-5,   2 ]").serializeJson( myStream );
	std::cout << myStream.str() << std::endl;
	//-> [4,-5,2]
 
					// From std::string to std::string:
	std::cout << untyped().deserializeJson("[ 4 ,-5,   2 ]").serializeJson() << std::endl;
	//-> "[4,-5,2]"
 
 
 
					// ****** Indented output ******

	myJson.prettyJsonMode(2); // <-- default tab size is 1 if no arg...

	myStream  << "{\"array\":[-10,-11,-12,-13], \"objectArray\" : [{\"o1\":false},{\"o2\":true} , {\"o3\":false
	std::cout << myJson(myStream) << std::endl;
	//->
	{
	  "array": [
	    -10,
	    -11,
	    -12,
	    -13
	  ],
	  "bool": true,
	  "char": 'a',
	  "double": -3.14159,
	  "empty": "",
	  "int": 15,
	  "objectArray": [
	    {
	      "o1": false
	      "o2": true
	    },
	    {
	      "o1": true
	      "o2": true
	    },
	    {
	      "o1": true
	      "o2": false
	    }
	  ],
	  "string": "abcdef",
	  "void": null
	}
 
									// in/from FILE:
	std::ofstream	outBinFile("/tmp/serialize.bin", std::ifstream::trunc|std::ifstream::binary);
	std::ifstream	inBinFile ("/tmp/serialize.bin", std::ofstream::binary);
 
	std::ofstream	outTxtFile("/tmp/serialize.json", std::ifstream::trunc);
	std::ifstream	inTxtFile ("/tmp/serialize.json", std::ofstream::in);
 
	myJson.binaryMode();
	myJson.serialise( outBinFile );
	myJson.serialiseJson( outTxtFile );
	outBinFile.flush(); outTxtFile.flush();

	std::cout << untyped()( inBinFile )["string"] << std::endl;
	//-> abcdef					// <-- Only what is needed...
 
	std::cout << inBinFile.tellg() << " octets deserialized from file." << std::endl;
	//-> 196 octets deserialized from file.
 
	myJson.jsonMode();
	std::cout << untyped()( inTxtFile )["double"] << std::endl << std::endl;
	//-> -3.14159				// <-- Extract only what is necessary...
 
	std::cout << inTxtFile.tellg() << " octets deserialized from file." << std::endl << std::endl;
	//-> 202 octets deserialized from file.

					// ****** Comments ******
	myStream=std::stringstream();
	myStream << "{/* This is a comment */ \"name\":\"Beno\u00EEt\"  /* This is an other comment */  }";
	std::cout << untyped()( myStream )["name"] << std::endl << std::endl;
	//-> "Benoît"
 
	return(0);
	}
