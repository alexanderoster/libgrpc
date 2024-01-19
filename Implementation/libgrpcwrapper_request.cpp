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


Abstract: This is a stub class definition of CRequest

*/

#include "libgrpcwrapper_request.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"

// Include custom headers here.
#include "libgrpcwrapper_response.hpp"

using namespace LibGRPCWrapper::Impl;

/*************************************************************************************************************************
 Class definition of CRequest 
**************************************************************************************************************************/

CRequest::CRequest(std::shared_ptr<CConnectionInstance> pConnectionInstance, const std::string& sRequestTypeIdentifier, const std::string& sResponseTypeIdentifier)
    : CMessage (), m_pConnectionInstance (pConnectionInstance), m_sRequestTypeIdentifier (sRequestTypeIdentifier), m_sResponseTypeIdentifier (sResponseTypeIdentifier)
{
    if (m_pConnectionInstance.get() == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);

    if (sRequestTypeIdentifier.empty ())
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_EMPTYREQUESTTYPEIDENTIFIER);
    if (sResponseTypeIdentifier.empty())
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_EMPTYRESPONSETYPEIDENTIFIER);

    if (!m_pConnectionInstance->hasMessageType (sRequestTypeIdentifier))
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDREQUESTTYPEIDENTIFIER, "invalid request type identifier: " + sRequestTypeIdentifier);
    if (!m_pConnectionInstance->hasMessageType(sResponseTypeIdentifier))
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDRESPONSETYPEIDENTIFIER, "invalid response type identifier: " + sResponseTypeIdentifier);

    m_pRequestMessageDescriptor = m_pConnectionInstance->getMessageDescriptor(sRequestTypeIdentifier);
    m_pRequestMessage = m_pConnectionInstance->createMessage(sRequestTypeIdentifier);
    m_pRequestReflection = m_pRequestMessage->GetReflection();

}

CRequest::~CRequest()
{
    m_pRequestReflection = nullptr;
    m_pRequestMessage = nullptr;
    m_pRequestMessageDescriptor = nullptr;
    m_pConnectionInstance = nullptr;
}

std::string CRequest::GetRequestType()
{
    return m_sRequestTypeIdentifier;
}

std::string CRequest::GetExpectedResponseType()
{
    return m_sResponseTypeIdentifier;
}

bool CRequest::HasField(const std::string& sFieldName)
{
    const google::protobuf::FieldDescriptor * pFieldDescriptor = m_pRequestMessageDescriptor->FindFieldByName(sFieldName);
    return (pFieldDescriptor != nullptr);
}

bool CRequest::HasStringField(const std::string& sFieldName)
{
    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pRequestMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor != nullptr) 
        return (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::Type::TYPE_STRING);

    return false;
}

void CRequest::SetStringField(const std::string& sFieldName, const std::string& sValue)
{
    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pRequestMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr) 
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_REQUESTFIELDNOTFOUND, "request field not found: " + sFieldName);

    m_pRequestReflection->SetString(m_pRequestMessage.get(), pFieldDescriptor, sValue);

}

std::string CRequest::GetStringField(const std::string& sFieldName)
{
    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pRequestMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_REQUESTFIELDNOTFOUND, "request field not found: " + sFieldName);

    return m_pRequestReflection->GetString (*m_pRequestMessage.get(), pFieldDescriptor);
}

IResponse * CRequest::SendBlocking(const std::string & sServiceMethod, const LibGRPCWrapper_uint32 nTimeOutInMS)
{
    grpc::ByteBuffer responseBuffer = m_pConnectionInstance->sendMessageBlocking(m_pRequestMessage, sServiceMethod, nTimeOutInMS);

    return new CResponse (m_pConnectionInstance, m_sResponseTypeIdentifier, responseBuffer);  
    

}

