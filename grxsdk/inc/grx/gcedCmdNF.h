#pragma once

#include "gcedinpt.h"
#include "gcdocman.h"

#ifdef __cplusplus
    extern "C" {
#endif
#pragma pack (push, 8)

GCAP_DLL_DECL bool gcedFiberWorld();
GCAP_DLL_DECL int gcedCommandS(int rtype, ...);
class GcApDocument;

GCAP_DLL_DECL int gcedCmdS(const resbuf*       rb,
               bool          forFutureUse  = false,
               GcApDocument* pForFutureUse = NULL);

typedef int (*GcEdCoroutineCallback)(void* pData);

GCAP_DLL_DECL int gcedCommandC(GcEdCoroutineCallback pCallback,
                           void* pReturnFcnParms,
                           int rtype, ...);
GCAP_DLL_DECL int gcedCmdC(GcEdCoroutineCallback pCallback,
                       void* pReturnFcnParms,
                       const struct resbuf *rb);
    
GCAP_DLL_DECL bool gcedPendingCmdCTokens();

GCAP_DLL_DECL bool gcedResumingInvocation();

GCAP_DLL_DECL void gcedCallBackOnCancel();

GCAP_DLL_DECL bool gcedCmdCWasCancelled();

#pragma pack (pop)
#ifdef __cplusplus
    }
#endif  /* __cplusplus */

GCAP_DLL_DECL bool gcedPendingFiberlessDocSwitch(GcApDocument** pNextActiveDocument = NULL);
