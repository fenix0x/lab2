echo off
REM ������ ��������� ��� ����������
findtext.exe 
IF NOT ERRORLEVEL 1 GOTO err
REM ������ ��������� � 1 ����������
findtext.exe readme.txt
IF NOT ERRORLEVEL 1 GOTO err
REM ������ ��������� � �������� ������
findtext.exe readme.tx version
IF NOT ERRORLEVEL 1 GOTO err
REM ������ ��������� � �����������
findtext.exe readme.txt version > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt "testout.txt"
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT