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


Here are use examples:

	# define out /*
	g++ -std=c++0x -rdynamic -Wall -s -O2 -o test $0 untyped.cpp; exit $?
	# define out */
	# undef out
 
	#include "untyped.h"
 
	int main() {
 								// Intuitive syntaxe:
	untyped	myJson('j');
	myJson.jsonMode();		// <-- JSON format management
 
	std::cout << myJson                 << std::endl;	// <-- type char
 
	std::cout << ( myJson + 'A' - 'a' ) << std::endl;
 
	myJson = "aaaJaaa";                                     // <-- type string
	std::cout << ( myJson + 's' + "on" - "aaa" - "aaa" ) << std::endl;
	
	myJson.binaryMode();	// <-- BINARY format management
	std::cout << ( myJson + 's' + "on" - "aaa" - "aaa" ) << std::endl << std::endl;
	myJson.jsonMode();	// <-- JSON format management
 
								// Implicit or explicit cast:
	myJson = 31.4159e-1;
	auto myDouble = myJson;							// <-- implicite
	std::cout << "myDouble   =" << myDouble << std::endl    << std::endl;
	std::cout << "cast<float>=" << myDouble.value<double>() << std::endl;	// <-- explicite
	std::cout << "cast<int>  =" << myDouble.value<int>()    << std::endl;
	std::cout << "cast<bool> =" << myDouble.value<bool>()   << std::endl << std::endl;

 
/-->

	'j'
	'J'
	"Json"
	Json
	
	myDouble   =3.14159
	cast<float>=3.14159
	cast<int>  =3
	cast<bool> =1
.

								// Automatic memory allocation, as close as needed:
 
	myJson.clear();
	myJson[0]=10;
	myJson[1]=11;
	myJson[2]=12;
	myJson[3]=13;
	std::cout << "Serialization:" << std::endl;
	std::cout << myJson << std::endl;
 
	untyped myJson2;
	myJson2["array1"] = myJson;
	myJson2["array2"] = myJson; myJson2["array2"][3]=23;
	myJson2["array3"] = myJson; myJson2["array3"][2]=32;
	myJson2["array4"] = myJson; myJson2["array4"][1]=41;
	myJson = myJson2; myJson2.clear();
	std::cout << myJson << std::endl << std::endl;
 
								// Serialization:
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
	std::cout << myJson << std::endl << std::endl;
 
								// from and to std::string:
	std::stringstream o(std::stringstream::out);
	untyped()("[4,-5,2]").serializeJson(o);
	std::string s(o.str());
	std::cout << "Deserialize and re-serialize fron/to strings: " << s << std::endl << std::endl;

  
/-->

	Serialization:
	[10,11,12,13]
	{"array1":[10,11,12,13],"array2":[10,11,12,23],"array3":[10,11,32,13],"array4":[10,41,12,13]}
 	
	{"array":[-10,-11,-12,-13],"bool":true,"char":'a',"float":-3.14159,"empty":null,"int":15,"string":"abcdef"}
 
	Deserialize and re-serialize fron/to strings: [4,-5,2]
 .

								// Deserialisation from stream:
 
	myStream  << "{\"array\":[-10,-11,-12,-13], \"objectArray\" : [{\"o1\":false},{\"o2\":true} , {\"o3\":false}],\"bool\":true,\"char\":'a',\"double\":-3.14159,\"empty\":\"\",\"void\":null,\"int\":15,\"string\":\"abcdef\"}";
 
	std::cout << "Deserialization:"                  << std::endl;
	std::cout << myJson.deserializeJson("[0,1,2,3]") << std::endl;			// From string
	std::cout << myJson("[0,-1,-2,-3]")              << std::endl; // for short...
	std::cout << myJson[2]              << std::endl << std::endl;
	
	std::cout << myJson.deserializeJson( myStream )  << std::endl;			// From stream
 	
	std::cout << "My object 'myJson[\"objectArray\"][1][\"o2\"]' is: " << myJson["objectArray"][1]["o2"] << std::endl;
	std::cout << "My object 'myJson[\"objectArray\"][2][\"o2\"]' is: " << myJson["objectArray"][2]["o2"] << std::endl << std::endl;
 
	std::cout << untyped()( myStream )["objectArray"] << std::endl << std::endl;
 
 
/-->
	
	Deserialization:
	[0,1,2,3]
	[0,-1,-2,-3]
	-2
	
	{"array":[-10,-11,-12,-13],"bool":true,"char":'a',"double":-3.14159,"empty":"","int":15,"objectArray":[{"o1":false,"o2":true},{"o1":true,"o2":true},{"o1":true,"o2":false}],"string":"abcdef","void":null}
	
	My object 'myJson["objectArray"][1]["o2"]' is: true
	My object 'myJson["objectArray"][2]["o2"]' is: false
 
	"objectArray":[{"o1":false,"o2":true},{"o1":true,"o2":true},{"o1":true,"o2":false}]
 
 .

								// Indented output:
	myJson.prettyJsonMode();
	std::cout << myJson << std::endl << std::endl;
 

/-->
	
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
 .

								// in/from FILE:
	std::ofstream	outBinFile("/tmp/serialize.bin", std::ifstream::trunc|std::ifstream::binary);
	std::ifstream	inBinFile ("/tmp/serialize.bin", std::ofstream::binary);
 
	std::ofstream	outTxtFile("/tmp/serialize.json", std::ifstream::trunc);
	std::ifstream	inTxtFile ("/tmp/serialize.json", std::ofstream::in);
 
	myJson.binaryMode();
	myJson.serialise( outBinFile );
	myJson.serialiseJson( outTxtFile );
	outBinFile.flush(); outTxtFile.flush();

	std::cout << untyped()( inBinFile )["string"] << std::endl;			// <-- Only what is needed...
	std::cout << inBinFile.tellg() << " octets deserialized from file." << std::endl;
	myJson.jsonMode();
	std::cout << untyped()( inTxtFile )["double"] << std::endl << std::endl;
	std::cout << inTxtFile.tellg() << " octets deserialized from file." << std::endl << std::endl;

  
/-->

	abcdef
	196 octets deserialized from file.
	"double": -3.14159,
	202 octets deserialized from file.
 .

								// Comments:
 
	myStream=std::stringstream();
	myStream << "{/* This is a comment */ \"name\":\"Beno\u00EEt\"  /* This is an other comment */  }";
	std::cout << untyped()( myStream )["name"] << std::endl << std::endl;

  
/-->

	"Benoît"
 .

	return(0);
	}
