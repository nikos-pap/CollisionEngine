@echo off
echo Copying DLLs...
xcopy /Y /D "%~dp0Dependencies\Binaries\slang\*.dll" "%1"
echo Done!
echo Copying Shaders...
xcopy /Y /D /I "%~dp0src\shaders\*" "%1\shaders\*"
echo Done!