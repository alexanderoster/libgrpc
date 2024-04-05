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


Abstract: This is a stub class definition of CMessage

*/

#include "libgrpcwrapper_message.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"

// Include custom headers here.


using namespace LibGRPCWrapper::Impl;

/*************************************************************************************************************************
 Class definition of CMessage 
**************************************************************************************************************************/

CMessage::CMessage(std::shared_ptr<CConnectionInstance> pConnectionInstance)
    : m_pMessageDescriptor (nullptr), m_pReflection (nullptr), m_pConnectionInstance (pConnectionInstance)
{
    if (pConnectionInstance.get() == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
}

CMessage::~CMessage()
{
    m_pReflection = nullptr;
    m_pMessage = nullptr;
    m_pMessageDescriptor = nullptr;

    m_pMessageOwner = nullptr;
    m_pConnectionInstance = nullptr;
}

void CMessage::setMessageObjects(std::shared_ptr<google::protobuf::Message> pMessageOwner, google::protobuf::Message* pMessage)
{
    if (pMessageOwner.get () == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
    if (pMessage == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);

    m_pMessageOwner = pMessageOwner;
    m_pMessage = pMessage;

    std::string sTypeName = m_pMessage->GetTypeName();
    m_pMessageDescriptor = m_pConnectionInstance->getMessageDescriptor(sTypeName);
    m_pReflection = m_pMessage->GetReflection();

}

void CMessage::ensureObjects()
{
    if (m_pMessage == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGISNULL);
    if (m_pMessageDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEDESCRIPTORISNULL);
    if (m_pReflection == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGREFLECTIONISNULL);

}


bool CMessage::HasField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    return (pFieldDescriptor != nullptr);
}

bool CMessage::HasStringField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor != nullptr)
        return (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::Type::TYPE_STRING);

    return false;
}

bool CMessage::HasMessageField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor != nullptr)
        return (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::Type::TYPE_MESSAGE);

    return false;

}


IMessage* CMessage::GetMessageField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    google::protobuf::Message* pSubMessage = m_pReflection->MutableMessage(m_pMessage, pFieldDescriptor);

    std::unique_ptr<CMessage> pResult;
    pResult->setMessageObjects(m_pMessageOwner, pSubMessage);

    return pResult.release();
}


void CMessage::SetStringField(const std::string& sFieldName, const std::string& sValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetString(m_pMessage, pFieldDescriptor, sValue);

}

std::string CMessage::GetStringField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "request field not found: " + sFieldName);

    return m_pReflection->GetString(*m_pMessage, pFieldDescriptor);
}


void CMessage::SetInt32Field(const std::string& sFieldName, const LibGRPCWrapper_int32 nValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "request field not found: " + sFieldName);

    m_pReflection->SetInt32(m_pMessage, pFieldDescriptor, nValue);
}

LibGRPCWrapper_int32 CMessage::GetInt32Field(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetInt32(*m_pMessage, pFieldDescriptor);
}

void CMessage::SetUInt32Field(const std::string& sFieldName, const LibGRPCWrapper_uint32 nValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetUInt32(m_pMessage, pFieldDescriptor, nValue);
}

LibGRPCWrapper_uint32 CMessage::GetUInt32Field(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetUInt32(*m_pMessage, pFieldDescriptor);
}

void CMessage::SetInt64Field(const std::string& sFieldName, const LibGRPCWrapper_int64 nValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetInt64(m_pMessage, pFieldDescriptor, nValue);
}

LibGRPCWrapper_int64 CMessage::GetInt64Field(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetInt64(*m_pMessage, pFieldDescriptor);
}

void CMessage::SetUInt64Field(const std::string& sFieldName, const LibGRPCWrapper_uint64 nValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetUInt64(m_pMessage, pFieldDescriptor, nValue);
}

LibGRPCWrapper_uint64 CMessage::GetUInt64Field(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetUInt64(*m_pMessage, pFieldDescriptor);
}

void CMessage::SetBoolField(const std::string& sFieldName, const bool bValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetBool(m_pMessage, pFieldDescriptor, bValue);

}

bool CMessage::GetBoolField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetBool(*m_pMessage, pFieldDescriptor);

}

void CMessage::SetFloatField(const std::string& sFieldName, const LibGRPCWrapper_single fValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetFloat(m_pMessage, pFieldDescriptor, fValue);
}

LibGRPCWrapper_single CMessage::GetFloatField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetFloat(*m_pMessage, pFieldDescriptor);

}

void CMessage::SetDoubleField(const std::string& sFieldName, const LibGRPCWrapper_double dValue)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    m_pReflection->SetDouble(m_pMessage, pFieldDescriptor, dValue);

}

LibGRPCWrapper_double CMessage::GetDoubleField(const std::string& sFieldName)
{
    ensureObjects();

    const google::protobuf::FieldDescriptor* pFieldDescriptor = m_pMessageDescriptor->FindFieldByName(sFieldName);
    if (pFieldDescriptor == nullptr)
        throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_MESSAGEFIELDNOTFOUND, "message field not found: " + sFieldName);

    return m_pReflection->GetDouble(*m_pMessage, pFieldDescriptor);

}

std::shared_ptr<CConnectionInstance> CMessage::getConnectionInstance()
{
    return m_pConnectionInstance;
}

google::protobuf::Message* CMessage::getMessage()
{
    ensureObjects();
    return m_pMessage;

}
