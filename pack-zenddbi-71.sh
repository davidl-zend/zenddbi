#!/QOpenSys/usr/bin/bash
ZENDDBI_SRC_DIR=/usr/src/zenddbi
VERSION=$1
VERSION=10.1.21


#extract version number from MariaDB version file
source VERSION

#MYSQL_VERSION_MAJOR=10
#MYSQL_VERSION_MINOR=1
#MYSQL_VERSION_PATCH=21

VERSION="${MYSQL_VERSION_MAJOR}.${MYSQL_VERSION_MINOR}.${MYSQL_VERSION_PATCH}"

echo Adding dependent libraries to archive...
#Extracting library to temporary directory
cp mariadb-${VERSION}-os400-powerpc.tar.gz /tmp
pushd /tmp && rm -rf /tmp/mariadb-${VERSION}-os400-powerpc
gtar xzf mariadb-${VERSION}-os400-powerpc.tar.gz && cp /usr/zlocal/zenddbi/mariadb-libdeps/* mariadb-${VERSION}-os400-powerpc/lib
tar -cf mariadb_i5os_install.tar mariadb-${VERSION}-os400-powerpc/
echo Packaging mariadb...
system "CALL PGM(QGPL/MARIADBPCK) PARM('1')"
echo Mariadb is packaged at QGPL/ZDBISAVF10
