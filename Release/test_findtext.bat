@echo off
REM запуск программы без параметров
findtext.exe 
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с 1 параметром
findtext.exe readme.txt
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с неверным файлом
findtext.exe readme.tx version
IF NOT ERRORLEVEL 1 GOTO err
REM запуск программы с параметрами
findtext.exe readme.txt version > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt "testout.txt"
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT