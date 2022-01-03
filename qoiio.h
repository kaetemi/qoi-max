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

#ifndef QM_QOIIO_H
#define QM_QOIIO_H

#include <max.h>
#include <istdplug.h>
#include <bmmlib.h>
#include <iparamb2.h>

#ifdef _MSC_VER
#define SEV_DECL_EXPORT __declspec(dllexport)
#define SEV_DECL_IMPORT __declspec(dllimport)
#else
#define SEV_DECL_EXPORT
#define SEV_DECL_IMPORT
#endif

#if defined(QM_LIB_EXPORT)
#define QM_EXPORT __declspec(dllexport)
#else
#define QM_EXPORT __declspec(dllimport)
#endif

#define QOI_ClassID Class_ID(0x5dd872f0, 0x664308eb)

class BitmapIO_QOI : public BitmapIO
{
public:
	QM_EXPORT BitmapIO_QOI();
	QM_EXPORT virtual ~BitmapIO_QOI();

	QM_EXPORT virtual int ExtCount() override;
	QM_EXPORT virtual const MCHAR *Ext(int n) override;

	QM_EXPORT virtual const MCHAR *LongDesc() override;
	QM_EXPORT virtual const MCHAR *ShortDesc() override;
	QM_EXPORT virtual const MCHAR *AuthorName() override;
	QM_EXPORT virtual const MCHAR *CopyrightMessage() override;
	QM_EXPORT virtual UINT Version() override;

	QM_EXPORT virtual int Capability() override;
};

#endif /* QM_QOIIO_H */

/* end of file */