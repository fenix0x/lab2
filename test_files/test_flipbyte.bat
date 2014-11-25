@echo off
REM запуск программы без параметров
flipbyte.exe 
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с нечисловым параметром
flipbyte.exe noname
IF NOT ERRORLEVEL 1 GOTO err
REM запуск программы с нецелочисленным параметром
flipbyte.exe 2.4
IF NOT ERRORLEVEL 1 GOTO err
REM запуск программы с неверным числом
flipbyte.exe 300
IF NOT ERRORLEVEL 2 GOTO err
REM запуск программы с корректным числом
flipbyte.exe 96 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt "flipout.txt"
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT