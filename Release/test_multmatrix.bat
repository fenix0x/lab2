echo off
REM запуск программы без параметров
multmatrix.exe
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с одним параметром
multmatrix.exe matrix.txt
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с неправильным параметром
multmatrix.exe  matrix  matrix.txt
IF NOT ERRORLEVEL 1 GOTO err
REM запуск программы с корректными данными
multmatrix.exe matrix.txt matrix.txt> output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt "matrixout.txt"
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT