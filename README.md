# Exana

------------------------------------------------------------------------------

Exana: EXecution-driven Application aNAlysis tool

Copyright (C)   2014-2018,   Yukinori Sato
All Rights Reserved. 

------------------------------------------------------------------------------

Please check [ExanaPkg](https://github.com/YukinoriSato/ExanaPkg), a packaged version (pre-compiled into binary code) with utility tools.

Currently, Exana provide the following functions:
* LCCT (Loop and call context tree)
* LCCT+M (Loop and call context tree with memory dataflow)
* MemPat (Memory access pattern analysis)
* Working set analysis
* C2Sim (Advanced cache simulation with line-conflict detection, see the following "EuroPar 2017" paper) 

## How to build
* Download Pin tool kit Intel64 linux.

    For information about Pin tool kit, please check:
    	http://pintool.org/ 
    Here, Exana is verified using Pin 3.4 rev 97438 for Intel64 linux on CentOS 7.  (For Pin-2.x and CentOS 6, please use the previous version uploaded on Sep 2017.)

* Unpack the pin-3.4-97438-gf90d1f746-gcc-linux
* cd pin-3.4/source/tools
* git clone https://github.com/YukinoriSato/Exana.git
* cd Exana
* make


## How to run
Run Exana with your target:
* pin -t obj-intel64/Exana.so -- ./a.out [input.dat]

ExanaPkg is provided as an utility for Exana.
For more details, please check HowToUse in ExanaPkg.


## Citation and Details for Exana

The canonical publication to cite Exana and ExanaPkg is:

* Yukinori Sato and Toshio Endo. “An Accurate Simulator of Cache-line Conflicts to Exploit the Underlying Cache Performance” 23rd International Europian Conference on Parallel and Distributed Computing (Euro-Par 2017), August 2017. (DOI: 10.1007/978-3-319-64203-1_9) [PDF (Author created version)](https://www.perf.cs.tut.ac.jp/~yukinori/EuroPar2017-sato-author-created-version.pdf)


* Yukinori Sato, Shimpei Sato, and Toshio Endo. Exana: An Execution-driven Application Analysis Tool for Assisting Productive Performance Tuning. Proceedings of the 2nd Workshop on Software Engineering for Parallel Systems (SEPS 2015), held in conjunction with SPLASH2015, Pages 1-10, October 2015. (DOI: 10.1145/2837476.2837477)


Please read the following papers if you are interested in detail techniques behind Exana:

* Yukinori Sato, Yasushi Inoguchi, Tadao Nakamura. Identifying Program Loop Nesting Structures during Execution of Machine Code. IEICE Transaction on Information and Systems, Vol.E97-D, No.9, pp.2371-2385, Sep. 2014. (DOI:10.1587/transinf.2013EDP7455)

* Yukinori Sato, Yasushi Inoguchi and Tadao Nakamura. Whole Program Data Dependence Profiling to Unveil Parallel Regions in the Dynamic Execution. In Proceedings of 2012 IEEE International Symposium on Workload Characterization (IISWC 2012). (DOI:10.1109/IISWC.2012.6402902) 

