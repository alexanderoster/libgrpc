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
development of GRPC Library Wrapper. The functions in this file need to be implemented. It needs to be generated only once.

Interface version: 1.2.0

*/

#include "libgrpcwrapper_abi.hpp"
#include "libgrpcwrapper_interfaces.hpp"
#include "libgrpcwrapper_interfaceexception.hpp"
#include "libgrpcwrapper_interfacejournal.hpp"

#include <map>

using namespace LibGRPCWrapper::Impl;

PLibGRPCWrapperInterfaceJournal m_GlobalJournal;

LibGRPCWrapperResult handleLibGRPCWrapperException(IBase * pIBaseClass, ELibGRPCWrapperInterfaceException & Exception, CLibGRPCWrapperInterfaceJournalEntry * pJournalEntry = nullptr)
{
	LibGRPCWrapperResult errorCode = Exception.getErrorCode();

	if (pJournalEntry != nullptr)
		pJournalEntry->writeError(errorCode);

	if (pIBaseClass != nullptr)
		pIBaseClass->RegisterErrorMessage(Exception.what());

	return errorCode;
}

LibGRPCWrapperResult handleStdException(IBase * pIBaseClass, std::exception & Exception, CLibGRPCWrapperInterfaceJournalEntry * pJournalEntry = nullptr)
{
	LibGRPCWrapperResult errorCode = LIBGRPCWRAPPER_ERROR_GENERICEXCEPTION;

	if (pJournalEntry != nullptr)
		pJournalEntry->writeError(errorCode);

	if (pIBaseClass != nullptr)
		pIBaseClass->RegisterErrorMessage(Exception.what());

	return errorCode;
}

LibGRPCWrapperResult handleUnhandledException(IBase * pIBaseClass, CLibGRPCWrapperInterfaceJournalEntry * pJournalEntry = nullptr)
{
	LibGRPCWrapperResult errorCode = LIBGRPCWRAPPER_ERROR_GENERICEXCEPTION;

	if (pJournalEntry != nullptr)
		pJournalEntry->writeError(errorCode);

	if (pIBaseClass != nullptr)
		pIBaseClass->RegisterErrorMessage("Unhandled Exception");

	return errorCode;
}



/*************************************************************************************************************************
 Class implementation for Base
**************************************************************************************************************************/

/*************************************************************************************************************************
 Class implementation for Connection
**************************************************************************************************************************/
LibGRPCWrapperResult libgrpcwrapper_connection_connect(LibGRPCWrapper_Connection pConnection, const char * pNetworkCredentials)
{
	IBase* pIBaseClass = (IBase *)pConnection;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginClassMethod(pConnection, "Connection", "Connect");
			pJournalEntry->addStringParameter("NetworkCredentials", pNetworkCredentials);
		}
		if (pNetworkCredentials == nullptr)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		std::string sNetworkCredentials(pNetworkCredentials);
		IConnection* pIConnection = dynamic_cast<IConnection*>(pIBaseClass);
		if (!pIConnection)
			throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDCAST);
		
		pIConnection->Connect(sNetworkCredentials);

		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

LibGRPCWrapperResult libgrpcwrapper_connection_sendrequest(LibGRPCWrapper_Connection pConnection)
{
	IBase* pIBaseClass = (IBase *)pConnection;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginClassMethod(pConnection, "Connection", "SendRequest");
		}
		IConnection* pIConnection = dynamic_cast<IConnection*>(pIBaseClass);
		if (!pIConnection)
			throw ELibGRPCWrapperInterfaceException(LIBGRPCWRAPPER_ERROR_INVALIDCAST);
		
		pIConnection->SendRequest();

		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}



/*************************************************************************************************************************
 Function table lookup implementation
**************************************************************************************************************************/

LibGRPCWrapperResult LibGRPCWrapper::Impl::LibGRPCWrapper_GetProcAddress (const char * pProcName, void ** ppProcAddress)
{
	if (pProcName == nullptr)
		return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
	if (ppProcAddress == nullptr)
		return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
	*ppProcAddress = nullptr;
	std::string sProcName (pProcName);
	
	if (sProcName == "libgrpcwrapper_connection_connect") 
		*ppProcAddress = (void*) &libgrpcwrapper_connection_connect;
	if (sProcName == "libgrpcwrapper_connection_sendrequest") 
		*ppProcAddress = (void*) &libgrpcwrapper_connection_sendrequest;
	if (sProcName == "libgrpcwrapper_getversion") 
		*ppProcAddress = (void*) &libgrpcwrapper_getversion;
	if (sProcName == "libgrpcwrapper_getlasterror") 
		*ppProcAddress = (void*) &libgrpcwrapper_getlasterror;
	if (sProcName == "libgrpcwrapper_acquireinstance") 
		*ppProcAddress = (void*) &libgrpcwrapper_acquireinstance;
	if (sProcName == "libgrpcwrapper_releaseinstance") 
		*ppProcAddress = (void*) &libgrpcwrapper_releaseinstance;
	if (sProcName == "libgrpcwrapper_getsymbollookupmethod") 
		*ppProcAddress = (void*) &libgrpcwrapper_getsymbollookupmethod;
	if (sProcName == "libgrpcwrapper_createconnection") 
		*ppProcAddress = (void*) &libgrpcwrapper_createconnection;
	
	if (*ppProcAddress == nullptr) 
		return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
	return LIBGRPCWRAPPER_SUCCESS;
}

/*************************************************************************************************************************
 Global functions implementation
**************************************************************************************************************************/
LibGRPCWrapperResult libgrpcwrapper_getversion(LibGRPCWrapper_uint32 * pMajor, LibGRPCWrapper_uint32 * pMinor, LibGRPCWrapper_uint32 * pMicro)
{
	IBase* pIBaseClass = nullptr;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginStaticFunction("GetVersion");
		}
		if (!pMajor)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		if (!pMinor)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		if (!pMicro)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		CWrapper::GetVersion(*pMajor, *pMinor, *pMicro);

		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->addUInt32Result("Major", *pMajor);
			pJournalEntry->addUInt32Result("Minor", *pMinor);
			pJournalEntry->addUInt32Result("Micro", *pMicro);
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

LibGRPCWrapperResult libgrpcwrapper_getlasterror(LibGRPCWrapper_Base pInstance, const LibGRPCWrapper_uint32 nErrorMessageBufferSize, LibGRPCWrapper_uint32* pErrorMessageNeededChars, char * pErrorMessageBuffer, bool * pHasError)
{
	IBase* pIBaseClass = nullptr;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginStaticFunction("GetLastError");
			pJournalEntry->addHandleParameter("Instance", pInstance);
		}
		if ( (!pErrorMessageBuffer) && !(pErrorMessageNeededChars) )
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		if (pHasError == nullptr)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		IBase* pIBaseClassInstance = (IBase *)pInstance;
		IBase* pIInstance = dynamic_cast<IBase*>(pIBaseClassInstance);
		if (!pIInstance)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDCAST);
		
		std::string sErrorMessage("");
		*pHasError = CWrapper::GetLastError(pIInstance, sErrorMessage);

		if (pErrorMessageNeededChars)
			*pErrorMessageNeededChars = (LibGRPCWrapper_uint32) (sErrorMessage.size()+1);
		if (pErrorMessageBuffer) {
			if (sErrorMessage.size() >= nErrorMessageBufferSize)
				throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_BUFFERTOOSMALL);
			for (size_t iErrorMessage = 0; iErrorMessage < sErrorMessage.size(); iErrorMessage++)
				pErrorMessageBuffer[iErrorMessage] = sErrorMessage[iErrorMessage];
			pErrorMessageBuffer[sErrorMessage.size()] = 0;
		}
		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->addStringResult("ErrorMessage", sErrorMessage.c_str());
			pJournalEntry->addBooleanResult("HasError", *pHasError);
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

LibGRPCWrapperResult libgrpcwrapper_acquireinstance(LibGRPCWrapper_Base pInstance)
{
	IBase* pIBaseClass = nullptr;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginStaticFunction("AcquireInstance");
			pJournalEntry->addHandleParameter("Instance", pInstance);
		}
		IBase* pIBaseClassInstance = (IBase *)pInstance;
		IBase* pIInstance = dynamic_cast<IBase*>(pIBaseClassInstance);
		if (!pIInstance)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDCAST);
		
		CWrapper::AcquireInstance(pIInstance);

		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

LibGRPCWrapperResult libgrpcwrapper_releaseinstance(LibGRPCWrapper_Base pInstance)
{
	IBase* pIBaseClass = nullptr;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginStaticFunction("ReleaseInstance");
			pJournalEntry->addHandleParameter("Instance", pInstance);
		}
		IBase* pIBaseClassInstance = (IBase *)pInstance;
		IBase* pIInstance = dynamic_cast<IBase*>(pIBaseClassInstance);
		if (!pIInstance)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDCAST);
		
		CWrapper::ReleaseInstance(pIInstance);

		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

LibGRPCWrapperResult libgrpcwrapper_getsymbollookupmethod(LibGRPCWrapper_pvoid * pSymbolLookupMethod)
{
	IBase* pIBaseClass = nullptr;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginStaticFunction("GetSymbolLookupMethod");
		}
		if (pSymbolLookupMethod == nullptr)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		*pSymbolLookupMethod = (void*)&LibGRPCWrapper::Impl::LibGRPCWrapper_GetProcAddress;
		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->addPointerResult("SymbolLookupMethod", *pSymbolLookupMethod);
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

LibGRPCWrapperResult libgrpcwrapper_createconnection(const char * pProtobufDefinition, LibGRPCWrapper_Connection * pConnectionInstance)
{
	IBase* pIBaseClass = nullptr;

	PLibGRPCWrapperInterfaceJournalEntry pJournalEntry;
	try {
		if (m_GlobalJournal.get() != nullptr)  {
			pJournalEntry = m_GlobalJournal->beginStaticFunction("CreateConnection");
			pJournalEntry->addStringParameter("ProtobufDefinition", pProtobufDefinition);
		}
		if (pProtobufDefinition == nullptr)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		if (pConnectionInstance == nullptr)
			throw ELibGRPCWrapperInterfaceException (LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		std::string sProtobufDefinition(pProtobufDefinition);
		IBase* pBaseConnectionInstance(nullptr);
		pBaseConnectionInstance = CWrapper::CreateConnection(sProtobufDefinition);

		*pConnectionInstance = (IBase*)(pBaseConnectionInstance);
		if (pJournalEntry.get() != nullptr) {
			pJournalEntry->addHandleResult("ConnectionInstance", *pConnectionInstance);
			pJournalEntry->writeSuccess();
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	catch (ELibGRPCWrapperInterfaceException & Exception) {
		return handleLibGRPCWrapperException(pIBaseClass, Exception, pJournalEntry.get());
	}
	catch (std::exception & StdException) {
		return handleStdException(pIBaseClass, StdException, pJournalEntry.get());
	}
	catch (...) {
		return handleUnhandledException(pIBaseClass, pJournalEntry.get());
	}
}

