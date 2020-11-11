# Cunit

https://sourceforge.net/projects/cunit/
https://github.com/jacklicn/CUnit

autoreconf -vif
./configure --prefix <Your choice of directory for installation>
make
make install

cmake . -B build/
cmake --build build/