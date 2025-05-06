@echo off

:: download "gcc-arm-none-eabi-10.3-2021.10-win32.exe" for windows ..
::   https://developer.arm.com/downloads/-/gnu-rm
::
:: download "gnu_make-3.81.exe" for windows ..
::   https://gnuwin32.sourceforge.net/packages/make.htm

@set PATH=C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin;%PATH%
@set PATH=C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\arm-none-eabi\bin;%PATH%
@set PATH=C:\Program Files (x86)\GnuWin32\bin;%PATH%

"C:\Program Files (x86)\GnuWin32\bin\make"

IF ERRORLEVEL 1 (
    echo.
    echo Build failed. ARCEncryptTools will not be run.
    goto :eof
)

echo.
echo Running ARCEncryptTools...
copy /Y .\build\firmware.bin .\firmware.hex
.\Tools\ARCEncryptTools.exe firmware.hex QzBtDzKjYxGsWalkieTalkieBt8000OpenDate20241202

pause
