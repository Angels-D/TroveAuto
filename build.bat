@echo off
echo === Compile Module.hpp into Module.dll ===
g++ -shared -static -Os -Wall -o Module.dll -x c++ ./libs/Module.hpp -lgdi32

echo === Compile TroveAuto.ahk into .exe ===
"C:\Program Files\AutoHotkey\Compiler\Ahk2Exe.exe" /compress 2 /base "C:\Program Files\AutoHotkey\v2\AutoHotkey64.exe" /in .\TroveAuto.ahk

echo === DONE ===

pause