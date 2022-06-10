#include <stdio.h>
#include <dbus-cxx.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){

	//The dispatcher sends us information.  Make sure that it doesn't go out of scope or bad things will happen.
	std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();
	//Create a connection to the session bus
	std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SESSION );

	//Create a pointer to a remote object with the specified interface and path.
	std::shared_ptr<DBus::ObjectProxy> object = connection->create_object_proxy("com.rm5248", "/");

	//Make a method that returns an int and takes in a string
	DBus::MethodProxy<int(std::string)>& echoMessage = *(object->create_method<int(std::string)>("com.rm5248.ReceiveInterface", "echoMessage"));
	
	//Make a method that returns an int and takes in a string and two ints
	DBus::MethodProxy<int(std::string, int, int)>& echoAndAdd = *(object->create_method<int(std::string, int, int)>
		("com.rm5248.ReceiveInterface", "echoAndAdd"));

	DBus::MethodProxy<int(std::string, int, int)>& echoAndSub = *(object->create_method<int(std::string, int, int)>
                ("com.rm5248.ReceiveInterface", "echoAndSub"));



	int a=0, b=0;
    	// Converting string type to integer type
    	// using function "atoi( argument)"* 

	if( argc <=3 ) {
		printf(" usage :\n");
		printf("./send echo . .\n");
		printf("./send add value1 value2 \n");
		printf("./send sub value1 value2 \n");
		exit(-1);
	}

	if(argc == 4) {
    		a = atoi(argv[2]);     
    		b = atoi(argv[3]);
	}



	if(strcmp(argv[1],"echo")==0) {
		//We can now call these methods as though they were defined in this file, or in an included file
        	int firstResult = echoMessage("Client: Hello server !");
        	printf("%d\n", firstResult);
	}

	if(strcmp(argv[1],"add")==0) {
		int secondResult = echoAndAdd("Testing the addition", a, b);
		printf("ADD=%d\n", secondResult); 
	}

	if(strcmp(argv[1],"sub")==0)  {
        	int thirdResult = echoAndSub("Testing the subtraction", a, b);
        	printf("SUB=%d\n", thirdResult); 
	}

  	return 0;
}
