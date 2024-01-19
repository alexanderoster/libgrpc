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


Abstract: This is the class declaration of CConnection

*/


#ifndef __LIBGRPCWRAPPER_CONNECTIONINSTANCE
#define __LIBGRPCWRAPPER_CONNECTIONINSTANCE

#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/generic/generic_stub.h>


namespace LibGRPCWrapper {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CConnection 
**************************************************************************************************************************/

    class CConnectionInstance;

    class CConnectionErrorCollector : public google::protobuf::compiler::MultiFileErrorCollector
    {
    private:

        std::vector<std::string> m_ErrorList;

    public:


        void AddError(const std::string& filename, int line, int column, const std::string& message)
        {
            m_ErrorList.push_back(filename + ":" + std::to_string(line) + ":" + std::to_string(column) + " " + message);
        }

        std::vector<std::string> getErrors()
        {
            return m_ErrorList;
        }

    };


    class CConnectionInstance {
    private:

        std::shared_ptr<grpc::Channel> m_pChannel;

        std::shared_ptr <google::protobuf::compiler::DiskSourceTree> m_pSourceTree;

        std::shared_ptr <CConnectionErrorCollector> m_pErrorCollector;

        std::shared_ptr<google::protobuf::compiler::Importer> m_pImporter;

        std::shared_ptr<google::protobuf::DynamicMessageFactory> m_pMessageFactory;
        
        const google::protobuf::FileDescriptor* m_pFileDescriptor;

    public:

        CConnectionInstance(const std::string & sProtobufDefinition, const std::string sEndPoint);

        virtual ~CConnectionInstance();

        bool hasMessageType(const std::string & sMessageTypeName);

        const google::protobuf::Descriptor* getMessageDescriptor(const std::string& sMessageTypeName);

        std::shared_ptr<google::protobuf::Message> createMessage(const std::string& sMessageTypeName);

        grpc::ByteBuffer sendMessageBlocking (std::shared_ptr<google::protobuf::Message> pMessage, const std::string & sServiceMethod, uint32_t nTimeoutInMS);
    };

} // namespace Impl
} // namespace LibGRPCWrapper


#endif // __LIBGRPCWRAPPER_CONNECTIONINSTANCE
