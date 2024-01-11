
#include <iostream>
#include "libgrpcwrapper_dynamic.hpp"
#include <sstream>

int main()
{
    try {

        std::cout << "Loading Wrapper\n";
        auto pWrapper = LibGRPCWrapper::CWrapper::loadLibrary("libgrpcwrapper.dll");

		std::stringstream protoFileStream;

		protoFileStream << "syntax = \"proto3\";" << std::endl;
		protoFileStream << "package machine;" << std::endl;

		protoFileStream << "service MachineService {" << std::endl;
		protoFileStream << "  rpc SendTestMessage(MachineRequest) returns (MachineResponse);" << std::endl;
		protoFileStream << "}" << std::endl;

		protoFileStream << "message MachineRequest {" << std::endl;
		protoFileStream << "  string field_1 = 1;" << std::endl;
		protoFileStream << "  string field_2 = 2;" << std::endl;
		protoFileStream << "}" << std::endl;

        protoFileStream << "message MachineResponse {" << std::endl;
        protoFileStream << "  string response_1 = 1;" << std::endl;
        protoFileStream << "}" << std::endl;

        std::cout << "Creating connection\n";
        auto pConnection = pWrapper->CreateConnection(protoFileStream.str());

        std::cout << "Connecting\n";

        //pConnection->Connect("localhost:50051");

        std::cout << "Sending Request\n";

        pConnection->SendTestMessage();

        std::cout << "done\n";
    }
    catch (std::exception& E) {
        std::cout << "Fatal error: " << E.what() << std::endl;
    }

    std::cout << "End of program. Press any key to exit...";
    std::cin.get();
}


