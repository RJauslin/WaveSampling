## Test environments
* Windows 10, R-devel (local), R-release (R 3.6.2) (local),
* Linux, Ubuntu 16.04 (on travis-ci) R-release, Debian, R-devel
* OS X 9.4 (on travis-ci), R-release

## R CMD check results

- R-release (R 3.6.2) : There were no ERRORs, WARNINGs or NOTEs.

- R-devel : There were no ERRORs, WARNINGs,

1 NOTE, seems that the output of the examples are non-standard things. 

checking for non-standard things in the check directory ... NOTE
  Found the following files/directories:
    'WaveSampling-Ex_i386.Rout' 'WaveSampling-Ex_x64.Rout'
    'examples_i386' 'examples_x64'

## rhub

- Fedora Linux, R-devel,, clang, gfortran
  * checking package dependencies ... ERROR
    Packages suggested but not available: 'ggvoronoi', 'sf'

- Ubuntu Linux 16.04 LTS, R-release, GCC
 * checking package dependencies ... ERROR
   Package suggested but not available: ‘sf’

- Debian Linux, R-devel, GCC ASAN/UBSAN
  * There were no ERRORs, WARNINGs or NOTEs.

- Windows Server 2008 R2 SP1, R-devel, 32/64 bit
  * checking CRAN incoming feasibility ... NOTE
 
  Possibly mis-spelled words in DESCRIPTION:
  Jauslin (19:47)
  Rapha�l (19:39)
  Till� (19:64)
  
  * checking for non-standard things in the check directory ... NOTE
    Found the following files/directories:
    'examples_i386' 'examples_x64'
    'WaveSampling-Ex_i386.Rout' 'WaveSampling-Ex_x64.Rout'


  
