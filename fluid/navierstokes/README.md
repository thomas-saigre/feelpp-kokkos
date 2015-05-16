Quicktart Navier-Stokes {#QSNS}
===============================

[TOC]


# Introduction {#intro}


\note: The source code of this example is available in \c quickstart/qs_ns.cpp

# Algebraic solution {#linalg}

We will deal with the nonlinear system arising from the discrete Navier-Stokes
equations by using either Picard or Newton iterations as seen in the previous
section. The initial iterate \f$(\mathbf{u}_0, p_0)\f$ is obtained by solving
the corresponding discrete Stokes problem.

The stopping criterion of the nonlinear iteration is when the vector Euclidean
norm of the nonlinear residual has a relative error of \f$10^{-5}\f$, that is

\f{equation}{
\label{eq:criterion}
\| \begin{pmatrix} \mathbf{f} - \left( \mathbf{F}(\mathbf{u}^{m})\mathbf{u}^{(m)} + B^Tp^{(m)}\right)\\ \mathbf{g} - B\mathbf{u}^{(m)}\end{pmatrix} \|  \leq 10^{-5} \| \begin{pmatrix} \mathbf{f}\\ \mathbf{g}\end{pmatrix}\|
\f}

As for the starting vector for the linearized iteration it is set to zero and the stopping criterion is

\f[ \|\mathbf{r}^{(k)}\| \leq 10^{-6}\|\mathbf{s}^{(m)}\| , \f]

where \f$\mathbf{r}^{(k)}\f$ is the residual of the linear system and
\f$\mathbf{s}^{(m)}\f$
is the left-hand side residual in (\ref{eq:criterion}) associated with the final
nonlinear system.


# Models {#models}

 - \subpage QSNSStep
 
# Complete Code {#QSNSCode}

\snippet qs_ns.cpp marker1
