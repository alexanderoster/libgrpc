
#include <iostream>
#include "libgrpcwrapper_dynamic.hpp"
#include <sstream>
#include <fstream>

int main()
{
    try {

        std::cout << "Loading Wrapper\n";
        auto pWrapper = LibGRPCWrapper::CWrapper::loadLibrary("libgrpcwrapper.dll");

        std::fstream fileStream;
        fileStream.open("machine.proto");
        if (!fileStream.is_open())
            throw std::runtime_error("could not open proto file.");

        std::stringstream buffer;
        buffer << fileStream.rdbuf();


		/*
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
        protoFileStream << "  bool response_2 = 2;" << std::endl;
        protoFileStream << "}" << std::endl;

        */

        std::cout << "Creating connection\n";
        std::cout << buffer.str() << std::endl;
        auto pProtocol = pWrapper->CreateProtocol(buffer.str());

        std::cout << "Connecting\n";
        auto pConnection = pProtocol->ConnectUnsecure("192.168.5.2:50051");

        std::cout << "Connection end point: " << pConnection->GetEndPoint() << std::endl;

        std::cout << "Creating request "<< std::endl;
        auto pRequest = pConnection->CreateStaticRequest("DoorOpenRequest", "Result");

        std::cout << "Setting fields" << std::endl;
        pRequest->SetBoolField("both", true);

        std::cout << "Sending Request\n";
        auto pResponse = pRequest->SendBlocking("/machine_interface.Machine/OpenDoors", 10000);
        if (pResponse->HasField("success")) {
            std::cout << "Call succeeded: " << pResponse->GetBoolField ("success") << std::endl;

        }
        else {
            std::string sResponseField = pResponse->GetStringField("error");
            std::cout << "Error field: " << sResponseField << std::endl;

        }
//         = pResponse->GetBoolField("success");

        //std::cout << "Response bool field: " << pRequest->GetBoolField ("response_2") << std::endl;

        std::cout << "done\n";
    }
    catch (std::exception& E) {
        std::cout << "Fatal error: " << E.what() << std::endl;
    }

    std::cout << "End of program. Press any key to exit...";
    std::cin.get();
}


