

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_VCClient,0xDE9619FD,0x75CD,0x4340,0x99,0xCB,0x56,0x0C,0x72,0xCC,0x23,0xFC);


MIDL_DEFINE_GUID(IID, DIID_IVCClient,0xA133626C,0x47D9,0x4EC8,0x81,0x85,0xC7,0x80,0x9A,0xC3,0xB6,0xCF);


MIDL_DEFINE_GUID(IID, IID_IClientClass,0xAEC6AEE8,0x331B,0x4234,0x8A,0xF8,0x59,0xE2,0x0B,0x4C,0x52,0x24);


MIDL_DEFINE_GUID(CLSID, CLSID_VCClient,0x7DED7EB1,0x4D40,0x41CF,0x99,0xBE,0xA1,0xBA,0x59,0xB4,0x7E,0x7A);


MIDL_DEFINE_GUID(CLSID, CLSID_ClientClass,0xBF1B54D8,0x74C8,0x4D74,0x87,0x87,0x2E,0xCC,0x76,0x70,0x6A,0x64);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



