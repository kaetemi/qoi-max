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
	void *Create(BOOL loading = FALSE) { return new BitmapIO_QOI(); }
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

extern "C" {

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

} /* extern "C" */

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
	return 4; // TODO
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
	static_assert(QOI_HEADER_SIZE == 14, "Header size mismatch");
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
	if (desc.channels == 4)
		pbi->SetFlags(MAP_HAS_ALPHA);
	pbi->SetAspect(1.0f);
	pbi->SetGamma(desc.colorspace == QOI_SRGB ? 2.2f : 1.0f);
	pbi->SetFirstFrame(0);
	pbi->SetLastFrame(0);

	return status;
}

BitmapStorage *BitmapIO_QOI::Load(BitmapInfo *pbi, Bitmap *pmap, BMMRES *status)
{
	*status = BMMRES_SUCCESS;

	// Open file
	FILE *fi = _tfopen(pbi->Name(), _T("rb"));
	if (!fi)
	{
		*status = BMMRES_FILENOTFOUND;
		return null;
	}
	OnExit closeInput([&]() -> void {
		if (fi)
		{
			fclose(fi);
			fi = null;
		}
	});

	// File length
	long size;
	fseek(fi, 0, SEEK_END);
	size = ftell(fi);
	if (size <= 0)
	{
		*status = BMMRES_IOERROR;
		return null;
	}
	fseek(fi, 0, SEEK_SET);

	// Read file
	void *data;
	data = malloc(size);
	if (!data)
	{
		*status = BMMRES_MEMORYERROR;
		return null;
	}
	OnExit freeData([&]() -> void {
		free(data);
		data = null;
	});
	size_t bytes_read = fread(data, 1, size, fi);
	fclose(fi);
	fi = null;

	// Decode
	qoi_desc desc;
	unsigned char *pixels = (unsigned char *)qoi_decode(data, bytes_read, &desc, 0);
	OnExit freePixels([&]() -> void {
		QOI_FREE(pixels);
		pixels = null;
	});

	// Commit info
	pbi->SetWidth(desc.width);
	pbi->SetHeight(desc.height);
	pbi->SetType(desc.channels == 3 ? BMM_TRUE_24 : BMM_TRUE_32);
	if (desc.channels == 4)
		pbi->SetFlags(MAP_HAS_ALPHA);
	pbi->SetAspect(1.0f);
	pbi->SetGamma(desc.colorspace == QOI_SRGB ? 2.2f : 1.0f);
	pbi->SetFirstFrame(0);
	pbi->SetLastFrame(0);

	// Create storage
	BitmapStorage *s = BMMCreateStorage(pmap->Manager(), BMM_TRUE_32);
	OnExit abortStorage([&]() -> void {
		if (s)
		{
			delete s;
			s = null;
		}
	});
	if (!s)
	{
		*status = BMMRES_CANTSTORAGE;
		return null;
	}
	if (!s->Allocate(pbi, pmap->Manager(), BMM_OPEN_R))
	{
		*status = BMMRES_MEMORYERROR;
		return null;
	}

	// Put pixels
	BMM_Color_64 *line = (BMM_Color_64 *)calloc(desc.width, sizeof(BMM_Color_64));
	OnExit freeLine([&]() -> void {
		free(line);
		line = null;
	});
	ptrdiff_t ip = 0;
	for (unsigned int y = 0; y < desc.height; ++y)
	{
		if (desc.channels == 4)
		{
			for (unsigned int x = 0; x < desc.width; ++x, ip += 4)
			{
				line[x].r = ((uint16_t)pixels[ip + 0]) << 8;
				line[x].g = ((uint16_t)pixels[ip + 1]) << 8;
				line[x].b = ((uint16_t)pixels[ip + 2]) << 8;
				line[x].a = ((uint16_t)pixels[ip + 3]) << 8;
			}
		}
		else
		{
			for (unsigned int x = 0; x < desc.width; ++x, ip += 3)
			{
				line[x].r = ((uint16_t)pixels[ip + 0]) << 8;
				line[x].g = ((uint16_t)pixels[ip + 1]) << 8;
				line[x].b = ((uint16_t)pixels[ip + 2]) << 8;
			}
		}
		s->PutPixels(0, y, desc.width, line);
	}

	// Commit result
	BitmapStorage *res = s;
	s = null;
	return res;
}

BMMRES BitmapIO_QOI::OpenOutput(BitmapInfo *pbi, Bitmap *pmap)
{
	if (openMode != BMM_NOT_OPEN)
		return ProcessImageIOError(pbi, BMMRES_INTERNALERROR);

	if (!pmap)
		return ProcessImageIOError(pbi, BMMRES_INTERNALERROR);

	bi.CopyImageInfo(pbi);
	bi.SetUpdateWindow(pbi->GetUpdateWindow());
	if (bi.GetCustomGamma() != 1.0f || (bi.Gamma() != 1.0f && bi.Gamma() != 2.2f))
		bi.SetCustomGamma(2.2f);

	map = pmap;
	openMode = BMM_OPEN_W;

	return BMMRES_SUCCESS;
}

BMMRES BitmapIO_QOI::Write(int frame)
{
	if (openMode != BMM_OPEN_W)
		return ProcessImageIOError(&bi, BMMRES_INTERNALERROR);

	if (!map)
		return (ProcessImageIOError(&bi, BMMRES_INTERNALERROR));

	openMode = BMM_OPEN_W;

	// Get filename
	TCHAR filename[MAX_PATH];
	if (frame == BMM_SINGLEFRAME)
		_tcscpy(filename, bi.Name());
	else if (!BMMCreateNumberedFilename(bi.Name(), frame, filename))
		return ProcessImageIOError(&bi, BMMRES_NUMBEREDFILENAMEERROR);
	MaxSDK::Util::Path storageNamePath(filename);
	storageNamePath.SaveBaseFile();

	// Open file
	FILE *fo = _tfopen(filename, _T("wb"));
	if (!fo)
		return ProcessImageIOError(&bi, BMMRES_IOERROR);
	OnExit closeOutput([&]() -> void {
		if (fo)
		{
			fclose(fo);
			fo = null;
		}
	});

	// Header
	qoi_desc desc;
	desc.width = map->Width();
	desc.height = map->Height();
	desc.channels = map->HasAlpha() ? 4 : 3;
	desc.colorspace = OutputGamma() == 1.0f ? QOI_LINEAR : QOI_SRGB;

	// Allocate memory
	unsigned char *pixels = (unsigned char *)malloc(desc.width * desc.height * desc.channels);
	if (!pixels)
		return BMMRES_MEMORYERROR;
	OnExit freePixels([&]() -> void {
		free(pixels);
		pixels = null;
	});

	// Get pixels
	BMM_Color_32 *line = (BMM_Color_32 *)calloc(desc.width, sizeof(BMM_Color_32));
	OnExit freeLine([&]() -> void {
		if (line)
		{
			free(line);
			line = null;
		}
	});
	ptrdiff_t ip = 0;
	for (unsigned int y = 0; y < desc.height; ++y)
	{
		if (!GetDitheredOutputPixels(0, y, desc.width, line))
		{
			return BMMRES_IOERROR;
		}
		if (desc.channels == 4)
		{
			for (unsigned int x = 0; x < desc.width; ++x, ip += 4)
			{
				pixels[ip + 0] = line[x].r;
				pixels[ip + 1] = line[x].g;
				pixels[ip + 2] = line[x].b;
				pixels[ip + 3] = line[x].a;
			}
		}
		else
		{
			for (unsigned int x = 0; x < desc.width; ++x, ip += 3)
			{
				pixels[ip + 0] = line[x].r;
				pixels[ip + 1] = line[x].g;
				pixels[ip + 2] = line[x].b;
			}
		}
	}
	free(line);
	line = null;

	// Encode
	int size;
	unsigned char *encoded = (unsigned char *)qoi_encode(pixels, &desc, &size);
	if (!encoded)
	{
		return BMMRES_IOERROR;
	}
	OnExit freeEncoded([&]() -> void {
		QOI_FREE(encoded);
		encoded = null;
	});

	// Write
	if (fwrite(encoded, 1, size, fo) != size)
	{
		return BMMRES_IOERROR;
	}

	return BMMRES_SUCCESS;
}

int BitmapIO_QOI::Close(int flag)
{
	openMode = BMM_NOT_OPEN;
	map = null;
	return 1;
}

/* end of file */
