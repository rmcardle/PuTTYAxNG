/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jan 17 05:56:59 2007
 */
/* Compiler settings for C:\AxTelnetClient\WINDOWS\MSVC\PUTTY\PuttyAx\PuttyAx.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_IPuttyAxObj = {0x716B2BB3,0x55B5,0x4CB8,{0x9E,0x2A,0x27,0x5B,0x29,0xB9,0x82,0xA8}};


const IID LIBID_PUTTYAXLib = {0xB2211620,0x5305,0x4544,{0x85,0xDC,0xA2,0x79,0xD2,0x8D,0xEA,0x12}};


const IID DIID__IPuttyAxObjEvents = {0xE317EEDE,0xB3A3,0x458E,{0xBD,0x1C,0x1D,0xFB,0x97,0x9A,0x87,0x73}};


const CLSID CLSID_PuttyAxObj = {0x5CC7C29A,0x80DB,0x44B9,{0x9A,0x90,0x48,0xEE,0xA3,0x9B,0x47,0x17}};


#ifdef __cplusplus
}
#endif

