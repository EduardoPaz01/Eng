@echo off
setlocal enabledelayedexpansion

REM Shuffle the questions in the Questions folder, randomly create a set of questions.

set "origem=%~dp0Questions"
set "destino=%~dp0ShuffledQuestions"
set "logFile=%destino%\log.txt"

if not exist "%destino%" mkdir "%destino%"

del "%logFile%" 2>nul

cd "%origem%"

for %%F in (*.png) do (
  set "extensao=%%~xF"
  set "novoNome=!random!_%%~nF_!time:~6,2!!time:~3,2!!time:~0,2!"
  copy "%%F" "%destino%\!novoNome!!extensao!" >nul
  echo !novoNome!!extensao! >> "%logFile%"
)

cd "%destino%"
endlocal