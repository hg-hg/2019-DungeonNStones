@echo off
setlocal enabledelayedexpansion

set PATH=G:\QT5.12.3\5.12.3\msvc2017_64\bin;%PATH%

for /R ./ %%i in (*.exe) do (
echo Dealing %%i
windeployqt %%i
)

echo done.
pause