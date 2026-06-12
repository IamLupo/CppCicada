Use MSYS2 MINGW64. You can download over here: https://www.msys2.org/

First time run:
```
pacman -Syu
pacman -Su
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake make
```

Log:
```
Anonymous@DESKTOP-60CPIHR MINGW64 ~
$ cd /c/Users/IamLupo/Downloads

Anonymous@DESKTOP-60CPIHR MINGW64 /c/Users/IamLupo/Downloads
$ cd CppCicada

Anonymous@DESKTOP-60CPIHR MINGW64 /c/Users/IamLupo/Downloads/CppCicada
$ mkdir build

Anonymous@DESKTOP-60CPIHR MINGW64 /c/Users/IamLupo/Downloads/CppCicada
$ cd build/

Anonymous@DESKTOP-60CPIHR MINGW64 /c/Users/IamLupo/Downloads/CppCicada/build
$ cmake -G "MSYS Makefiles" ..
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/msys64/mingw64/bin/cc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/msys64/mingw64/bin/c++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.6s)
-- Generating done (0.0s)
-- Build files have been written to: C:/Users/iamlupo/Downloads/CppCicada/build

Anonymous@DESKTOP-60CPIHR MINGW64 /c/Users/IamLupo/Downloads/CppCicada/build
$ make -j 8
[ 10%] Building CXX [o b4j0e[%[c ] t4 4 00C%B%M]u]a i klBeduBFiiuinlilgdle idsCni/XgncX gi C coXCabX
Xdj Xa[eo . cbod5tjbi0 ejr%Cce/cst]Mtr  a kCcCBeM/MuFacaiikoklleredeFeFisi.in/lclgcepe sspiC//.cXcco
aXiibd ccjaoaa
.bdddjaaie..rcdd/tiis rrrC//cMss/arrckccoe//rFtteirr/laaPennrss[so/f fcco6oeir0rscm%msae]eedr rda//A
.BTVtdueibiixgarltes/d.nhsiceprn.rpcgce./ p.otCpcbrj.pXa
opXnb. sjoofb
bojjre
mcetr /CSMhaikfetF.iclpeps./ocbijca
da.dir/src/transform[e r7/0T%o]t ienBtu.iclpdpi.nogb jCX
X object CMakeFiles/cicada.dir/src/util/screen.cpp.obj
[ 80%] Building CXX object CMakeFiles/cicada.dir/src/pages.cpp.obj
[ 90%] Building CXX object CMakeFiles/cicada.dir/src/main.cpp.obj
[100%] Linking CXX executable cicada.exe
[100%] Built target cicada

Anonymous@DESKTOP-60CPIHR MINGW64 /c/Users/IamLupo/Downloads/CppCicada/build
$ ls
CMakeCache.txt  CMakeFiles  Makefile  cicada.exe  cmake_install.cmake
```