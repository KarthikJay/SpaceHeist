@ECHO OFF
::#################################################################################################################################
:: Elevate this script                                                                                                            #
::#################################################################################################################################

(
    :: Check Admin rights and create VBS Script to elevate
    >nul fsutil 2>&1 || (

        :: Very little red console
        mode con cols=80 lines=3 
        color cf

        :: Message
        title Please wait...
        echo.
        echo                         Requesting elevated shell...

        :: Create VBS script
        echo Set UAC = CreateObject^("Shell.Application"^)>"%TEMP%\elevate.vbs"
        echo UAC.ShellExecute "%~f0", "%TEMP%\elevate.vbs", "", "runas", 1 >>"%TEMP%\elevate.vbs"
        if exist "%TEMP%\elevate.vbs" start /b >nul cscript /nologo "%TEMP%\elevate.vbs" 2>&1
        exit /b
    )

    :: Delete elevation script if exist
    if exist "%~1" >nul del /f "%~1" 2>&1
)

SETLOCAL
set /A port = 32756
ENDLOCAL
pushd "%~dp0"
start UE4Editor.exe "%~dp0..\SpaceHeist.uproject" ThirdPersonExampleMap?Listen -game -log -LogCmds="LogOnline All" -port=%port%
popd