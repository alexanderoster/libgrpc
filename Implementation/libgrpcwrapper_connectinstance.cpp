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

#include "libgrpcwrapper_connectioninstance.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"

// Include custom headers here.
#include <fstream>

using namespace LibGRPCWrapper::Impl;

/*************************************************************************************************************************
 Class definition of CConnection 
**************************************************************************************************************************/


CConnectionInstance::CConnectionInstance(const std::string& sProtobufDefinition, const std::string sEndPoint)
{
    m_pChannel = grpc::CreateChannel(sEndPoint, grpc::InsecureChannelCredentials());
    if (m_pChannel.get() == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_COULDNOTCREATECHANNEL, "Could not create channel: " + sEndPoint);

    // Create temporary.proto file and fill with given content
    // TODO: Make virtual path readers!!!
    std::wstring sMapPathW;
    std::string sMapPath;
#ifdef _WIN32
    std::vector<wchar_t> TempPathBufferW;
    TempPathBufferW.resize(MAX_PATH + 1);
    auto nSize = GetTempPathW(MAX_PATH, TempPathBufferW.data());
    if (nSize == 0)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_COULDNOTRETRIEVETEMPPATHS);

    TempPathBufferW[MAX_PATH] = 0;
    sMapPathW = TempPathBufferW.data();

    std::vector<char> TempPathBuffer(MAX_PATH * 2 + 4);
    int nResult = WideCharToMultiByte(CP_UTF8, 0, sMapPathW.c_str(), sMapPathW.size (), TempPathBuffer.data (), MAX_PATH, nullptr, nullptr);
    if (nResult == 0)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_COULDNOTCONVERTUNICODESTRING);

    TempPathBuffer.at(TempPathBuffer.size() - 1) = 0;

    sMapPath = TempPathBuffer.data ();

#else
    sMapPath = "/tmp";
#endif

    std::string sProtoFilePathTemp = "libgrpc_temp_";

    for (int index = 0; index < 16; index++) {
        uint8_t nValue = rand() % 16;
        if (nValue < 10)
            sProtoFilePathTemp += ('0' + nValue);
        else
            sProtoFilePathTemp += ('a' + nValue - 10);
    }

    sProtoFilePathTemp += ".proto";

    std::wstring sProtoFilePathTempW (sProtoFilePathTemp.begin (), sProtoFilePathTemp.end());

    std::ofstream tempFile(sMapPathW + L"/" + sProtoFilePathTempW);
    tempFile << sProtobufDefinition;
    tempFile.close();

    m_pSourceTree = std::make_shared<google::protobuf::compiler::DiskSourceTree>();
    m_pSourceTree->MapPath("", sMapPath);

    m_pErrorCollector = std::make_shared<CConnectionErrorCollector> ();

    m_pImporter = std::make_shared<google::protobuf::compiler::Importer>(m_pSourceTree.get (), m_pErrorCollector.get());
    m_pFileDescriptor = m_pImporter->Import(sProtoFilePathTemp);

    if (m_pFileDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_FAILEDTOIMPORTPROTODEFINITION);   

    m_pMessageFactory = std::make_shared<google::protobuf::DynamicMessageFactory> ();

}

CConnectionInstance::~CConnectionInstance()
{
    m_pImporter = nullptr;
    m_pErrorCollector = nullptr;
    m_pSourceTree = nullptr;
}


bool CConnectionInstance::hasMessageType(const std::string& sMessageTypeName)
{
    const google::protobuf::Descriptor* messageDescriptor = m_pFileDescriptor->FindMessageTypeByName(sMessageTypeName);
    return (messageDescriptor != nullptr);
}

const google::protobuf::Descriptor* CConnectionInstance::getMessageDescriptor(const std::string& sMessageTypeName)
{
    const google::protobuf::Descriptor* messageDescriptor = m_pFileDescriptor->FindMessageTypeByName(sMessageTypeName);
    if (messageDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_UNKNOWNMESSAGETYPENAME, "unknown message type name:" + sMessageTypeName);

    return messageDescriptor;
}


std::shared_ptr<google::protobuf::Message> CConnectionInstance::createMessage(const std::string& sMessageTypeName)
{
    const google::protobuf::Descriptor* messageDescriptor = getMessageDescriptor(sMessageTypeName);

    const google::protobuf::Message* pMessage = m_pMessageFactory->GetPrototype(messageDescriptor);
    if (pMessage == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_COULDNOTGETMESSAGEPROTOTYPE);

    std::shared_ptr<google::protobuf::Message> pMessageInstance (pMessage->New());

    return pMessageInstance;
}

grpc::ByteBuffer CConnectionInstance::sendMessageBlocking(std::shared_ptr<google::protobuf::Message> pMessage, const std::string& sServiceMethod, uint32_t nTimeoutInMS)
{
    if (pMessage.get () == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
    if (sServiceMethod.empty ())
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_EMPTYSERVICEMETHOD);

    // Serialize request message and feed byte buffer
    std::string serializedRequest;
    pMessage->SerializeToString(&serializedRequest);
    grpc::Slice requestSlices(serializedRequest.c_str(), serializedRequest.size());
    grpc::ByteBuffer requestBuffer(&requestSlices, 1);

    // Setup RPC send/receive queue
    grpc::ClientContext context;
    grpc::CompletionQueue completionQueue;
    grpc::Status status;

    // Set deadline for server response
    std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(nTimeoutInMS);
    context.set_deadline(deadline);

    // Create client stub
    grpc::GenericStub genericStub(m_pChannel);
    std::unique_ptr<grpc::GenericClientAsyncReaderWriter> call = genericStub.PrepareCall(&context, sServiceMethod, &completionQueue);

    void* tag = nullptr;
    bool ok = false;

    std::cout << "Initialize RPC call and wait for confirmation";

    //Initialize RPC calland wait for confirmation
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

    return responseBuffer;

}
