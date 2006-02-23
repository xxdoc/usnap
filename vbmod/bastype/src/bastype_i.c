/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 23 22:36:43 2006
 */
/* Compiler settings for C:\.lokaj\zbmis\module\bastype\src\bastype.idl:
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

const IID IID_IComparable = {0x3AD5FB90,0x8C80,0x461D,{0x8F,0x18,0xF6,0x57,0x32,0xFC,0xED,0x17}};


const IID IID_IStringizable = {0x99A5A9D2,0x90B9,0x48A6,{0x80,0x5F,0x2D,0x14,0xFE,0xD3,0x23,0x8A}};


const IID IID_IList = {0xC5D3407B,0xD364,0x4328,{0xBC,0x1A,0x3C,0x4C,0xCA,0x63,0x1D,0xDA}};


const IID LIBID_BasTypeLib = {0xA2C5D7B2,0x5074,0x4051,{0x82,0x9C,0x05,0x45,0x54,0xA5,0x21,0x94}};


const CLSID CLSID_List = {0xB4C78A36,0x6E54,0x4E66,{0xA1,0xE9,0x77,0x6E,0x6B,0xA8,0xFB,0x80}};


#ifdef __cplusplus
}
#endif
