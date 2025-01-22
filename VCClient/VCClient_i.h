

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for VCClient.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __VCClient_i_h__
#define __VCClient_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVCClient_FWD_DEFINED__
#define __IVCClient_FWD_DEFINED__
typedef interface IVCClient IVCClient;

#endif 	/* __IVCClient_FWD_DEFINED__ */


#ifndef __IClientClass_FWD_DEFINED__
#define __IClientClass_FWD_DEFINED__
typedef interface IClientClass IClientClass;

#endif 	/* __IClientClass_FWD_DEFINED__ */


#ifndef __VCClient_FWD_DEFINED__
#define __VCClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class VCClient VCClient;
#else
typedef struct VCClient VCClient;
#endif /* __cplusplus */

#endif 	/* __VCClient_FWD_DEFINED__ */


#ifndef __ClientClass_FWD_DEFINED__
#define __ClientClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class ClientClass ClientClass;
#else
typedef struct ClientClass ClientClass;
#endif /* __cplusplus */

#endif 	/* __ClientClass_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __VCClient_LIBRARY_DEFINED__
#define __VCClient_LIBRARY_DEFINED__

/* library VCClient */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_VCClient;

#ifndef __IVCClient_DISPINTERFACE_DEFINED__
#define __IVCClient_DISPINTERFACE_DEFINED__

/* dispinterface IVCClient */
/* [uuid] */ 


EXTERN_C const IID DIID_IVCClient;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A133626C-47D9-4EC8-8185-C7809AC3B6CF")
    IVCClient : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IVCClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVCClient * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVCClient * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVCClient * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVCClient * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVCClient * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVCClient * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVCClient * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IVCClientVtbl;

    interface IVCClient
    {
        CONST_VTBL struct IVCClientVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVCClient_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVCClient_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVCClient_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVCClient_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVCClient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVCClient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVCClient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IVCClient_DISPINTERFACE_DEFINED__ */


#ifndef __IClientClass_INTERFACE_DEFINED__
#define __IClientClass_INTERFACE_DEFINED__

/* interface IClientClass */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IClientClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AEC6AEE8-331B-4234-8AF8-59E20B4C5224")
    IClientClass : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IClientClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IClientClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IClientClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IClientClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IClientClass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IClientClass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IClientClass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IClientClass * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IClientClassVtbl;

    interface IClientClass
    {
        CONST_VTBL struct IClientClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClientClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IClientClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IClientClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IClientClass_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IClientClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IClientClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IClientClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IClientClass_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_VCClient;

#ifdef __cplusplus

class DECLSPEC_UUID("7DED7EB1-4D40-41CF-99BE-A1BA59B47E7A")
VCClient;
#endif

EXTERN_C const CLSID CLSID_ClientClass;

#ifdef __cplusplus

class DECLSPEC_UUID("BF1B54D8-74C8-4D74-8787-2ECC76706A64")
ClientClass;
#endif
#endif /* __VCClient_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


