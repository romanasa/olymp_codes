@echo off 
for /L %%i in (1, 1, 10000000000000) do (
	gen.exe %%i >01
	oksol.exe %%i >02
	sol.exe <01 >03
	
	FC 02 03
	
	echo %%i
	
	if errorlevel 1 (
		exit
	) 
)
