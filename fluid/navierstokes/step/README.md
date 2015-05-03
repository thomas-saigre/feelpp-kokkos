Backward Step {#QSNSStep}
=========================

[TOC]

# Description {#description}

Let us consider the standard backward-facing step benchmark. The inflow is at
\f$x=-1\f$ and the outflow is at \f$x=5\f$ for \f$Re=10\f$ and \f$Re=100\f$, and at \f$x=10\f$ for
\f$Re=200\f$.

A Poiseuille flow profile is imposed on the inflow boundary, a no-flow condition
is imposed on the wall and a Newmann condition is applied at the outflow
boundary. The 2D and 3D Poiseuille profile are defined as follows respectively:

\f[
\mathbf{u}=(6y(1-y),0), \qquad \mathbf{u}=(6y(1-y),0,0)
\f]

The relative contribution of the convection and diffusion are defined by the
Reynolds number:

\f[Re=\frac{UD}{\nu}\f]

where \f$U\f$ is the mean of the velocity at the inflow, \f$D\f$ is the characteristic
length scale of the domain, here the width of the step (\f$D=2\f$).




The parameters are
 - `rho`
 - `mu` : viscosity of the fluid
 - `umax` : 
 - `L`: the length of the channel
 
# Execution {#execution}

## 2D

here is a possible command line to run the code on `nprocs` 
```
mpirun -np <nprocs> ./feelpp_qs_ns_2d --config-file step/step_2d.cfg 
```

## 3D

here is a possible command line to run the code on `nprocs` 
\code
mpirun -np <nprocs> ./feelpp_qs_ns_3d --config-file step/step_3d.cfg 
\endcode

# Complete Code

\snippet 
