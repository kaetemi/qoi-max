
SetCompressor lzma
Name "QOI Bitmap I/O Plugin for 3ds Max"
OutFile "qoi-max-setup-release.exe"
RequestExecutionLevel Admin
XPStyle on

LicenseData "3RDPARTY.md"

!define VERSION "1.01"
VIAddVersionKey "ProductName" "QOI Bitmap I/O Plugin for 3ds Max"
VIAddVersionKey "ProductVersion" ${VERSION}
VIAddVersionKey "CompanyName" "Polyverse OÜ"
VIAddVersionKey "LegalTrademarks" "Polyverse is a trademark of Polyverse OÜ."
VIAddVersionKey "LegalCopyright" "Copyright (C) 2022 Jan Boon, Polyverse OÜ; Copyright (C) 2021 Dominic Szablewski"
VIAddVersionKey "FileDescription" "Setup QOI Bitmap I/O Plugin for 3ds Max"
VIAddVersionKey "FileVersion" ${VERSION}
VIProductVersion "${VERSION}.0.0"

Page license
Page components
Page instfiles

!include LogicLib.nsh
Function .onInit
	SetRegView 64
	
	ClearErrors
	ReadRegStr $0 HKLM "SOFTWARE\Autodesk\3dsMax\19.0" "Installdir"
	${If} ${Errors}
		SectionSetFlags 0 ${SF_RO}
	${Else}
		Var /GLOBAL max2017InstallDir
		StrCpy $max2017InstallDir $0
	${EndIf}
	
	ClearErrors
	ReadRegStr $0 HKLM "SOFTWARE\Autodesk\3dsMax\20.0" "Installdir"
	${If} ${Errors}
		SectionSetFlags 1 ${SF_RO}
	${Else}
		Var /GLOBAL max2018InstallDir
		StrCpy $max2018InstallDir $0
	${EndIf}
	
	ClearErrors
	ReadRegStr $0 HKLM "SOFTWARE\Autodesk\3dsMax\21.0" "Installdir"
	${If} ${Errors}
		SectionSetFlags 2 ${SF_RO}
	${Else}
		Var /GLOBAL max2019InstallDir
		StrCpy $max2019InstallDir $0
	${EndIf}
	
	ClearErrors
	ReadRegStr $0 HKLM "SOFTWARE\Autodesk\3dsMax\22.0" "Installdir"
	${If} ${Errors}
		SectionSetFlags 3 ${SF_RO}
	${Else}
		Var /GLOBAL max2020InstallDir
		StrCpy $max2020InstallDir $0
	${EndIf}
	
	ClearErrors
	ReadRegStr $0 HKLM "SOFTWARE\Autodesk\3dsMax\23.0" "Installdir"
	${If} ${Errors}
		SectionSetFlags 4 ${SF_RO}
	${Else}
		Var /GLOBAL max2021InstallDir
		StrCpy $max2021InstallDir $0
	${EndIf}
	
	ClearErrors
	ReadRegStr $0 HKLM "SOFTWARE\Autodesk\3dsMax\24.0" "Installdir"
	${If} ${Errors}
		SectionSetFlags 5 ${SF_RO}
	${Else}
		Var /GLOBAL max2022InstallDir
		StrCpy $max2022InstallDir $0
	${EndIf}
FunctionEnd

Section "QOI Bitmap I/O Plugin for 3ds Max 2017"
	SetOutPath $max2017InstallDir\Plugins
	File qoi-max-release\max_2017\qoi.bmi
SectionEnd

Section "QOI Bitmap I/O Plugin for 3ds Max 2018"
	SetOutPath $max2018InstallDir\Plugins
	File qoi-max-release\max_2018\qoi.bmi
SectionEnd

Section "QOI Bitmap I/O Plugin for 3ds Max 2019"
	SetOutPath $max2019InstallDir\Plugins
	File qoi-max-release\max_2019\qoi.bmi
SectionEnd

Section "QOI Bitmap I/O Plugin for 3ds Max 2020"
	SetOutPath $max2020InstallDir\Plugins
	File qoi-max-release\max_2020\qoi.bmi
SectionEnd

Section "QOI Bitmap I/O Plugin for 3ds Max 2021"
	SetOutPath $max2021InstallDir\Plugins
	File qoi-max-release\max_2021\qoi.bmi
SectionEnd

Section "QOI Bitmap I/O Plugin for 3ds Max 2022"
	SetOutPath $max2022InstallDir\Plugins
	File qoi-max-release\max_2022\qoi.bmi
SectionEnd
