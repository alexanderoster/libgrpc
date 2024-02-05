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


Abstract: This is a stub class definition of CResponse

*/

#include "libgrpcwrapper_response.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"

// Include custom headers here.


using namespace LibGRPCWrapper::Impl;

/*************************************************************************************************************************
 Class definition of CResponse 
**************************************************************************************************************************/

CResponse::CResponse(std::shared_ptr<CConnectionInstance> pConnectionInstance, const std::string& sResponseTypeIdentifier, const grpc::ByteBuffer& byteBuffer)
    : CMessage(), m_pConnectionInstance(pConnectionInstance), m_sResponseTypeIdentifier(sResponseTypeIdentifier)
{
    if (m_pConnectionInstance.get() == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);

    if (sResponseTypeIdentifier.empty())
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_EMPTYRESPONSETYPEIDENTIFIER);

    if (!m_pConnectionInstance->hasMessageType(sResponseTypeIdentifier))
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDRESPONSETYPEIDENTIFIER, "invalid response type identifier: " + sResponseTypeIdentifier);

    m_pMessageDescriptor = m_pConnectionInstance->getMessageDescriptor(sResponseTypeIdentifier);
    m_pMessage = m_pConnectionInstance->createMessage(sResponseTypeIdentifier);
    m_pReflection = m_pMessage->GetReflection();

    // Deserialize response
    std::vector<grpc::Slice> responseSlices;
    byteBuffer.Dump(&responseSlices);

    if (responseSlices.empty())
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_EMPTYREQUESTRESPONSE, "empty request response: " + m_sResponseTypeIdentifier);
    std::string serializedResponse = std::string((const char*)responseSlices[0].begin(), responseSlices[0].size());

    if (!m_pMessage->ParseFromString(serializedResponse))
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_FAILEDTOPARSEREQUESTRESPONSE, "empty request response: " + m_sResponseTypeIdentifier);

}

CResponse::~CResponse()
{

}


std::string CResponse::GetResponseType()
{
    return m_sResponseTypeIdentifier;
}

