# ksamp
A small kernel sampler based on the Lab 3.1 from Gary Nutt's book Operating Systems. 


The kernel sampler (ksamp) application accepts three various forms. The first form is it's natural form "./ksamp", which will just show the basic info of the CPU Info, Time since last reboot, and processes created since last reboot.
  
  If you use "./ksamp -s", it will show the information from the natural form along with the CPU times (user mode, kernel mode, and idle time), Disk Read/Write stats, number of context switches, time of last reboot (in time/date form).
 
  The third and final form, "./ksamp -l" accepts two arguments after the optional l form. The arguments are two integers (the program will create integers if floats are given), the first one, the sampling time is the amount of time the program will wait to sample. The next number, the observation time, is how long each sample collection will last. So for instance, "./ksamp -l 2 60" means that for 60 seconds, the program will sample the kernel every 2 seconds. This sampling is done in the loadAverages() function, and allows us to sample the load averages over a set amount of time. The third part ( "-l" ) also differs in the fact that it shows the available memory and memory configured. 
