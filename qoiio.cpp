/*

Copyright (C) 2022  Jan BOON (Kaetemi) <jan.boon@kaetemi.be>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "platform.h"
#include "qoirc.h"

#define QM_LIB_EXPORT
#include "qoiio.h"

#define QOI_NO_STDIO
#define QOI_IMPLEMENTATION
#include "qoi.h"

#define DLLEXPORT __declspec(dllexport)

namespace /* anonymous */
{

HINSTANCE s_HInstance = null;

} /* anonymous namespace */

/* DLL */

BOOL WINAPI DllMain(HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		MaxSDK::Util::UseLanguagePackLocale();
		s_HInstance = hDLLInst;
		DisableThreadLibraryCalls(s_HInstance);
		break;
	case DLL_PROCESS_DETACH:
		s_HInstance = null;
		break;
	}
	return TRUE;
}

/* Class Desc */

class QOIClassDesc : public ClassDesc2
{
public:
	int IsPublic() { return 1; }
	void *Create(BOOL loading = FALSE) { return null /* new BitmapIO_QOI() */; }
	const TCHAR *ClassName() { return _T("QOI"); }
	const TCHAR *NonLocalizedClassName() { return _T("QOI"); }
	SClass_ID SuperClassID() { return BMM_IO_CLASS_ID; }
	Class_ID ClassID() { return QOI_ClassID; }
	const TCHAR *Category() { return _T("Bitmap I/O"); }
	const TCHAR *InternalName() { return _T("qoiio"); }
	HINSTANCE HInstance() { return s_HInstance; }
};

static QOIClassDesc QOIDesc;

/* Interface */

DLLEXPORT const TCHAR *LibDescription()
{
	return _T("QOI File I/O");
}

DLLEXPORT int LibNumberClasses()
{
	return 1;
}

DLLEXPORT ClassDesc *LibClassDesc(int i)
{
	switch (i)
	{
	case 0:
		return &QOIDesc;
		break;
	default:
		return 0;
		break;
	}
}

DLLEXPORT ULONG LibVersion()
{
	return (VERSION_3DSMAX);
}

DLLEXPORT ULONG CanAutoDefer()
{
	return 1;
}

/* Bitmap I/O */

BitmapIO_QOI::BitmapIO_QOI()
{
}

BitmapIO_QOI::~BitmapIO_QOI()
{
}

int BitmapIO_QOI::ExtCount()
{
	return 1;
}

const MCHAR *BitmapIO_QOI::Ext(int n)
{
	return _T("qoi");
}

const MCHAR *BitmapIO_QOI::LongDesc()
{
	return _T("Quite OK Image Format");
}

const MCHAR *BitmapIO_QOI::ShortDesc()
{
	return _T("QOI");
}

const MCHAR *BitmapIO_QOI::AuthorName()
{
	return _T("Jan BOON (Kaetemi) <jan.boon@kaetemi.be>");
}

const MCHAR *BitmapIO_QOI::CopyrightMessage()
{
	return _T("Copyright (C) 2022 Jan Boon; Copyright (C) 2021 Dominic Szablewski");
}

UINT BitmapIO_QOI::Version()
{
	return 100; // 1.00
}

int BitmapIO_QOI::Capability()
{
	return BMMIO_READER | BMMIO_WRITER | BMMIO_EXTENSION | BMMIO_CONTROLWRITE;
}

/* end of file */
