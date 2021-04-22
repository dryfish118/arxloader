#ifndef __INETSTRC_H
#define __INETSTRC_H 

#include "TD_PackPush.h"

namespace OdInet
{
  const int StatusBase = 20000;
  enum Status
  {
    statusOk = StatusBase,
    statusInCache,

    statusFileNotFound,			
    statusBadPath,					
    statusTooManyOpenFiles,	
    statusFileAccessDenied,	
    statusInvalidFileHandle,
    statusDirectoryFull,		
    statusHardwareError,		
    statusSharingViolation,	
    statusDiskFull,					
    statusFileGenericError,	

    statusValidURL,
    statusNotAnURL,						
    statusNoWinInet,					
    statusOldWinInet,					
    statusNoAcadInet,					
    statusNotImplemented,			
    statusProtocolNotSupported,

    statusCreateInternetSessionFailed,
    statusInternetSessionConnectFailed,
    statusInternetSessionOpenFailed,

    statusInvalidAccessType,			
    statusFileOpenFailed,					
    statusHttpOpenRequestFailed,	
    statusUserCancelledTransfer,

    statusHttpBadRequest,					
    statusHttpAccessDenied,				
    statusHttpPaymentRequired,		
    statusHttpRequestForbidden,		
    statusHttpObjectNotFound,			
    statusHttpBadMethod,					
    statusHttpNoAcceptableResponse,	
    statusHttpProxyAuthorizationRequired,	
    statusHttpTimedOut,						
    statusHttpConflict,						
    statusHttpResourceGone,				
    statusHttpLengthRequired,			
    statusHttpPreconditionFailure,
    statusHttpRequestTooLarge,		
    statusHttpUriTooLong,					
    statusHttpUnsupportedMedia,		

    statusHttpServerError,
    statusHttpNotSupported,
    statusHttpBadGateway,
    statusHttpServiceUnavailable,
    statusHttpGatewayTimeout,
    statusHttpVersionNotSupported,

    statusInternetError,

    statusGenericException,

    statusUnknownError
  };
}

namespace OdInet
{
  enum
  {
    TF_VALIDATE_URL = 0x01,
    TF_DOWNLOAD_FILE = 0x02,
    TF_UPLOAD_FILE = 0x04,
    TF_IGNORE_CACHE = 0x08
  };
}

#include "TD_PackPop.h"
#endif