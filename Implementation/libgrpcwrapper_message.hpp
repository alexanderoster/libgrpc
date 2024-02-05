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


Abstract: This is the class declaration of CMessage

*/


#ifndef __LIBGRPCWRAPPER_MESSAGE
#define __LIBGRPCWRAPPER_MESSAGE

#include "libgrpcwrapper_interfaces.hpp"

// Parent classes
#include "libgrpcwrapper_base.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "libgrpcwrapper_connectioninstance.hpp"

namespace LibGRPCWrapper {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CMessage 
**************************************************************************************************************************/

class CMessage : public virtual IMessage, public virtual CBase {
private:


protected:

    const google::protobuf::Descriptor* m_pMessageDescriptor;
    std::shared_ptr<google::protobuf::Message> m_pMessage;
    const google::protobuf::Reflection* m_pReflection;

    void ensureObjects();

public:

    CMessage();

    virtual ~CMessage();

    bool HasField(const std::string& sFieldName) override;

    bool HasStringField(const std::string& sFieldName) override;

    void SetStringField(const std::string& sFieldName, const std::string& sValue) override;

    std::string GetStringField(const std::string& sFieldName) override;

	void SetInt32Field(const std::string& sFieldName, const LibGRPCWrapper_int32 nValue) override;

	LibGRPCWrapper_int32 GetInt32Field(const std::string& sFieldName) override;

	void SetUInt32Field(const std::string& sFieldName, const LibGRPCWrapper_uint32 nValue) override;

	LibGRPCWrapper_uint32 GetUInt32Field(const std::string& sFieldName) override;

	void SetInt64Field(const std::string& sFieldName, const LibGRPCWrapper_int64 nValue) override;

	LibGRPCWrapper_int64 GetInt64Field(const std::string& sFieldName) override;

	void SetUInt64Field(const std::string& sFieldName, const LibGRPCWrapper_uint64 nValue) override;

	LibGRPCWrapper_uint64 GetUInt64Field(const std::string& sFieldName) override;

	void SetBoolField(const std::string& sFieldName, const bool bValue) override;

	bool GetBoolField(const std::string& sFieldName) override;

	void SetFloatField(const std::string& sFieldName, const LibGRPCWrapper_single fValue) override;

	LibGRPCWrapper_single GetFloatField(const std::string& sFieldName) override;

	void SetDoubleField(const std::string& sFieldName, const LibGRPCWrapper_double dValue) override;

	LibGRPCWrapper_int32 GetDoubleField(const std::string& sFieldName) override;


};

} // namespace Impl
} // namespace LibGRPCWrapper

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBGRPCWRAPPER_MESSAGE
