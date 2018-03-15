@echo off

for /f %%p in ('cd') do set _currentpath=%%p
cd ..
for /f %%p in ('cd') do set _ngpcpath=%%p
cd %_currentpath%

path=%PATH%;%_ngpcpath%\t900\bin
SET THOME=%_ngpcpath%\t900\
PROMPT $P$_NGPC$G
make
cmd