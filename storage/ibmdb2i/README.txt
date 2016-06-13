unzip into ibmdb2i
> cd /home/ADC/mysql-5.5.49/storage/ibmdb2i
> unzip new55_ibmdb2i.zip

copy ILE includes ...
> zzcpyincludes.sh

cmake makefile ...
> cmake CMakeLists.txt

make ...
> make


====
notes
====
Changes are defined by #ifdef PASE_55 (see db2i_global.h)

