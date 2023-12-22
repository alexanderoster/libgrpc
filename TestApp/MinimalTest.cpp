
#include <iostream>
#include "libgrpcwrapper_dynamic.hpp"
#include <sstream>

int main()
{
    std::cout << "Hello World!\n";

    try {

        std::cout << "Loading Wrapper\n";
        auto pWrapper = LibGRPCWrapper::CWrapper::loadLibrary("libgrpcwrapper.dll");

		std::stringstream protoFileStream;
		
		protoFileStream << "syntax = \"proto3\";" << std::endl;
		protoFileStream << "package test;" << std::endl;

		protoFileStream << "service Todo {" << std::endl;
		protoFileStream << "  rpc createTodo(TodoItem) returns (TodoItem);" << std::endl;
		protoFileStream << "}" << std::endl;

		protoFileStream << "message TodoItem {" << std::endl;
		protoFileStream << "  int32 id = 1;" << std::endl;
		protoFileStream << "  string text = 2;" << std::endl;
		protoFileStream << "}" << std::endl;

        std::cout << "Creating connection\n";
        auto pConnection = pWrapper->CreateConnection(protoFileStream.str ());

        std::cout << "Connecting\n";

        pConnection->Connect("localhost");

        std::cout << "Sending Request\n";

        pConnection->SendRequest();

        std::cout << "done\n";
    }
    catch (std::exception& E) {
        std::cout << "Fatal error: " << E.what() << std::endl;
    }

}


