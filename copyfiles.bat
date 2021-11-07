@echo off
cd ..

xcopy Engine\Assets\* bin\x64\Debug\Assets\* /S /Y /R /C /E
xcopy Engine\Assets\* bin\x64\Release\Assets\* /S /Y /R /C /E

xcopy Game\Game\Assets\* bin\x64\Debug\Assets\* /S /Y /R /C /E
xcopy Game\Game\Assets\* bin\x64\Release\Assets\* /S /Y /R /C /E

xcopy Engine\Dependencies\*.dll bin\x64\Debug /D /S /Y /R
xcopy Engine\Dependencies\*.dll bin\x64\Release /D /S /Y /R