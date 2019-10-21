## Resubmission
This is a resubmission. In this version :

> Please replace \dontrun{} by \donttest{} or unwap the examples if they can be executed in less than 5 sec per Rd-file.

* I have remove all the \dontrun{} in the examples.

> if there are references describing the (theoretical background of Weakly Associated Vectors) methods in your package, please add these in the Description field of your DESCRIPTION file in the form authors (year) <doi:...> authors (year) <arXiv:...> authors (year, ISBN:...) with no space after 'doi:', 'arXiv:' and angle brackets for auto-linking."

* The paper is almost finished. I will do the modification of the DESCRIPTION file once the paper is uploaded on arXiv if it is ok for you ? Best,


## Resubmission
This is a resubmission. In this version I have:

* Changes the @OPENMP_CFLAG@ by @OPENMP_FLAG@ in Makevars.in, It should resolved the following note on Debian distribution : 

  checking use of SHLIB_OPENMP_*FLAGS in Makefiles ... NOTE
  src/Makevars: SHLIB_OPENMP_CXXFLAGS is included in PKG_CXXFLAGS but not in PKG_LIBS
  src/Makevars: SHLIB_OPENMP_CFLAGS is included in PKG_LIBS but linking is by C++


* Modified in the DESCRIPTION file : VEctors -> Vectors and autocorrelated -> auto-correlated.


## Test environments
* local Windows 10, R-devel, R-release (R 3.6.1),
* ubuntu 14.04 (on travis-ci), R-release, R-devel
* OS X 9.4 (on travis-ci), R-release

## R CMD check results
- R-release (R 3.6.1) : There were no ERRORs, WARNINGs or NOTEs.

- R-devel : There were no ERRORs, WARNINGs,

1 NOTE, seems that the output of the examples are non-standard things. 

checking for non-standard things in the check directory ... NOTE
  Found the following files/directories:
    'WaveSampling-Ex_i386.Rout' 'WaveSampling-Ex_x64.Rout'
    'examples_i386' 'examples_x64'

On r-hub check with the two platforms :

 - Fedora Linux, R-devel, clang, gfortran
  * checking package dependencies ... NOTE
    Package suggested but not available for checking: ‘sf’

 - Ubuntu Linux 16.04 LTS, R-release, GCC
  * checking package dependencies ... NOTE
    Package suggested but not available for checking: ‘sf’
  * checking installed package size ... NOTE
    installed size is  6.6Mb
    sub-directories of 1Mb or more:
    libs   6.3Mb

This seems to be something to do with r-hub rather than a real problem.