C:
call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
X:
rmdir /s /q qoi-max-release
rmdir /s /q build_2017
rmdir /s /q build_2018
rmdir /s /q build_2019
rmdir /s /q build_2020
rmdir /s /q build_2021
rmdir /s /q build_2022
mkdir build_2017
mkdir build_2018
mkdir build_2019
mkdir build_2020
mkdir build_2021
mkdir build_2022
cd build_2017
cmake -G "Visual Studio 17 2022" -T "v140" "-DCMAKE_SUPPRESS_REGENERATION=ON" "-DMaxSDK_DIR=C:/Program Files/Autodesk/3ds Max 2017 SDK/maxsdk" ..
if %errorlevel% neq 0 pause
cd ..
cd build_2018
cmake -G "Visual Studio 17 2022" -T "v140" "-DCMAKE_SUPPRESS_REGENERATION=ON" "-DMaxSDK_DIR=C:/Program Files/Autodesk/3ds Max 2018 SDK/maxsdk" ..
if %errorlevel% neq 0 pause
cd ..
cd build_2019
cmake -G "Visual Studio 17 2022" -T "v140" "-DCMAKE_SUPPRESS_REGENERATION=ON" "-DMaxSDK_DIR=C:/Program Files/Autodesk/3ds Max 2019 SDK/maxsdk" ..
if %errorlevel% neq 0 pause
cd ..
cd build_2020
cmake -G "Visual Studio 17 2022" -T "v141" "-DCMAKE_SUPPRESS_REGENERATION=ON" "-DMaxSDK_DIR=C:/Program Files/Autodesk/3ds Max 2020 SDK/maxsdk" ..
if %errorlevel% neq 0 pause
cd ..
cd build_2021
cmake -G "Visual Studio 17 2022" -T "v141" "-DCMAKE_SUPPRESS_REGENERATION=ON" "-DMaxSDK_DIR=C:/Program Files/Autodesk/3ds Max 2021 SDK/maxsdk" ..
if %errorlevel% neq 0 pause
cd ..
cd build_2022
cmake -G "Visual Studio 17 2022" -T "v141" "-DCMAKE_SUPPRESS_REGENERATION=ON" "-DMaxSDK_DIR=C:/Program Files/Autodesk/3ds Max 2022 SDK/maxsdk" ..
if %errorlevel% neq 0 pause
cd ..
cd build_2017
cmake .
if %errorlevel% neq 0 pause
msbuild QOI.sln /m:2 /p:Configuration=Release
if %errorlevel% neq 0 pause
cd ..
cd build_2018
cmake .
if %errorlevel% neq 0 pause
msbuild QOI.sln /m:2 /p:Configuration=Release
if %errorlevel% neq 0 pause
cd ..
cd build_2019
cmake .
if %errorlevel% neq 0 pause
msbuild QOI.sln /m:2 /p:Configuration=Release
if %errorlevel% neq 0 pause
cd ..
cd build_2020
cmake .
if %errorlevel% neq 0 pause
msbuild QOI.sln /m:2 /p:Configuration=Release
if %errorlevel% neq 0 pause
cd ..
cd build_2021
cmake .
if %errorlevel% neq 0 pause
msbuild QOI.sln /m:2 /p:Configuration=Release
if %errorlevel% neq 0 pause
cd ..
cd build_2022
cmake .
if %errorlevel% neq 0 pause
msbuild QOI.sln /m:2 /p:Configuration=Release
if %errorlevel% neq 0 pause
cd ..
cd build_2017/bin/Release
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "*.bmi"
if %errorlevel% neq 0 pause
cd ../../..
cd build_2018/bin/Release
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "*.bmi"
if %errorlevel% neq 0 pause
cd ../../..
cd build_2019/bin/Release
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "*.bmi"
if %errorlevel% neq 0 pause
cd ../../..
cd build_2020/bin/Release
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "*.bmi"
if %errorlevel% neq 0 pause
cd ../../..
cd build_2021/bin/Release
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "*.bmi"
if %errorlevel% neq 0 pause
cd ../../..
cd build_2022/bin/Release
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "*.bmi"
if %errorlevel% neq 0 pause
cd ../../..
mkdir qoi-max-release
cd qoi-max-release
mkdir max_2017
mkdir max_2018
mkdir max_2019
mkdir max_2020
mkdir max_2021
mkdir max_2022
xcopy ..\build_2017\bin\Release\qoi.bmi max_2017
xcopy ..\build_2018\bin\Release\qoi.bmi max_2018
xcopy ..\build_2019\bin\Release\qoi.bmi max_2019
xcopy ..\build_2020\bin\Release\qoi.bmi max_2020
xcopy ..\build_2020\bin\Release\qoi.bmi max_2021
xcopy ..\build_2022\bin\Release\qoi.bmi max_2022
cd ..
"C:\Program Files (x86)\NSIS\makensis.exe" setup.nsi
"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin\signtool.exe" sign /sha1 f0ef3c22d0373d2d6e3735207194d097c8f69877 /t http://timestamp.comodoca.com/authenticode "qoi-max-setup-release.exe"
if %errorlevel% neq 0 pause
pause
