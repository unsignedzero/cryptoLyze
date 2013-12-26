# cryptoLyze [![Build status:Can't load apt.travis-ci.org](https://api.travis-ci.org/unsignedzero/cryptoLyze.png?branch=master)](https://travis-ci.org/unsignedzero/cryptoLyze)

A small support library created to analyze sboxes.

The tool exists in three pieces, the data, the raw library and the wrapper
around the raw library. The raw library provides all lower-level functions
needed to do the analysis itself. The wrapper calls the functions on the sbox,
preforms the work on the original and the seven rotations its creates, and
prints the output to a file.

There is a main that will run through the given data, preform the work
requested and output to a file.

Created by David Tran (unsignedzero)

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/unsignedzero/cryptolyze/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

* * * *

## Version/Changelog #

* Added BitDeli badge.
* Fixed bad commit author names in repo.
* Make file removes output files now after completion.
* Restored static keyword that was moved.
* Added travis-ci test logo to README.

## 1.3.0 #
* Bugfix: Values of InverseSbox need to be decremented by 1.
* Bug found with function calculateOrderSbox. Fixing...
* Bugfix: Filename mismatch.
* Adding include location in make and removing folding path in sboxMain.
* Setting Travis-CI to default only run make, as autotools is not used.
* Testing Travis-CI tests. Commits after this might be deleted that they involve
  checking Travis-CI and making sure the tests run correctly.
* Make test will run through both tests.
* sboxMain can read from args passed in.
* Creating test option for make.
* Moved data.h files into data directory.

## 1.2.1 #
* Removed unneeded dependencies due to separating files.
* Separated sboxSupportLib into three files.

## 1.2.0 #
* Fixing template issue.
* At linking stage, all lib files are separately created as oppose to one giant file.

## 1.1.0 #
* Lib files are in lib folder and statically linked in compile time.
* Reordered includes. Preparing for static libs.

## 1.0.0 #
* Library initially created, commented and tested.
