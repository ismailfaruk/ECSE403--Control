@call "\\expo.campus.mcgill.ca\Profiles$\frouss7\Application Data\MathWorks\MATLAB\R2011b\mexopts.bat"
@echo on
call "%VCINSTALLDIR%\vcvarsall.bat" x86_amd64
set MATLAB=C:\PROGRA~1\MATLAB\R2011b
nmake -f Project_Model_Correct.mk  GENERATE_REPORT=0 SHOW_TIMES=0 DEBUG=0 DEBUG_HEAP=0
