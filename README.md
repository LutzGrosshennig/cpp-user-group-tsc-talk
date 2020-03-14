# cpp-user-group-tsc-talk
This is a minimal and very easy to understand example of TSC usage shown during my presentation at the CPP user group Bremen-Oldenburg meeting.

The joy and perils of the Intel timestamp counters

Abstract:

The TSC was introduced with the first Intel Pentium processors and offered a very simple method to perform time measurements with a precesion down to a single clockcycle. Back in thoose days live was simple. You usally only had one core, no out-of-order execution and since a CPU only required around 15-30 Watts no real need for power savings mechanisms like SpeedStep. CPUs allways ran at a fixed Clockspeed. A simple RDTSC would give us a 64 Bit Value (in EAX:EDX) that represents the current amount a clockcycles elapsed since the CPU was powered on. At this time each clockcycle took a fixed amount of time since there was no variation of the CPU clock. Live was easy.

With the dawn of the Pentium-II out-of-order execution came into play and unfortunatly the RDTSC command was not designed to be a serializing instruction. This is the beginning of the demise of the RDTSC instruction. The usual workaround back at the time was to call a serializing CPUID instruction prior to the RDTSC call. Of course that added additional cycles to the measurement process. However we still had a fixed clockspeed and a fixed amount of time between each clock cycle. Live was still simple yet a bit akward.

The Pentium III came and with the mobile version of the Pentium III Speedstep was introduced to save power. While this is good for the battery and the it wrecked havoc on the timestamp counters because now the clock cyle rate can vary at any moment and thus we could still measure the amount of clockcycles but we cant transform this into a timespan anymore.

While the Pentium 4 (Willamette and Northwood) core does not have Speedstep another technology came into play to give the timestamp counters a hard time: Thermal Throttling. While this was a great technology by itself it behaves rather odd. When thermal throttling is active on said P4 Core it will not lower the clock speed! The core just stops doing things for a certain amount of time. So we see a variation in the execution time!

Up and until this time running an SMP system did not make much of a difference since all CPU 
