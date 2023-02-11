PROMPT $g
rem ---------------------------------------------------------------------
rem This file executes the build command for the windows executable file.
rem It is here because I am lazy
rem ---------------------------------------------------------------------
del *.pyc
rmdir /S /Q dist
rmdir /S /Q dist32
rmdir /S /Q dist64

C:\Users\hangm\AppData\Local\Programs\Python\Python38-32\python.exe py2exe_setup.py py2exe
rmdir /S /Q build
move dist dist32
rem pause

del *.pyc
C:\Users\hangm\.platformio\python27\python.exe py2exe_setup.py py2exe
rmdir /S /Q build
move dist dist64
pause