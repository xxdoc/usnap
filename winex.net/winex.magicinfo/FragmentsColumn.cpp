// FragmentsColumn.cpp : Implementation of CFragmentsColumn

#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include "FragmentsColumn.h"


GUID FMTID_Fragments = { 0x893c63b0, 0xb0e1, 0x43ea, { 0x85, 0x8b, 0xc1, 0x25, 0xa0, 0x3d, 0xc8, 0x29 } };

// CFragmentsColumn

// IColumnProvider

static void alert(LPCTSTR format, ...) {
	va_list args;
	va_start(args, format); 

	TCHAR buf[1000];
	_vstprintf_s(buf, ARRAYSIZE(buf), format, args); 
	MessageBox(NULL, buf, _T("alert"), 0); 
}

static int satBlockSize(int size) {
	if (size < 1)
		return 1; 
	if (size > MAXBLOCK)
		return MAXBLOCK; 
	return size; 
}

static LPCTSTR startsWith(LPCTSTR str, LPCTSTR pattern) {
	int plen = lstrlen(pattern); 
	if (_tcsncmp(str, pattern, plen) == 0)
		return str + plen; 
	return NULL; 
}

size_t readFile(LPCTSTR path, void *buf, int start, int len) {
	int atFoot = len < 0; 
	if (atFoot) len = -len; 
	FILE *file = NULL; 
	errno_t err = _tfopen_s(&file, path, _T("rb")); 
	if (err != 0)
		return -1; 
	size_t cbread; 
	if (atFoot)
		fseek(file, -len, SEEK_END);
	cbread = fread(buf, 1, len, file); 
	fclose(file); 
	return cbread; 
}

STDMETHODIMP
CFragmentsColumn::Initialize(LPCSHCOLUMNINIT psci) {
	// alert(_T("Initialize")); 
	HKEY hk; 
	LONG err; 
	err = RegCreateKey(HKEY_CURRENT_USER, TEXT("ns\\winex\\winex.magicinfo\\winex.magicinfo.FragmentsColumn"), &hk); 
	if (err != ERROR_SUCCESS)
		return S_FALSE; 

	for (int valIndex = 0; ; valIndex++) {
		TCHAR valName[100];
		BYTE  valBuf[2000];
		DWORD valType; 
		DWORD ccName = ARRAYSIZE(valName); 
		DWORD cbBuf = sizeof(valBuf); 
		err = RegEnumValue(hk, valIndex, valName, &ccName, NULL, &valType, valBuf, &cbBuf); 
		if (err != ERROR_SUCCESS) // ERROR_NO_MORE_ITEMS
			break; 
		
		LPCTSTR suffix; 
		if (lstrcmpi(valName, _T("headerSize")) == 0)
			m_headerSize = satBlockSize(*(int *) valBuf); 
		else if (lstrcmpi(valName, _T("footerSize")) == 0)
			m_footerSize = satBlockSize(*(int *) valBuf);
		else if (suffix = startsWith(valName, _T("title_"))) {
			int pid = (int) _tcstol(suffix, NULL, 10);
			lstrcpy(m_titles[pid], (LPCTSTR) valBuf); 
		} else if (suffix = startsWith(valName, _T("magic_"))) {
			TCHAR *end = (TCHAR *) (valBuf + cbBuf); 
			int half = 0;
			BYTE byt; 
			BYTE *pbuf = NULL;
			int *plen = NULL; 
			for (TCHAR *p = (TCHAR *) valBuf; p < end && *p; p++) {
				switch (*p) {
					case _T('$'): 
						plen = &footerMaskLen[m_magics];
						pbuf = footerMask[m_magics];
						continue; 
					case _T('^'): 
						plen = &headerMaskLen[m_magics];
						pbuf = headerMask[m_magics];
						continue; 
				}
				TCHAR c = *p;
				int d; 
				if (c >= '0' && c <= '9')
					d = c - '0'; 
				else if (c >= 'a' && c <= 'f')
					d = c - 'a' + 10;
				else if (c >= 'A' && c <= 'F')
					d = c - 'A' + 10; 
				else
					continue;
				if (half) {
					*pbuf++ = (byt << 4) | d;
					half = 0; 
					++*plen;
				} else {
					byt = d; 
					half = 1; 
				}
			} // while p<end
			flagChars[m_magics++] = _tcsdup(suffix);
		} // if valName = ...
	} // for valIndex
	RegCloseKey(hk); 
	return S_OK; 
}

STDMETHODIMP
CFragmentsColumn::GetColumnInfo(DWORD dwIndex, SHCOLUMNINFO *psci) {
	// alert(_T("GetColumnInfo(%d)"), dwIndex); 
	
	// scid, vt, fmt, cChars, csFlags, wszTitle, wszDescription
	// {{0}, VT_BSTR, LVCFMT_LEFT, 30, SHCOLSTATE_TYPE_STR | SHCOLSTATE_SECONDARYUI, TEXT("Short Filename"), TEXT("Displays the 8.3 filename.")},
	SHCOLUMNINFO sci; 
	sci.scid.fmtid = FMTID_Fragments;
	sci.scid.pid = dwIndex;
	sci.vt = VT_BSTR; 
	sci.fmt = LVCFMT_LEFT;
	sci.cChars = 16; 
	sci.csFlags = SHCOLSTATE_TYPE_STR | SHCOLSTATE_SECONDARYUI;
	TCHAR *title = NULL; 
	TCHAR *description = NULL; 

	switch (dwIndex) {
		case 0: 
			description = TEXT("File header bytes"); 
			break; 
		case 1: 
			description = TEXT("File footer bytes"); 
			break;
		case 2: 
			description = TEXT("Magic Attributes"); 
			sci.cChars = 30; 
			sci.csFlags &= ~SHCOLSTATE_SECONDARYUI;
			break;
		default: 
			return S_FALSE; 
	}
	psci->scid = sci.scid;
	psci->vt = sci.vt;
	psci->fmt = sci.fmt;
	psci->cChars = sci.cChars;
	psci->csFlags = sci.csFlags;
	if (!title)
		title = m_titles[dwIndex]; 
	lstrcpyn(psci->wszTitle, title, ARRAYSIZE(psci->wszTitle)); 
	if (description)
		lstrcpyn(psci->wszDescription, description, ARRAYSIZE(psci->wszDescription)); 
	return S_OK; 
}

STDMETHODIMP
CFragmentsColumn::GetItemData(LPCSHCOLUMNID pscid, LPCSHCOLUMNDATA pscd, VARIANT *pvarData) {
	if (!IsEqualFMTID(pscid->fmtid, FMTID_Fragments))
		return S_FALSE; 
	
	LPCTSTR path = CW2CT(pscd->wszFile); 
	struct _stat32 stat; 
	_tstat32(path, &stat); 
	if (stat.st_mode & _S_IFDIR) { // isdir
		pvarData->vt = VT_BSTR; 
		pvarData->bstrVal = SysAllocString(L"<dir>"); 
		return S_OK; 
	}

	// alert(_T("GetItemData(%d)/%s"), pscid->pid, path); 

	char buf[MAXBLOCK]; 
	TCHAR flags[MAX_MAGICS + 1];
	size_t cbread; 
	switch (pscid->pid) {
		case 0: // header
			cbread = readFile(path, buf, 0, m_headerSize); 
			break;
		case 1: // footer
			cbread = readFile(path, buf, 0, -m_footerSize); 
			break;

		case 2: // magic
			flags[0] = TEXT('\0'); 
			for (int i = 0; i < m_magics; i++) {
				int len;
				int match = 0; 
				if (len = headerMaskLen[i]) {
					readFile(path, buf, 0, len); 
					buf[len] = 0;	
					if (memcmp(buf, headerMask[i], len) != 0)
						continue; 
					match++;
				}
				if (len = footerMaskLen[i]) {
					readFile(path, buf, 0, -len); 
					buf[len] = 0;
					// alert(_T("foot of %s = [%s]"), path, buf); 
					if (memcmp(buf, footerMask[i], len) != 0)
						continue; 
					match++;
				}
				if (!match)
					continue; 
				// Y, N -> lang..
				lstrcat(flags, _T(",")); 
				lstrcat(flags, flagChars[i]); 
			}
			pvarData->vt = VT_BSTR; 
			pvarData->bstrVal = SysAllocString(CT2CW(flags)); 
			return S_OK; 

		default: 
			return S_FALSE; 
	}

	buf[cbread] = '\0'; 
	pvarData->vt = VT_BSTR; 
	pvarData->bstrVal = SysAllocString(CA2W(buf)); 
	return S_OK; 
}

STDMETHODIMP CFragmentsColumn::init(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	this->Initialize(NULL); 
	return S_OK;
}
