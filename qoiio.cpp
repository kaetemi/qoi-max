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
	return BMMIO_READER | BMMIO_WRITER | BMMIO_EXTENSION /* | BMMIO_CONTROLWRITE */;
}

INT_PTR CALLBACK AboutCtrlDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		CenterWindow(hWnd, GetParent(hWnd));
		SetWindowText(GetDlgItem(hWnd, IDC_LICENSE), _T("Permission is hereby granted, free of charge, to any person obtaining a copy of\r\n"
		                                                "this software and associated documentation files(the \"Software\"), to deal in\r\n"
		                                                "the Software without restriction, including without limitation the rights to\r\n"
		                                                "use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies\r\n"
		                                                "of the Software, and to permit persons to whom the Software is furnished to do\r\n"
		                                                "so, subject to the following conditions :\r\n"
		                                                "The above copyright notice and this permission notice shall be included in all\r\n"
		                                                "copies or substantial portions of the Software.\r\n"
		                                                "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\r\n"
		                                                "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\r\n"
		                                                "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\r\n"
		                                                "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\r\n"
		                                                "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\r\n"
		                                                "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\r\n"
		                                                "SOFTWARE."));
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hWnd, 1);
			break;
		}
		return 1;
	}
	return 0;
}

void BitmapIO_QOI::ShowAbout(HWND hWnd)
{
	DialogBoxParam(s_HInstance, MAKEINTRESOURCE(IDD_QOI_ABOUT),
	    hWnd, (DLGPROC)AboutCtrlDlgProc, (LPARAM)0);
}

BOOL BitmapIO_QOI::ShowControl(HWND hWnd, DWORD flag)
{
	return FALSE; // TODO
}

DWORD BitmapIO_QOI::EvaluateConfigure()
{
	return FALSE; // TODO
}

BOOL BitmapIO_QOI::LoadConfigure(void *ptr, DWORD piDataSize)
{
	return FALSE; // TODO
}

BOOL BitmapIO_QOI::SaveConfigure(void *ptr)
{
	return FALSE; // TODO
}

BMMRES BitmapIO_QOI::GetImageInfo(BitmapInfo *pbi)
{
	BMMRES status = BMMRES_SUCCESS;

	// Open file
	FILE *fi = _tfopen(pbi->Name(), _T("rb"));
	if (!fi)
		return BMMRES_FILENOTFOUND;

	OnExit closeInput([&]() -> void {
		if (fi)
		{
			fclose(fi);
			fi = null;
		}
	});

	// Read header
	static_assert(QOI_HEADER_SIZE == 14);
	unsigned char header[QOI_HEADER_SIZE];
	if (fread(header, 1, QOI_HEADER_SIZE, fi) != QOI_HEADER_SIZE)
		return BMMRES_INVALIDFORMAT;
	fclose(fi);
	fi = null;

	// Parse header
	int p = 0;
	unsigned int header_magic;
	qoi_desc desc;
	header_magic = qoi_read_32(header, &p); // From qoi.h
	desc.width = qoi_read_32(header, &p);
	desc.height = qoi_read_32(header, &p);
	desc.channels = header[p++];
	desc.colorspace = header[p++];

	// Check header
	if (desc.width == 0 || desc.height == 0 // From qoi.h
	    || desc.channels < 3 || desc.channels > 4
	    || desc.colorspace > 1
	    || header_magic != QOI_MAGIC
	    || desc.height >= QOI_PIXELS_MAX / desc.width)
	{
		return BMMRES_INVALIDFORMAT;
	}

	// Commit info
	pbi->SetWidth(desc.width);
	pbi->SetHeight(desc.height);
	pbi->SetType(desc.channels == 3 ? BMM_TRUE_24 : BMM_TRUE_32);
	pbi->SetAspect(1.0f);
	pbi->SetGamma(desc.colorspace == QOI_SRGB ? 2.2f : 1.0f);
	pbi->SetFirstFrame(0);
	pbi->SetLastFrame(0);

	return status;
}

BitmapStorage *BitmapIO_QOI::Load(BitmapInfo *pbi, Bitmap *pmap, BMMRES *status)
{
	return NULL;
}

/* end of file */
