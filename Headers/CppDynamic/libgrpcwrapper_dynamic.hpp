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

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of GRPC Library Wrapper

Interface version: 1.2.0

*/

#ifndef __LIBGRPCWRAPPER_CPPHEADER_DYNAMIC_CPP
#define __LIBGRPCWRAPPER_CPPHEADER_DYNAMIC_CPP

#include "libgrpcwrapper_types.hpp"
#include "libgrpcwrapper_dynamic.h"


#ifdef _WIN32
#include <windows.h>
#else // _WIN32
#include <dlfcn.h>
#endif // _WIN32
#include <string>
#include <memory>
#include <vector>
#include <exception>

namespace LibGRPCWrapper {

/*************************************************************************************************************************
 Forward Declaration of all classes
**************************************************************************************************************************/
class CWrapper;
class CBase;
class CConnection;

/*************************************************************************************************************************
 Declaration of deprecated class types
**************************************************************************************************************************/
typedef CWrapper CLibGRPCWrapperWrapper;
typedef CBase CLibGRPCWrapperBase;
typedef CConnection CLibGRPCWrapperConnection;

/*************************************************************************************************************************
 Declaration of shared pointer types
**************************************************************************************************************************/
typedef std::shared_ptr<CWrapper> PWrapper;
typedef std::shared_ptr<CBase> PBase;
typedef std::shared_ptr<CConnection> PConnection;

/*************************************************************************************************************************
 Declaration of deprecated shared pointer types
**************************************************************************************************************************/
typedef PWrapper PLibGRPCWrapperWrapper;
typedef PBase PLibGRPCWrapperBase;
typedef PConnection PLibGRPCWrapperConnection;


/*************************************************************************************************************************
 classParam Definition
**************************************************************************************************************************/

template<class T> class classParam {
private:
	const T* m_ptr;

public:
	classParam(const T* ptr)
		: m_ptr (ptr)
	{
	}

	classParam(std::shared_ptr <T> sharedPtr)
		: m_ptr (sharedPtr.get())
	{
	}

	LibGRPCWrapperHandle GetHandle()
	{
		if (m_ptr != nullptr)
			return m_ptr->handle();
		return nullptr;
	}
};

/*************************************************************************************************************************
 Class ELibGRPCWrapperException 
**************************************************************************************************************************/
class ELibGRPCWrapperException : public std::exception {
protected:
	/**
	* Error code for the Exception.
	*/
	LibGRPCWrapperResult m_errorCode;
	/**
	* Error message for the Exception.
	*/
	std::string m_errorMessage;
	std::string m_originalErrorMessage;

public:
	/**
	* Exception Constructor.
	*/
	ELibGRPCWrapperException(LibGRPCWrapperResult errorCode, const std::string & sErrorMessage)
		: m_errorCode(errorCode), m_originalErrorMessage(sErrorMessage)
	{
		m_errorMessage = buildErrorMessage();
	}

	/**
	* Returns error code
	*/
	LibGRPCWrapperResult getErrorCode() const noexcept
	{
		return m_errorCode;
	}

	/**
	* Returns error message
	*/
	const char* what() const noexcept
	{
		return m_errorMessage.c_str();
	}

	const char* getErrorMessage() const noexcept
	{
		return m_originalErrorMessage.c_str();
	}

	const char* getErrorName() const noexcept
	{
		switch(getErrorCode()) {
			case LIBGRPCWRAPPER_SUCCESS: return "SUCCESS";
			case LIBGRPCWRAPPER_ERROR_NOTIMPLEMENTED: return "NOTIMPLEMENTED";
			case LIBGRPCWRAPPER_ERROR_INVALIDPARAM: return "INVALIDPARAM";
			case LIBGRPCWRAPPER_ERROR_INVALIDCAST: return "INVALIDCAST";
			case LIBGRPCWRAPPER_ERROR_BUFFERTOOSMALL: return "BUFFERTOOSMALL";
			case LIBGRPCWRAPPER_ERROR_GENERICEXCEPTION: return "GENERICEXCEPTION";
			case LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY: return "COULDNOTLOADLIBRARY";
			case LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT: return "COULDNOTFINDLIBRARYEXPORT";
			case LIBGRPCWRAPPER_ERROR_INCOMPATIBLEBINARYVERSION: return "INCOMPATIBLEBINARYVERSION";
			case LIBGRPCWRAPPER_ERROR_NOTCONNECTED: return "NOTCONNECTED";
		}
		return "UNKNOWN";
	}

	const char* getErrorDescription() const noexcept
	{
		switch(getErrorCode()) {
			case LIBGRPCWRAPPER_SUCCESS: return "success";
			case LIBGRPCWRAPPER_ERROR_NOTIMPLEMENTED: return "functionality not implemented";
			case LIBGRPCWRAPPER_ERROR_INVALIDPARAM: return "an invalid parameter was passed";
			case LIBGRPCWRAPPER_ERROR_INVALIDCAST: return "a type cast failed";
			case LIBGRPCWRAPPER_ERROR_BUFFERTOOSMALL: return "a provided buffer is too small";
			case LIBGRPCWRAPPER_ERROR_GENERICEXCEPTION: return "a generic exception occurred";
			case LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY: return "the library could not be loaded";
			case LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT: return "a required exported symbol could not be found in the library";
			case LIBGRPCWRAPPER_ERROR_INCOMPATIBLEBINARYVERSION: return "the version of the binary interface does not match the bindings interface";
			case LIBGRPCWRAPPER_ERROR_NOTCONNECTED: return "PLC is not connected";
		}
		return "unknown error";
	}

private:

	std::string buildErrorMessage() const noexcept
	{
		std::string msg = m_originalErrorMessage;
		if (msg.empty()) {
			msg = getErrorDescription();
		}
		return std::string("Error: ") + getErrorName() + ": " + msg;
	}
};

/*************************************************************************************************************************
 Class CInputVector
**************************************************************************************************************************/
template <typename T>
class CInputVector {
private:
	
	const T* m_data;
	size_t m_size;
	
public:
	
	CInputVector(const std::vector<T>& vec)
		: m_data( vec.data() ), m_size( vec.size() )
	{
	}
	
	CInputVector(const T* in_data, size_t in_size)
		: m_data( in_data ), m_size(in_size )
	{
	}
	
	const T* data() const
	{
		return m_data;
	}
	
	size_t size() const
	{
		return m_size;
	}
	
};

// declare deprecated class name
template<typename T>
using CLibGRPCWrapperInputVector = CInputVector<T>;

/*************************************************************************************************************************
 Class CWrapper 
**************************************************************************************************************************/
class CWrapper {
public:
	
	explicit CWrapper(void* pSymbolLookupMethod)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTableFromSymbolLookupMethod(&m_WrapperTable, pSymbolLookupMethod));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	explicit CWrapper(const std::string &sFileName)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTable(&m_WrapperTable, sFileName.c_str()));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	static PWrapper loadLibrary(const std::string &sFileName)
	{
		return std::make_shared<CWrapper>(sFileName);
	}
	
	static PWrapper loadLibraryFromSymbolLookupMethod(void* pSymbolLookupMethod)
	{
		return std::make_shared<CWrapper>(pSymbolLookupMethod);
	}
	
	~CWrapper()
	{
		releaseWrapperTable(&m_WrapperTable);
	}
	
	inline void CheckError(CBase * pBaseClass, LibGRPCWrapperResult nResult);

	inline void GetVersion(LibGRPCWrapper_uint32 & nMajor, LibGRPCWrapper_uint32 & nMinor, LibGRPCWrapper_uint32 & nMicro);
	inline bool GetLastError(classParam<CBase> pInstance, std::string & sErrorMessage);
	inline void AcquireInstance(classParam<CBase> pInstance);
	inline void ReleaseInstance(classParam<CBase> pInstance);
	inline LibGRPCWrapper_pvoid GetSymbolLookupMethod();
	inline PConnection CreateConnection(const std::string & sProtobufDefinition);

private:
	sLibGRPCWrapperDynamicWrapperTable m_WrapperTable;
	
	LibGRPCWrapperResult checkBinaryVersion()
	{
		LibGRPCWrapper_uint32 nMajor, nMinor, nMicro;
		GetVersion(nMajor, nMinor, nMicro);
		if ( (nMajor != LIBGRPCWRAPPER_VERSION_MAJOR) || (nMinor < LIBGRPCWRAPPER_VERSION_MINOR) ) {
			return LIBGRPCWRAPPER_ERROR_INCOMPATIBLEBINARYVERSION;
		}
		return LIBGRPCWRAPPER_SUCCESS;
	}
	LibGRPCWrapperResult initWrapperTable(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable);
	LibGRPCWrapperResult releaseWrapperTable(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable);
	LibGRPCWrapperResult loadWrapperTable(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName);
	LibGRPCWrapperResult loadWrapperTableFromSymbolLookupMethod(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable, void* pSymbolLookupMethod);

	friend class CBase;
	friend class CConnection;

};

	
/*************************************************************************************************************************
 Class CBase 
**************************************************************************************************************************/
class CBase {
public:
	
protected:
	/* Wrapper Object that created the class. */
	CWrapper * m_pWrapper;
	/* Handle to Instance in library*/
	LibGRPCWrapperHandle m_pHandle;

	/* Checks for an Error code and raises Exceptions */
	void CheckError(LibGRPCWrapperResult nResult)
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->CheckError(this, nResult);
	}
public:
	/**
	* CBase::CBase - Constructor for Base class.
	*/
	CBase(CWrapper * pWrapper, LibGRPCWrapperHandle pHandle)
		: m_pWrapper(pWrapper), m_pHandle(pHandle)
	{
	}

	/**
	* CBase::~CBase - Destructor for Base class.
	*/
	virtual ~CBase()
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->ReleaseInstance(this);
		m_pWrapper = nullptr;
	}

	/**
	* CBase::handle - Returns handle to instance.
	*/
	LibGRPCWrapperHandle handle() const
	{
		return m_pHandle;
	}

	/**
	* CBase::wrapper - Returns wrapper instance.
	*/
	CWrapper * wrapper() const
	{
		return m_pWrapper;
	}
	
	friend class CWrapper;
};
	
/*************************************************************************************************************************
 Class CConnection 
**************************************************************************************************************************/
class CConnection : public CBase {
public:
	
	/**
	* CConnection::CConnection - Constructor for Connection class.
	*/
	CConnection(CWrapper* pWrapper, LibGRPCWrapperHandle pHandle)
		: CBase(pWrapper, pHandle)
	{
	}
	
	inline void Connect(const std::string & sNetworkCredentials);
	inline void SendRequest();
};
	
	/**
	* CWrapper::GetVersion - retrieves the binary version of this library.
	* @param[out] nMajor - returns the major version of this library
	* @param[out] nMinor - returns the minor version of this library
	* @param[out] nMicro - returns the micro version of this library
	*/
	inline void CWrapper::GetVersion(LibGRPCWrapper_uint32 & nMajor, LibGRPCWrapper_uint32 & nMinor, LibGRPCWrapper_uint32 & nMicro)
	{
		CheckError(nullptr,m_WrapperTable.m_GetVersion(&nMajor, &nMinor, &nMicro));
	}
	
	/**
	* CWrapper::GetLastError - Returns the last error recorded on this object
	* @param[in] pInstance - Instance Handle
	* @param[out] sErrorMessage - Message of the last error
	* @return Is there a last error to query
	*/
	inline bool CWrapper::GetLastError(classParam<CBase> pInstance, std::string & sErrorMessage)
	{
		LibGRPCWrapperHandle hInstance = pInstance.GetHandle();
		LibGRPCWrapper_uint32 bytesNeededErrorMessage = 0;
		LibGRPCWrapper_uint32 bytesWrittenErrorMessage = 0;
		bool resultHasError = 0;
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, 0, &bytesNeededErrorMessage, nullptr, &resultHasError));
		std::vector<char> bufferErrorMessage(bytesNeededErrorMessage);
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, bytesNeededErrorMessage, &bytesWrittenErrorMessage, &bufferErrorMessage[0], &resultHasError));
		sErrorMessage = std::string(&bufferErrorMessage[0]);
		
		return resultHasError;
	}
	
	/**
	* CWrapper::AcquireInstance - Acquire shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::AcquireInstance(classParam<CBase> pInstance)
	{
		LibGRPCWrapperHandle hInstance = pInstance.GetHandle();
		CheckError(nullptr,m_WrapperTable.m_AcquireInstance(hInstance));
	}
	
	/**
	* CWrapper::ReleaseInstance - Releases shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::ReleaseInstance(classParam<CBase> pInstance)
	{
		LibGRPCWrapperHandle hInstance = pInstance.GetHandle();
		CheckError(nullptr,m_WrapperTable.m_ReleaseInstance(hInstance));
	}
	
	/**
	* CWrapper::GetSymbolLookupMethod - Returns the address of the SymbolLookupMethod
	* @return Address of the SymbolAddressMethod
	*/
	inline LibGRPCWrapper_pvoid CWrapper::GetSymbolLookupMethod()
	{
		LibGRPCWrapper_pvoid resultSymbolLookupMethod = 0;
		CheckError(nullptr,m_WrapperTable.m_GetSymbolLookupMethod(&resultSymbolLookupMethod));
		
		return resultSymbolLookupMethod;
	}
	
	/**
	* CWrapper::CreateConnection - Returns a PLC instance
	* @param[in] sProtobufDefinition - String containing the proto definition
	* @return Connection Instance
	*/
	inline PConnection CWrapper::CreateConnection(const std::string & sProtobufDefinition)
	{
		LibGRPCWrapperHandle hConnectionInstance = nullptr;
		CheckError(nullptr,m_WrapperTable.m_CreateConnection(sProtobufDefinition.c_str(), &hConnectionInstance));
		
		if (!hConnectionInstance) {
			CheckError(nullptr,LIBGRPCWRAPPER_ERROR_INVALIDPARAM);
		}
		return std::make_shared<CConnection>(this, hConnectionInstance);
	}
	
	inline void CWrapper::CheckError(CBase * pBaseClass, LibGRPCWrapperResult nResult)
	{
		if (nResult != 0) {
			std::string sErrorMessage;
			if (pBaseClass != nullptr) {
				GetLastError(pBaseClass, sErrorMessage);
			}
			throw ELibGRPCWrapperException(nResult, sErrorMessage);
		}
	}
	

	inline LibGRPCWrapperResult CWrapper::initWrapperTable(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
		
		pWrapperTable->m_LibraryHandle = nullptr;
		pWrapperTable->m_Connection_Connect = nullptr;
		pWrapperTable->m_Connection_SendRequest = nullptr;
		pWrapperTable->m_GetVersion = nullptr;
		pWrapperTable->m_GetLastError = nullptr;
		pWrapperTable->m_AcquireInstance = nullptr;
		pWrapperTable->m_ReleaseInstance = nullptr;
		pWrapperTable->m_GetSymbolLookupMethod = nullptr;
		pWrapperTable->m_CreateConnection = nullptr;
		
		return LIBGRPCWRAPPER_SUCCESS;
	}

	inline LibGRPCWrapperResult CWrapper::releaseWrapperTable(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
		
		if (pWrapperTable->m_LibraryHandle != nullptr) {
		#ifdef _WIN32
			HMODULE hModule = (HMODULE) pWrapperTable->m_LibraryHandle;
			FreeLibrary(hModule);
		#else // _WIN32
			dlclose(pWrapperTable->m_LibraryHandle);
		#endif // _WIN32
			return initWrapperTable(pWrapperTable);
		}
		
		return LIBGRPCWRAPPER_SUCCESS;
	}

	inline LibGRPCWrapperResult CWrapper::loadWrapperTable(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName)
	{
		if (pWrapperTable == nullptr)
			return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
		if (pLibraryFileName == nullptr)
			return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
		
		#ifdef _WIN32
		// Convert filename to UTF16-string
		int nLength = 0;
		while ((pLibraryFileName[nLength] != 0) && (nLength < MAX_PATH))
			nLength++;
		int nBufferSize = nLength * 2 + 2;
		std::vector<wchar_t> wsLibraryFileName(nBufferSize);
		int nResult = MultiByteToWideChar(CP_UTF8, 0, pLibraryFileName, nLength, &wsLibraryFileName[0], nBufferSize);
		if (nResult == 0)
			return LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY;
		
		HMODULE hLibrary = LoadLibraryW(wsLibraryFileName.data());
		if (hLibrary == 0) 
			return LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY;
		#else // _WIN32
		void* hLibrary = dlopen(pLibraryFileName, RTLD_LAZY);
		if (hLibrary == 0) 
			return LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY;
		dlerror();
		#endif // _WIN32
		
		#ifdef _WIN32
		pWrapperTable->m_Connection_Connect = (PLibGRPCWrapperConnection_ConnectPtr) GetProcAddress(hLibrary, "libgrpcwrapper_connection_connect");
		#else // _WIN32
		pWrapperTable->m_Connection_Connect = (PLibGRPCWrapperConnection_ConnectPtr) dlsym(hLibrary, "libgrpcwrapper_connection_connect");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_Connection_Connect == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_Connection_SendRequest = (PLibGRPCWrapperConnection_SendRequestPtr) GetProcAddress(hLibrary, "libgrpcwrapper_connection_sendrequest");
		#else // _WIN32
		pWrapperTable->m_Connection_SendRequest = (PLibGRPCWrapperConnection_SendRequestPtr) dlsym(hLibrary, "libgrpcwrapper_connection_sendrequest");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_Connection_SendRequest == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetVersion = (PLibGRPCWrapperGetVersionPtr) GetProcAddress(hLibrary, "libgrpcwrapper_getversion");
		#else // _WIN32
		pWrapperTable->m_GetVersion = (PLibGRPCWrapperGetVersionPtr) dlsym(hLibrary, "libgrpcwrapper_getversion");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetVersion == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetLastError = (PLibGRPCWrapperGetLastErrorPtr) GetProcAddress(hLibrary, "libgrpcwrapper_getlasterror");
		#else // _WIN32
		pWrapperTable->m_GetLastError = (PLibGRPCWrapperGetLastErrorPtr) dlsym(hLibrary, "libgrpcwrapper_getlasterror");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetLastError == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_AcquireInstance = (PLibGRPCWrapperAcquireInstancePtr) GetProcAddress(hLibrary, "libgrpcwrapper_acquireinstance");
		#else // _WIN32
		pWrapperTable->m_AcquireInstance = (PLibGRPCWrapperAcquireInstancePtr) dlsym(hLibrary, "libgrpcwrapper_acquireinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_AcquireInstance == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_ReleaseInstance = (PLibGRPCWrapperReleaseInstancePtr) GetProcAddress(hLibrary, "libgrpcwrapper_releaseinstance");
		#else // _WIN32
		pWrapperTable->m_ReleaseInstance = (PLibGRPCWrapperReleaseInstancePtr) dlsym(hLibrary, "libgrpcwrapper_releaseinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_ReleaseInstance == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetSymbolLookupMethod = (PLibGRPCWrapperGetSymbolLookupMethodPtr) GetProcAddress(hLibrary, "libgrpcwrapper_getsymbollookupmethod");
		#else // _WIN32
		pWrapperTable->m_GetSymbolLookupMethod = (PLibGRPCWrapperGetSymbolLookupMethodPtr) dlsym(hLibrary, "libgrpcwrapper_getsymbollookupmethod");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetSymbolLookupMethod == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_CreateConnection = (PLibGRPCWrapperCreateConnectionPtr) GetProcAddress(hLibrary, "libgrpcwrapper_createconnection");
		#else // _WIN32
		pWrapperTable->m_CreateConnection = (PLibGRPCWrapperCreateConnectionPtr) dlsym(hLibrary, "libgrpcwrapper_createconnection");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_CreateConnection == nullptr)
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		pWrapperTable->m_LibraryHandle = hLibrary;
		return LIBGRPCWRAPPER_SUCCESS;
	}

	inline LibGRPCWrapperResult CWrapper::loadWrapperTableFromSymbolLookupMethod(sLibGRPCWrapperDynamicWrapperTable * pWrapperTable, void* pSymbolLookupMethod)
{
		if (pWrapperTable == nullptr)
			return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
		if (pSymbolLookupMethod == nullptr)
			return LIBGRPCWRAPPER_ERROR_INVALIDPARAM;
		
		typedef LibGRPCWrapperResult(*SymbolLookupType)(const char*, void**);
		
		SymbolLookupType pLookup = (SymbolLookupType)pSymbolLookupMethod;
		
		LibGRPCWrapperResult eLookupError = LIBGRPCWRAPPER_SUCCESS;
		eLookupError = (*pLookup)("libgrpcwrapper_connection_connect", (void**)&(pWrapperTable->m_Connection_Connect));
		if ( (eLookupError != 0) || (pWrapperTable->m_Connection_Connect == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_connection_sendrequest", (void**)&(pWrapperTable->m_Connection_SendRequest));
		if ( (eLookupError != 0) || (pWrapperTable->m_Connection_SendRequest == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_getversion", (void**)&(pWrapperTable->m_GetVersion));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetVersion == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_getlasterror", (void**)&(pWrapperTable->m_GetLastError));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetLastError == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_acquireinstance", (void**)&(pWrapperTable->m_AcquireInstance));
		if ( (eLookupError != 0) || (pWrapperTable->m_AcquireInstance == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_releaseinstance", (void**)&(pWrapperTable->m_ReleaseInstance));
		if ( (eLookupError != 0) || (pWrapperTable->m_ReleaseInstance == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_getsymbollookupmethod", (void**)&(pWrapperTable->m_GetSymbolLookupMethod));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetSymbolLookupMethod == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("libgrpcwrapper_createconnection", (void**)&(pWrapperTable->m_CreateConnection));
		if ( (eLookupError != 0) || (pWrapperTable->m_CreateConnection == nullptr) )
			return LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		return LIBGRPCWRAPPER_SUCCESS;
}

	
	
	/**
	 * Method definitions for class CBase
	 */
	
	/**
	 * Method definitions for class CConnection
	 */
	
	/**
	* CConnection::Connect - Connects to an end point
	* @param[in] sNetworkCredentials - Host to connect to
	*/
	void CConnection::Connect(const std::string & sNetworkCredentials)
	{
		CheckError(m_pWrapper->m_WrapperTable.m_Connection_Connect(m_pHandle, sNetworkCredentials.c_str()));
	}
	
	/**
	* CConnection::SendRequest - Send a request
	*/
	void CConnection::SendRequest()
	{
		CheckError(m_pWrapper->m_WrapperTable.m_Connection_SendRequest(m_pHandle));
	}

} // namespace LibGRPCWrapper

#endif // __LIBGRPCWRAPPER_CPPHEADER_DYNAMIC_CPP

