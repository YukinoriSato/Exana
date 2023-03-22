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
    Here, Exana is verified using Pin 3.7 for Intel64 linux on CentOS 7.
    
% wget https://software.intel.com/sites/landingpage/pintool/downloads/pin-3.7-97619-g0d0c92f4f-gcc-linux.tar.gz

For information about Pin tool kit, please check: https://software.intel.com/content/www/us/en/develop/articles/pin-a-dynamic-binary-instrumentation-tool.html

Unpack the pin-3.7 (Due to the API update of Pin after 3.8, the current ExanaPkg can be executed before pin-3.7)
    
* cd pin-3.7xxxx/source/tools
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

