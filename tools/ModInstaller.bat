:: Get-ItemProperty 'HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\FeatureUsage\*','HKCU:\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Compatibility Assistant\Store' -Name '*GlyphClientApp.exe' | ForEach-Object {$_ | Get-Member -Name '*GlyphClientApp.exe'| Select-Object -ExpandProperty Name} | ForEach {if(Test-Path $_ -PathType Leaf) {$GAME_PATH = Split-Path $_}}; if(-not $GAME_PATH) {$GAME_PATH = Get-ItemProperty 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*' | Where-Object DisplayName -EQ "Trove" | Select-Object -ExpandProperty InstallLocation}

@ECHO off&(cd/d "%~dp0")&(cacls "%SystemDrive%\System Volume Information" >nul 2>&1)||(start "" mshta vbscript:CreateObject^("Shell.Application"^).ShellExecute^("%~snx0"," %*","","runas",1^)^(window.close^)&exit /b)

SET PATH_REG="HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\FeatureUsage" ^
             "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Compatibility Assistant\Store"
SET PATH_ModCfgs=%AppData%\Trove\ModCfgs\

mkdir ModCfgs mods > NUL 2>&1

setlocal EnableDelayedExpansion
FOR %%I IN (%PATH_REG%) DO (
    FOR /F "skip=2 tokens=*" %%J IN ('REG QUERY %%I /S /V "*Live\Trove.exe"') DO (
        SET STR=
        FOR %%K IN (%%J) DO (
            ECHO !STR! | FINDSTR "Trove.exe" >NUL || SET STR=!STR!%%K 
        )
        IF EXIST !STR! ( 
            SET PATH_mods=!STR!
            GOTO START
        )
    )
)

ECHO 错误: 未找到你的模组路径，请手动配置
GOTO END

:START
SET PATH_mods=%PATH_mods:~0,-10%mods
ECHO ******* 欢迎使用Trove 模组安装脚本 ———— By とても残念だ *******
ECHO * 须知: 部分模组需要搭配配置文件
ECHO *       模组文件后缀名为tmod, 需要放入mods文件夹
ECHO *       配置文件后缀名为cfg, 需要放入ModCfgs文件夹
ECHO * 提示: 您的tmod文件将会被拷贝至: %PATH_mods%
ECHO *       您的cfg文件将会被拷贝至: %PATH_ModCfgs%
ECHO * 1. 如果您正在压缩包内打开本脚本, 则请先解压至任意目录再重新运行本脚本
ECHO * 2. 请根据提示, 先将您需要安装的tmod文件和cfg文件分别放入当前目录下的mods和ModCfgs文件夹下
ECHO *    当前路径为: %~dp0
ECHO * 3. 准备好上述操作后, 请继续下一步

setlocal EnableDelayedExpansion
ECHO %~dp0 | FINDSTR %temp% | FINDSTR "zip 7z rar tar" &&^
ECHO 警告: 疑似在压缩包/临时目录下打开脚本, 建议先移动脚本到其他路径 &&^
CHOICE /M ">>> 键入Y继续, N退出" || if %errorlevel% == 1 EXIT

setlocal EnableDelayedExpansion
DIR /a /b mods|findstr .* >NUL || DIR /a /b ModCfgs|findstr .* >NUL ||^
ECHO 警告: 疑似待安装的模组文件夹为空, 请确认您已放置好待安装模组 &&^
CHOICE /M ">>> 键入Y继续, N退出" || if %errorlevel% == 1 EXIT

MD "%PATH_mods%"
XCOPY mods "%PATH_mods%" /E
ECHO 提示: 模组配置完成

MD "%PATH_ModCfgs%"
XCOPY ModCfgs "%PATH_ModCfgs%" /E
ECHO 提示: ModCfgs配置完成

:END
ECHO ^>^>^> 按任意键退出 ^<^<^<
PAUSE>NUL
EXIT

