echo Building Mariadb
#pushd ~/server
export LDFLAGS="-Wl,-blibpath:/usr/local/mariadb/lib:/usr/lib:/lib -Wl,-bmaxdata:0x80000000 -Wl,-bexpall -Wl,-bexpfull -Wl,-bnoipath -Wl,-bbigtoc"
export M4=/usr/local/bin/m4
#Use perzl binaries where available
echo $PATH |grep freeware || export PATH=/opt/freeware/bin:$PATH
cmake . -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS_DEBUG="-O0 -g -mminimal-toc -Wno-attributes -mcpu=power6" \
    -DCMAKE_C_FLAGS_DEBUG="-O0 -g -mminimal-toc -Wno-attributes -mcpu=power6" \
    -DCMAKE_EXE_LINKER_FLAGS_DEBUG="-Wl,-blibpath:/usr/local/mariadb/lib:/usr/lib:/lib -Wl,-bmaxdata:0x80000000 -Wl,-bexpfull -Wl,-bnoipath -Wl,-bbigtoc" \
    -DCMAKE_MODULE_LINKER_FLAGS_DEBUG="-Wl,-blibpath:/usr/local/mariadb/lib:/usr/lib:/lib -Wl,-bmaxdata:0x80000000 -Wl,-bexpfull -Wl,-bnoipath -Wl,-bbigtoc" \
    -DCMAKE_SHARED_LINKER_FLAGS_DEBUG="-Wl,-blibpath:/usr/local/mariadb/lib:/usr/lib:/lib -Wl,-bmaxdata:0x80000000 -Wl,-bexpfull -Wl,-bnoipath -Wl,-bbigtoc" \
    -DEFAULT_SYSCONFDIR=/usr/local/mariadb/bin \
    -DCMAKE_INSTALL_PREFIX=/usr/local/mariadb \
    -DMYSQL_DATADIR=/usr/local/mariadbdata \
    -DCMAKE_BUILD_WITH_INSTALL_RPATH=TRUE \
    -DCMAKE_INSTALL_RPATH=/usr/local/mariadb/lib \
    -DDISABLE_SHARED=OFF \
    -DWITH_READLINE=OFF \
    -DCURSES_CURSES_H_PATH=/usr/include \
    -DCURSES_CURSES_LIBRARY=/usr/lib/libcurses.a \
    -DCURSES_EXTRA_LIBRARY=CURSES_EXTRA_LIBRARY-NOTFOUND \
    -DCURSES_FORM_LIBRARY=/usr/lib/libform.a \
    -DCURSES_HAVE_CURSES_H=/usr/include/curses.h \
    -DCURSES_INCLUDE_PATH=/usr/include \
    -DCURSES_LIBRARY=/usr/lib/libcurses.a \
    -DCURSES_NCURSES_LIBRARY=/usr/lib/libncurses.a
    #-DCURSES_NCURSES_LIBRARY= \
    #-DREADLINE_INCLUDE_DIR= \
    #-DREADLINE_LIBRARY= \
    # // Path to a file.
    #    -DCURSES_CURSES_H_PATH= \
    #-DCURSES_CURSES_LIBRARY= \
    #-DCURSES_EXTRA_LIBRARY=CURSES_EXTRA_LIBRARY-NOTFOUND \
    #-DCURSES_FORM_LIBRARY= \
    #-DCURSES_HAVE_CURSES_H= \
    #-DCURSES_INCLUDE_PATH= \
    #-DCURSES_LIBRARY= \

    # READLINE_INCLUDE_DIR:PATH=/usr/include/readline
    #
    # // Path to a library.
    # READLINE_LIBRARY:FILEPATH=/usr/lib/libreadline.a
    #
    # CURSES_CURSES_H_PATH:PATH=/usr/include
    #
    # // Path to a library.
    # CURSES_CURSES_LIBRARY:FILEPATH=/usr/lib/libcurses.a
    #
    # // Path to a library.
    # CURSES_EXTRA_LIBRARY:FILEPATH=CURSES_EXTRA_LIBRARY-NOTFOUND
    #
    # // Path to a library.
    # CURSES_FORM_LIBRARY:FILEPATH=/usr/lib/libform.a
    #
    # // Path to a file.
    # CURSES_HAVE_CURSES_H:FILEPATH=/usr/include/curses.h
    #
    # // The curses include path
    # CURSES_INCLUDE_PATH:FILEPATH=/usr/include
    #
    # // The curses library
    # CURSES_LIBRARY:FILEPATH=/usr/lib/libcurses.a
    #
    # // Path to a library.
    # CURSES_NCURSES_LIBRARY:FILEPATH=/usr/lib/libncurses.a
    #
    #


make

