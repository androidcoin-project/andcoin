AndCOIN [AND] integration/staging tree
==========================================

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2011-2013 Litecoin Developers
Copyright (c) 	   2018 AndCOIN

What is AndCOIN?
----------------

AndCOIN is the cryptocurrency for www.andcoin.top

## Specifications

Name: ANDCOIN
Symbol: AND
Algo: A5A
Pure POW
Total coin: 25 Million 
Block time: 60 seconds 
Difficulty Re-targets: Every block used DigiShield
Confirmations on Transactions: 10 
Maturity: 100
Block 1 - Premine block 3.5%
Block Reward: 5 AND
Block reward 1st year cut half every 3 months: 5 AND, 2.5 AND, 1.25 AND, 0.625 AND. Next year cut half every 12 months 
 
QR CODE support
UPNP Support

P2p port=35444
Rpc port=35422

Release note
------------
25 frebuary 2018 
version 1.2.0.0 launch

5 march 2018 Mandatory update
version 1.2.0.2 fix key checkpoint & add checkpoint

7 march 2018 optional update
version 1.2.1.1 update qt icon & add console main tab 

License
-------

AndCOIN is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the AndCOIN
development team members simply pulls it.

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitcoin/bitcoin/tags) are created
regularly to indicate new official, stable release versions of AndCOIN.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake ANDCOIN_QT_TEST=1 -o Makefile.test andcoin-qt.pro
    make -f Makefile.test
    ./andcoin-qt_test

