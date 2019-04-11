@echo off 
for /L %%i in (1, 1, 10000000000000) do (
	gen1.exe %%i >input.txt
	ok.exe <input.txt >outputok.txt
	sol.exe <input.txt >output.txt
	
	FC outputok.txt output.txt >log
	
	echo %%i
	
	if errorlevel 1 (
		exit
	) 
)
