@echo off
REM ������ ��������� ��� ����������
flipbyte.exe 
IF NOT ERRORLEVEL 0 GOTO err
REM ������ ��������� � ���������� ����������
flipbyte.exe noname
IF NOT ERRORLEVEL 1 GOTO err
REM ������ ��������� � ��������������� ����������
flipbyte.exe 2.4
IF NOT ERRORLEVEL 1 GOTO err
REM ������ ��������� � �������� ������
flipbyte.exe 300
IF NOT ERRORLEVEL 2 GOTO err
REM ������ ��������� � ���������� ������
flipbyte.exe 96 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt "flipout.txt"
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT