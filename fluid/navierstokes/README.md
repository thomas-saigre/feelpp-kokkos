
# backward step

## Parameters

the parameters are
 - `rho`
 - `mu` : viscosity of the fluid
 - `umax` : 
 - `L`: the length of the channel
 
## Execution

here is a possible command line to run the code on `nprocs` 
```
mpirun -np <nprocs> ./feelpp_qs_ns_2d --config-file step/step_2d.cfg --bc-file $PWD/step/step_2d.bc 
```
