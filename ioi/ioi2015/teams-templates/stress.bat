@echo off 
for /L %%i in (1, 1, 10000000000000) do (
	gen.exe %%i >sample.in
	teamsok.exe 
	teams.exe
	
	FC sample.out sampleok.out
	
	echo %%i
	
	if errorlevel 1 (
		exit
	) 
)
