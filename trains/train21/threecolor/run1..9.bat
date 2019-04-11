@echo off

for /L %%i in (1, 1, 9) do (
	echo %%i
	greedy.exe <0%%i >0%%i.txt
)