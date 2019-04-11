@echo off

set problem=carpet
set author=ip
rem you can set lang as dpr, java, cpp or python
set lang=java

echo Compiling checker...

if exist check.dpr dcc32 -U..\..\..\lib -cc check.dpr
if exist Check.java javac -classpath ../../../lib/testlib4j.jar Check.java -encoding utf8 
if exist Check.class jar cf Check.jar *.class

echo Compiling validator...

rmdir /S /Q __tmp 2> nul
mkdir __tmp
javac -sourcepath . -d __tmp Validate.java
pushd __tmp
mkdir META-INF
echo Main-Class: Validate> META-INF/manifest.1
call jar cfm Validate.jar META-INF/manifest.1 *.class
copy /Y Validate.jar .. > nul
popd
rmdir /S /Q __tmp

echo Generating tests...
if exist preliminary rd /s /q preliminary
if exist tests rd /s /q tests
cd src
if exist TestGen.py python TestGen.py
if exist TestGen.java javac TestGen.java
if exist TestGen.class java TestGen
cd ..

echo Compiling main solution...
if [%lang%]==[java] javac %problem%_%author%.java -encoding utf8
if [%lang%]==[cpp] g++ %problem%_%author%.cpp -O2 -Wall -Wl,--stack=67108864 -o %problem%_%author%.exe
if [%lang%]==[dpr] dcc32 -cc %problem%_%author%.dpr

echo Generating answers...

rem you can add tests folders here. For example: for %%s in (preliminary, tests, tests\subtask1, tests\subtask2)
for %%s in (preliminary, tests) do ( 
    for %%i in (%%s\???) do (
        echo Copying input for test %%i
        copy %%i %problem%.in > nul
        if exist validate.jar (
            echo Validating test %%i
            java -jar validate.jar < %problem%.in
            if errorlevel 1 (
                echo Validator rejects test %%i
                goto end
            )
            echo Validator accepts test %%i
        )

        echo Running solution on test %%i
        if [%lang%]==[java] java %problem%_%author%
        if [%lang%]==[cpp] %problem%_%author%.exe
        if [%lang%]==[dpr] %problem%_%author%.exe
        if [%lang%]==[python] python %problem%_%author%.py
        if errorlevel 1 (
            echo Solution failed on test %%i
            goto end
        )


        copy %problem%.out %%i.a > nul
        echo Running checker on test %%i
        if exist check.exe check %%i %%i.a %%i.a
        if exist Check.class java -Xmx256M -Xss64M -cp ../../../lib/testlib4j.jar;. ru.ifmo.testlib.CheckerFramework Check %%i %%i.a %%i.a
        if errorlevel 1 (
            echo Checker rejects main solution output on test %%i
            goto end
        )
    )
)

:end