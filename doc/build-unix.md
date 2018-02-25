Copyright (c) 2009-2012 Bitcoin Developers

Copyright (c) 2014-2015 andcoin Developers

Distributed under the MIT/X11 software license, see the accompanying file license.txt or http://www.opensource.org/licenses/mit-license.php. This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/).  This product includes cryptographic software written by Eric Young (eay+AEA-cryptsoft.com) and UPnP
software written by Thomas Bernard.

UNIX BUILD NOTES
+AD0APQA9AD0APQA9AD0APQA9AD0APQA9AD0APQA9AD0-

It is recommeded to use Berkeley DB 4.8 for building andcoin wallet (see the following instructions) as well as OpenSSL 1.0.x. 

Build andcoind
+AD0APQA9AD0APQA9AD0APQA9AD0APQA9AD0APQA9AD0-

To Build On i386, amd64
--------
	cd src/
	make -f makefile.unix                          +ACM- Headless andcoin

To Build On armv6l
--------
	cd src/
	make -f makefile.unix xCPUARCH+AD0-armv6l           +ACM- Headless andcoin

To Build On armv7l
--------
	cd src/
	make -f makefile.unix xCPUARCH+AD0-armv7l           +ACM- Headless andcoin

The release is built with GCC and then +ACI-strip bitcoind+ACI- to strip the debug symbols, which reduces the executable size by about 90+ACU-.

Build andcoin-qt
+AD0APQA9AD0APQA9AD0APQA9AD0APQA9AD0APQA9AD0-

See readme-qt.rst for instructions on building andcoin-QT. In general, the QT wallet can be built through following commands (provided dependencies are properly installed):
	qmake andcoin-qt.pro
	make

To compile Berkeley DB 4.8 on your own:

+AGAAYABg-bash
wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
+ACM- Verify source
echo '12edc0df75bf9abd7f82f821795bcee50f42cb2e5f76a6a281b85732798364ef  db-4.8.30.NC.tar.gz' +AHw- sha256sum -c
tar -xzvf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build+AF8-unix
+ACM- Build and install DB4.8 under /opt/local/db-4.8.30.NC
../dist/configure --disable-shared --enable-cxx --disable-replication --with-pic --prefix+AD0-/opt/local/db-4.8.30.NC
make
sudo make install
+AGAAYABg-
Then Build Qt wallet with explicit DB paths:

	qmake andcoin-qt.pro BDB+AF8-INCLUDE+AF8-PATH+AD0-/opt/local/db-4.8.30.NC/include BDB+AF8-LIB+AF8-PATH+AD0-/opt/local/db-4.8.30.NC/lib BDB+AF8-LIB+AF8-SUFFIX+AD0--4.8
	make


Dependencies for i386, amd64
------------

 Library      +AHw- Purpose           +AHw- Description
 -------------+AHw--------------------+AHw-----------------------
 libssl       +AHw- SSL Support       +AHw- Secure communications
 libdb4.8     +AHw- Berkeley DB       +AHw- Blockchain +ACY- wallet storage
 libboost     +AHw- Boost             +AHw- C Library
 libminiupnpc +AHw- UPnP Support      +AHw- Optional firewall-jumping support
 libqrencode  +AHw- QRCode generation +AHw- Optional QRCode generation
 libgmp       +AHw- GMP               +AHw- Multiple precision arithmetic library

Dependencies for armv6l, armv7l
------------

 Library      +AHw- Purpose           Description
 -------------+AHw--------------------+AHw-----------------------
 libssl       +AHw- SSL Support       +AHw- Secure communications
 libdb4.8     +AHw- Berkeley DB       +AHw- Blockchain +ACY- wallet storage
 libboost     +AHw- Boost             +AHw- C Library
 libminiupnpc +AHw- UPnP Support      +AHw- Optional firewall-jumping support
 libqrencode  +AHw- QRCode generation +AHw- Optional QRCode generation
 libgmp       +AHw- GMP               +AHw- Multiple precision arithmetic library

Note that libexecinfo should be installed, if you building under +ACo-BSD systems. 
This library provides backtrace facility.

miniupnpc may be used for UPnP port mapping.  It can be downloaded from
http://miniupnp.tuxfamily.org/files/.  UPnP support is compiled in and
turned off by default.  Set USE+AF8-UPNP to a different value to control this:

	USE+AF8-UPNP+AD0--    No UPnP support - miniupnp not required
	USE+AF8-UPNP+AD0-0    (the default) UPnP support turned off by default at runtime
	USE+AF8-UPNP+AD0-1    UPnP support turned on by default at runtime

libqrencode may be used for QRCode image generation. It can be downloaded
from http://fukuchi.org/works/qrencode/index.html.en, or installed via
your package manager. Set USE+AF8-QRCODE to control this:

	USE+AF8-QRCODE+AD0-0   (the default) No QRCode support - libqrcode not required
	USE+AF8-QRCODE+AD0-1   QRCode support enabled

Dependency Build Instructions: Ubuntu +ACY- Debian (i386, amd64)
----------------------------------------------
See above db4.8 building if you cannot find it through apt installation. The version libgmp may change, for example, libgmp3-dev as in the latest Debian distribution, you'll need to make sure the right version to be installed. 

	sudo apt-get install build-essential libtool autotools-dev autoconf automake
	sudo apt-get install libssl-dev
	sudo apt-get install libdb4.8-dev
	sudo apt-get install libdb4.8dev
	sudo apt-get install libgmp-dev
	sudo apt-get install libminiupnpc-dev
	sudo apt-get install libboost-all-dev
	sudo apt-get install libprotobuf-dev libqrencode-dev

Dependency Build Instructions: Ubuntu +ACY- Debian (armv7l)
----------------------------------------------
See above db4.8 building if you cannot find it through apt installation. The version libgmp may change, for example, libgmp3-dev as in the latest Debian distribution, you'll need to make sure the right version to be installed. 

	sudo apt-get install build-essential
	sudo apt-get install libssl-dev
	sudo apt-get install libdb4.8-dev
	sudo apt-get install libdb4.8dev
	sudo apt-get install libgmp-dev
	sudo apt-get install libminiupnpc-dev
	sudo apt-get install libboost-all-dev
	sudo apt-get install libprotobuf-dev libqrencode-dev

Security
--------
To help make your bitcoin installation more secure by making certain attacks impossible to
exploit even if a vulnerability is found, you can take the following measures:

+ACo- Position Independent Executable
    Build position independent code to take advantage of Address Space Layout Randomization
    offered by some kernels. An attacker who is able to cause execution of code at an arbitrary
    memory location is thwarted if he doesn't know where anything useful is located.
    The stack and heap are randomly located by default but this allows the code section to be
    randomly located as well.

    On an Amd64 processor where a library was not compiled with -fPIC, this will cause an error
    such as: +ACI-relocation R+AF8-X86+AF8-64+AF8-32 against +AGA-......' can not be used when making a shared object+ADsAIg-

    To build with PIE, use:
    make -f makefile.unix ... -e PIE+AD0-1

    To test that you have built PIE executable, install scanelf, part of paxutils, and use:
    scanelf -e ./bitcoin

    The output should contain:
     TYPE
    ET+AF8-DYN

+ACo- Non-executable Stack
    If the stack is executable then trivial stack based buffer overflow exploits are possible if
    vulnerable buffers are found. By default, bitcoin should be built with a non-executable stack
    but if one of the libraries it uses asks for an executable stack or someone makes a mistake
    and uses a compiler extension which requires an executable stack, it will silently build an
    executable without the non-executable stack protection.

    To verify that the stack is non-executable after compiling use:
    scanelf -e ./bitcoin

    the output should contain:
    STK/REL/PTL
    RW- R-- RW-

    The STK RW- means that the stack is readable and writeable but not executable.
