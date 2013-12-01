# cryptoLyze #

A small support library created to analyze sboxes.

The tool exists in three pieces, the data, the raw library and the wrapper
around the raw library. The raw library provides all lower-level functions
needed to do the analysis itself. The wrapper calls the functions on the sbox,
preforms the work on the original and the seven rotations its creates, and
prints the output to a file.

There is a main that will run through the given data, preform the work
requested and output to a file.

Created by David Tran (unsignedzero)

* * * *

## Version/Changelog #

* Reordered includes. Preparing for static libs.

## 1.0.0 #
* Library initially created, commented and tested.
