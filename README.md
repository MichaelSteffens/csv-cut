csv-cut
=======

A tiny cut-like utilty for extractings from CVS files or streams.

SYNOPSIS
--------
**csv-cut** \[**OPTION**...\] **FILE** \[**FILE**\] ...

DESCRIPTION
-----------
Usage resembles the Unix tool cut(1), but is limited to the selection of delimiter separated fields.
Unlike cut(0), input is parsed and output is formatted according to [RFC4180](https://www.rfc-editor.org/rfc/rfc4180.txt) using minimal quoting.
Unlike cut(0), parsing stdin is currently not supported, due to an [issue with csv-parser's chunked read mechanism](https://github.com/vincentlaucsb/csv-parser/issues/180).

-h, --help

: Print usage

-d, --delimiter arg

: Input delimiter \[\\t,:;|\] (default: ,)

-f, --fields arg

: Comma separated list of fields (default: "")

--output-delimiter arg

: Output delimiter \[\\t,:;|\] (default: same as input delimiter)

SEE ALSO
--------

cvs-cut makes use of header libraries provided in the include directory:

 * Command line processing: from [cxxopts](https://github.com/jarro2783/cxxopts/tree/v3.0.0), release 3.0.0, MIT license.
 * CVS parsing and formatting: from [Vince's csv-parser](https://github.com/vincentlaucsb/csv-parser/tree/2.1.3), release 2.1.3, MIT license.
