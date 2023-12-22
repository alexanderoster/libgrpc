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


This file has been generated by the Automatic Component Toolkit (ACT) version 1.8.0-develop.

Abstract: This is an autogenerated C++ implementation file in order to allow easy
development of GRPC Library Wrapper. It provides an automatic Journaling mechanism for the library implementation.

Interface version: 1.2.0

*/


#include <string>
#include <sstream>
#include <iomanip>

#include "libgrpcwrapper_interfacejournal.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"


std::string LibGRPCWrapperHandleToHex (LibGRPCWrapperHandle pHandle)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(sizeof(LibGRPCWrapper_uint64) * 2)
		<< std::hex << (LibGRPCWrapper_uint64) pHandle;
	return stream.str();
}

CLibGRPCWrapperInterfaceJournalEntry::CLibGRPCWrapperInterfaceJournalEntry(CLibGRPCWrapperInterfaceJournal * pJournal, std::string sClassName, std::string sMethodName, LibGRPCWrapperHandle pInstanceHandle)
	: m_pJournal(pJournal), m_ErrorCode(LIBGRPCWRAPPER_SUCCESS), m_sClassName(sClassName), m_sMethodName(sMethodName), m_nInitTimeStamp(0), m_nFinishTimeStamp(0)
{
	if (pJournal == nullptr)
		throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
	m_nInitTimeStamp = m_pJournal->getTimeStamp ();
	m_sInstanceHandle = LibGRPCWrapperHandleToHex (pInstanceHandle);
}

CLibGRPCWrapperInterfaceJournalEntry::~CLibGRPCWrapperInterfaceJournalEntry()
{
}

void CLibGRPCWrapperInterfaceJournalEntry::addParameter(const std::string & sName, const std::string & sParameterType, const std::string & sParameterValue)
{
	m_sParameters.push_back(std::make_pair(std::make_pair(sName, sParameterType), sParameterValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addResult(const std::string & sName, const std::string & sResultType, const std::string & sResultValue)
{
	m_sResultValues.push_back(std::make_pair(std::make_pair(sName, sResultType), sResultValue));
}

std::string CLibGRPCWrapperInterfaceJournalEntry::getXMLString()
{
	std::stringstream sStream;
	LibGRPCWrapper_uint64 nDuration = 0;

	if (m_nFinishTimeStamp > m_nInitTimeStamp)
		nDuration = m_nFinishTimeStamp - m_nInitTimeStamp;

	sStream << "    <entry";
	if (m_sClassName != "")
		sStream << " class=\"" << m_sClassName << "\"";
	sStream << " method=\"" << m_sMethodName << "\"";
	if (m_ErrorCode != LIBGRPCWRAPPER_SUCCESS)
		sStream << " errorcode=\"" << m_ErrorCode << "\"";
	sStream << " timestamp=\"" << m_nInitTimeStamp << "\" duration=\"" << nDuration << "\">\n";

	if (m_sClassName != "")
		sStream << "        <instance handle=\"" << m_sInstanceHandle << "\" />\n";

	auto iParamIter = m_sParameters.begin();
	while (iParamIter != m_sParameters.end()) {
		sStream << "        <parameter name=\"" << iParamIter->first.first << "\" type=\"" << iParamIter->first.second << "\" value=\"" << iParamIter->second <<"\" />\n";
		iParamIter++;
	}

	auto iResultIter = m_sResultValues.begin();
	while (iResultIter != m_sResultValues.end()) {
		sStream << "        <result name=\"" << iResultIter->first.first << "\" type=\"" << iResultIter->first.second << "\" value=\"" << iResultIter->second << "\" />\n";
		iResultIter++;
	}

	sStream << "    </entry>\n";
	return sStream.str ();
}

void CLibGRPCWrapperInterfaceJournalEntry::writeSuccess()
{
	writeError(LIBGRPCWRAPPER_SUCCESS);
}

void CLibGRPCWrapperInterfaceJournalEntry::writeError(LibGRPCWrapperResult nErrorCode)
{
	m_ErrorCode = nErrorCode;
	m_nFinishTimeStamp = m_pJournal->getTimeStamp();
	m_pJournal->writeEntry(this);
}

void CLibGRPCWrapperInterfaceJournalEntry::addBooleanParameter(const std::string & sName, const bool bValue)
{
	addParameter (sName, "bool", std::to_string((int)bValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt8Parameter(const std::string & sName, const LibGRPCWrapper_uint8 nValue)
{
	addParameter(sName, "uint8", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt16Parameter(const std::string & sName, const LibGRPCWrapper_uint16 nValue)
{
	addParameter(sName, "uint16", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt32Parameter(const std::string & sName, const LibGRPCWrapper_uint32 nValue)
{
	addParameter(sName, "uint32", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt64Parameter(const std::string & sName, const LibGRPCWrapper_uint64 nValue)
{
	addParameter(sName, "uint64", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt8Parameter(const std::string & sName, const LibGRPCWrapper_int8 nValue)
{
	addParameter(sName, "int8", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt16Parameter(const std::string & sName, const LibGRPCWrapper_int16 nValue)
{
	addParameter(sName, "int16", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt32Parameter(const std::string & sName, const LibGRPCWrapper_int32 nValue)
{
	addParameter(sName, "uint32", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt64Parameter(const std::string & sName, const LibGRPCWrapper_int64 nValue)
{
	addParameter(sName, "int64", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addSingleParameter(const std::string & sName,  const LibGRPCWrapper_single fValue)
{
	addParameter(sName, "single", std::to_string(fValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addDoubleParameter(const std::string & sName, const LibGRPCWrapper_double dValue)
{
	addParameter(sName, "double", std::to_string(dValue));
}
void CLibGRPCWrapperInterfaceJournalEntry::addPointerParameter(const std::string & sName, const LibGRPCWrapper_pvoid pValue)
{
	addParameter(sName, "pointer", std::to_string(reinterpret_cast<const LibGRPCWrapper_uint64>(pValue)));
}

void CLibGRPCWrapperInterfaceJournalEntry::addStringParameter(const std::string & sName, const char * pValue)
{
	if (pValue != nullptr) {
		addParameter(sName, "string", pValue);
	}
	else {
		addParameter(sName, "nullstring", "");
	}
}

void CLibGRPCWrapperInterfaceJournalEntry::addHandleParameter(const std::string & sName, const LibGRPCWrapperHandle pHandle)
{
	addParameter(sName, "handle", LibGRPCWrapperHandleToHex(pHandle));
}

void CLibGRPCWrapperInterfaceJournalEntry::addEnumParameter(const std::string & sName, const std::string & sEnumType, const LibGRPCWrapper_int32 nValue)
{
	addParameter(sName, "enum" + sEnumType, std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addBooleanResult(const std::string & sName, const bool bValue)
{
	addResult(sName, "bool", std::to_string((int)bValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt8Result(const std::string & sName, const LibGRPCWrapper_uint8 nValue)
{
	addResult(sName, "uint8", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt16Result(const std::string & sName, const LibGRPCWrapper_uint16 nValue)
{
	addResult(sName, "uint16", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt32Result(const std::string & sName, const LibGRPCWrapper_uint32 nValue)
{
	addResult(sName, "uint32", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addUInt64Result(const std::string & sName, const LibGRPCWrapper_uint64 nValue)
{
	addResult(sName, "uint64", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt8Result(const std::string & sName, const LibGRPCWrapper_int8 nValue)
{
	addResult(sName, "int8", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt16Result(const std::string & sName, const LibGRPCWrapper_int16 nValue)
{
	addResult(sName, "int16", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt32Result(const std::string & sName, const LibGRPCWrapper_int32 nValue)
{
	addResult(sName, "uint32", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addInt64Result(const std::string & sName, const LibGRPCWrapper_int64 nValue)
{
	addResult(sName, "int64", std::to_string(nValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addSingleResult(const std::string & sName,  const LibGRPCWrapper_single fValue)
{
	addResult(sName, "single", std::to_string(fValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addDoubleResult(const std::string & sName, const LibGRPCWrapper_double dValue)
{
	addResult(sName, "double", std::to_string(dValue));
}

void CLibGRPCWrapperInterfaceJournalEntry::addPointerResult(const std::string & sName, const LibGRPCWrapper_pvoid pValue)
{
	addResult(sName, "pointer", std::to_string(reinterpret_cast<const LibGRPCWrapper_uint64>(pValue)));
}

void CLibGRPCWrapperInterfaceJournalEntry::addStringResult(const std::string & sName, const char * pValue)
{
	if (pValue != nullptr) {
		addResult(sName, "string", pValue);
	}
	else {
		addResult(sName, "nullstring", "");
	}
}

void CLibGRPCWrapperInterfaceJournalEntry::addHandleResult(const std::string & sName, const LibGRPCWrapperHandle pHandle)
{
	addResult(sName, "handle", LibGRPCWrapperHandleToHex(pHandle));
}

void CLibGRPCWrapperInterfaceJournalEntry::addEnumResult(const std::string & sName, const std::string & sEnumType, const LibGRPCWrapper_int32 nValue)
{
	addResult(sName, "enum" + sEnumType, std::to_string(nValue));
}


CLibGRPCWrapperInterfaceJournal::CLibGRPCWrapperInterfaceJournal (const std::string & sFileName)
	: m_sFileName (sFileName)
{
	m_StartTime = std::chrono::high_resolution_clock::now();
	m_Stream.open (sFileName, std::ios::out);
	m_Stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
	m_Stream << "<journal library=\"LibGRPCWrapper\" version=\"1.2.0\" xmlns=\"http://schemas.autodesk.com/components/LibGRPCWrapper/1.2.0\">\n";
	m_Stream << "\n";

}

CLibGRPCWrapperInterfaceJournal::~CLibGRPCWrapperInterfaceJournal ()
{
	m_Stream << "</journal>\n";
}

PLibGRPCWrapperInterfaceJournalEntry CLibGRPCWrapperInterfaceJournal::beginClassMethod(const LibGRPCWrapperHandle pHandle, const std::string & sClassName, const std::string & sMethodName)
{
	return std::make_shared<CLibGRPCWrapperInterfaceJournalEntry>(this, sClassName, sMethodName, pHandle);
}

PLibGRPCWrapperInterfaceJournalEntry CLibGRPCWrapperInterfaceJournal::beginStaticFunction(const std::string & sMethodName)
{
	return std::make_shared<CLibGRPCWrapperInterfaceJournalEntry>(this, "", sMethodName, nullptr);
}

void CLibGRPCWrapperInterfaceJournal::writeEntry (CLibGRPCWrapperInterfaceJournalEntry * pEntry)
{
	if (pEntry == nullptr)
		throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);

	std::string sXMLString = pEntry->getXMLString();
	m_Mutex.lock();
	try {
		m_Stream << sXMLString;
		m_Stream << "\n";

		m_Mutex.unlock();
	}
	catch (...) {
		m_Mutex.unlock();
	}
}

LibGRPCWrapper_uint64 CLibGRPCWrapperInterfaceJournal::getTimeStamp ()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	if (m_StartTime < currentTime) {
		auto duration = currentTime - m_StartTime;
		auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds> (duration);

		return (LibGRPCWrapper_uint64) milliSeconds.count();
	}
	else {
		return 0;
	}

}
