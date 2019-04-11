@echo off 
for /L %%i in (1, 1, 10000000000000) do (
	gen.exe %%i >01
	Hok.exe <01 >02
	H.exe <01 >03
	
	FC 02 03 >log
	
	echo %%i
	
	if errorlevel 1 (
		exit
	) 
)
