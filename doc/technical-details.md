AndCOIN [START] Technical Details
===================================

This document outlines the technical implementation details for AndCOIN. It should be of use to advanced users and developers.

Specifications
--------------

* 84 million coins in total
* 1 minute average block time
* 40 coins per block
* Block reward halves every 12 months
* Retargets difficulty temporally using DigiShield
* x11 ASIC-resistant Proof-of-Work algorithm

Port numbers
------------

The following port numbers are used by AndCOIN.

* P2P uses port 35444 (35444 on Testnet)
* RPC uses port 35422 (35331 on Testnet)

Message start string
--------------------

The message start string used by AndCOIN is:

```
0xff, 0xc4, 0xba, 0xdf
```

The message start string for Testnet is:

```
0xff, 0xc4, 0xb9, 0xde
```
