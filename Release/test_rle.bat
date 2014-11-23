@echo off
REM запуск программы без параметров
rle.exe 
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с 1 параметром
rle.exe readme.txt
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с нулевым исходным файлом
rle.exe pack null.txt null.pak
IF NOT ERRORLEVEL 0 GOTO err
REM запуск программы с параметрами на упаковку
rle.exe pack test1.txt test1.pak
IF NOT ERRORLEVEL 0 GOTO err
FC /B test1.pak test1.std
IF ERRORLEVEL 1 GOTO err
rle.exe unpack test1.pak test1.tst
IF NOT ERRORLEVEL 0 GOTO err
FC /B test1.txt test1.tst
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT