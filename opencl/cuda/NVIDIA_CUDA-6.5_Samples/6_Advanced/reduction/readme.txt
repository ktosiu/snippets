This code uses the shuffle operation when available to reduce
warp synchronization and various costs associated with shared
memory access as opposed to register access. For devices that 
do not support this instruction, the last warp worth of work
is unrolled to reduce looping overhead. While it is tempting
to remove synchronization when operating strictly within a 
single warp like this, such "warp synchronous" programming
is generally discouraged because it can lead to brittle
code.
