/*++

Copyright (C) 2023 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Autodesk Inc. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Abstract: This is a stub class definition of CConnection

*/

#include "libgrpcwrapper_connection.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"

// Include protobuf and grpc package (installed via vcpkg manager)
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/generic/generic_stub.h>

// Include custom headers here.
#include <fstream>
#include <iostream>

using namespace LibGRPCWrapper::Impl;

class ErrorCollector : public google::protobuf::compiler::MultiFileErrorCollector
{
public:
    void AddError(const std::string& filename, int line, int column, const std::string& message)
    {
        std::cerr << filename << ":" << line << ":" << column << ": " << message << std::endl;
    }
};

/*************************************************************************************************************************
 Class definition of CConnection 
**************************************************************************************************************************/


CConnection::CConnection(const std::string& sProtobufDefinition)
    : m_sProtobufDefinition (sProtobufDefinition)
{
    
}

CConnection::~CConnection()
{

}

void CConnection::Connect(const std::string & sNetworkCredentials)
{
}

void CConnection::SendTestMessage()
{
    const std::string& sNetworkCredentials = "localhost:50051";

    std::cout << "Used proto file: " << std::endl << m_sProtobufDefinition << std::endl;

    std::shared_ptr<grpc::Channel> channel;
    const google::protobuf::FileDescriptor* fileDescriptor;

    // Create temporary.proto file and fill with given content
    const std::string sProtoFilePathTemp = "temp.proto";
    std::ofstream tempFile(sProtoFilePathTemp);
    tempFile << m_sProtobufDefinition;
    tempFile.close();

    std::cout << "Protobuf definition:" << std::endl;
    std::cout << m_sProtobufDefinition << std::endl;
    std::cout << "connecting to: " << sNetworkCredentials << std::endl;

    channel = grpc::CreateChannel(sNetworkCredentials, grpc::InsecureChannelCredentials());


    google::protobuf::compiler::DiskSourceTree sourceTree;
    sourceTree.MapPath("", "C:/WORKSPACE/libgrpc/build/Release/");
    ErrorCollector errorCollector;
    google::protobuf::compiler::Importer importer(&sourceTree, &errorCollector);

    fileDescriptor = importer.Import(sProtoFilePathTemp);

    if (!fileDescriptor)
    {
        std::cerr << "Failed to import proto content" << std::endl;
        return;
    }

    // Get descrip
    // tors for request method and response method
    const google::protobuf::Descriptor* requestDescriptor = fileDescriptor->FindMessageTypeByName("MachineRequest");
    const google::protobuf::Descriptor* responseDescriptor = fileDescriptor->FindMessageTypeByName("MachineResponse");

    if (!requestDescriptor || !responseDescriptor)
    {
        std::cerr << "Message types not found in .proto file" << std::endl;
        return;
    }

    // Use dynamic message factory to build request and response messages
    google::protobuf::DynamicMessageFactory factory;
    google::protobuf::Message* requestMessage = factory.GetPrototype(requestDescriptor)->New(); // delete at end of scope
    google::protobuf::Message* responseMessage = factory.GetPrototype(responseDescriptor)->New(); // delete at end of scope

    // Use reflection to populate the request message
    const google::protobuf::Reflection* requestReflection = requestMessage->GetReflection();
    requestReflection->SetString(requestMessage, requestDescriptor->FindFieldByName("field_1"), "Test value for field 1");
    requestReflection->SetString(requestMessage, requestDescriptor->FindFieldByName("field_2"), "Test value for field 2");

    std::string serializedRequest;
    requestMessage->SerializeToString(&serializedRequest);
    grpc::Slice requestSlices(serializedRequest.c_str(), serializedRequest.size());
    grpc::ByteBuffer requestBuffer(&requestSlices, 1);

    grpc::string serviceMethod = "/machine.MachineService/SendTestMessage";

    // Cleanup
    delete requestMessage;

    // Setup RPC send/receive queue
    grpc::ClientContext context;
    grpc::CompletionQueue completionQueue;
    grpc::Status status;

    // Set deadline for server response
    long deadlineInSec = 10;
    std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() + std::chrono::seconds(deadlineInSec);
    context.set_deadline(deadline);

    // Create client stub
    grpc::GenericStub genericStub(channel);
    std::unique_ptr<grpc::GenericClientAsyncReaderWriter> call = genericStub.PrepareCall(&context, serviceMethod, &completionQueue);

    void* tag;
    bool ok;

    // Initialize RPC call and wait for confirmation
    call->StartCall((void*)1);

    if (!completionQueue.Next(&tag, &ok) || !ok || tag != (void*)1)
    {
        std::cout << "Could not start RPC call" << std::endl;
    }
    else
    {
        std::cout << "Successfully started RPC call" << std::endl;
    }

    // Send request to server and wait for confirmation
    call->Write(requestBuffer, (void*)2);

    if (!completionQueue.Next(&tag, &ok) || !ok || tag != (void*)2)
    {
        std::cout << "Could not send request" << std::endl;
    }
    else
    {
        std::cout << "Successfully sent request" << std::endl;
    }

    // Indicate that request is completed and wait for confirmation
    call->WritesDone((void*)3);

    if (!completionQueue.Next(&tag, &ok) || !ok || tag != (void*)3)
    {
        std::cout << "Could not indicate end of request" << std::endl;
    }
    else
    {
        std::cout << "Successfully indicated end of request" << std::endl;
    }

    // Read response from server and wait for confirmation
    grpc::ByteBuffer responseBuffer;
    call->Read(&responseBuffer, (void*)4);

    if (!completionQueue.Next(&tag, &ok) || !ok || tag != (void*)4)
    {
        std::cout << "Could not receive response" << std::endl;
    }
    else
    {
        std::cout << "Successfully received response" << std::endl;
    }

    // Finish RPC call and wait for confirmation
    call->Finish(&status, (void*)5);

    if (!completionQueue.Next(&tag, &ok) || !ok || tag != (void*)5)
    {
        std::cout << "Could not finish RPC call" << std::endl;
    }
    else
    {
        std::cout << "Successfully finished RPC call" << std::endl;
    }

    if (!status.ok())
    {
        std::cerr << "RPC failed: " << status.error_message() << " - code: " << status.error_code() << std::endl;
    }

    // Deserialize response
    std::vector<grpc::Slice> responseSlices;
    responseBuffer.Dump(&responseSlices);

    if (!responseSlices.empty())
    {
        std::string serializedResponse = std::string((const char*)responseSlices[0].begin(), responseSlices[0].size());

        if (responseMessage->ParseFromString(serializedResponse))
        {
            const google::protobuf::Reflection* reflection = responseMessage->GetReflection();
            const google::protobuf::FieldDescriptor* fieldDescriptor = responseDescriptor->FindFieldByName("response_1");

            std::string responseValue = reflection->GetString(*responseMessage, fieldDescriptor);
            std::cout << "Received response: '" << responseValue << "'" << std::endl;

            // Cleanup
            delete responseMessage;
        }
        else
        {
            std::cerr << "Failed to parse the response" << std::endl;
        }
    }
}


