echo off
REM ������ ��������� ��� ����������
multmatrix.exe
IF NOT ERRORLEVEL 0 GOTO err
REM ������ ��������� � ����� ����������
multmatrix.exe matrix.txt
IF NOT ERRORLEVEL 0 GOTO err
REM ������ ��������� � ������������ ����������
multmatrix.exe  matrix  matrix.txt
IF NOT ERRORLEVEL 1 GOTO err
REM ������ ��������� � ����������� �������
multmatrix.exe matrix.txt matrix.txt> output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt "matrixout.txt"
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded : -)
EXIT
:err
ECHO Program testing failed : -(
EXIT