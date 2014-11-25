@echo off
REM ������ ��������� ��� ����������
rle.exe 
IF NOT ERRORLEVEL 0 GOTO err
REM ������ ��������� � 1 ����������
rle.exe readme.txt
IF NOT ERRORLEVEL 0 GOTO err
REM ������ ��������� � ������� �������� ������
rle.exe pack null.txt null.pak
IF NOT ERRORLEVEL 0 GOTO err
REM ������ ��������� � ����������� �� ��������
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