Laplacian {#QSLaplacian}
=========

[TOC]

\note The source code of this example is available [here](qs_laplacian.cpp).

# Introduction {#QSLaplacianintro}

As an introduction to the aim and the way to do with Feel++, we provide a sort of
`Hello World` program to evaluate the library. We solve for the laplacian
with Dirichlet boundary conditions.

# Problem setup {#QSLaplaciansetup}

We want to solve the following problem:<br>
\f[ - \Delta u = 1,\quad u_{|\partial \Omega} = g \f]
where \f$\Omega \in \mathbb{R}^n, n\in{1,2,3}\f$.<br>

The variational form reads: looks for \f$u \in H^1_g\left( \Omega \right) = \{ v \in H^1(\Omega) | v = g \mbox{ on } \partial \Omega \}\f$
such that
\f[a\left( u,v \right) = l\left( v \right)\quad \forall v \in H^1\left( \Omega \right).\f]
with:
\f[a\left( u,v \right) = \int_{\Omega} \nabla u \cdot \nabla v ,\quad l\left( v \right) = \int_{\Omega} v \f]

The aim of \feel is to provide the simplest way to write the \f$a\f$ and \f$l\f$
forms.

From a discrete point of view, we introduce \f$V_h\subset H^1\left( \Omega \right)\f$ such that:
<br><center>\f$
  \begin{aligned}
V_h = \left\{ v \in C^0\left( \Omega \right), \forall K\in \mathcal{T}_h, \right.v\left|_K \in P_1\left( K \right) \right\},
    \end{aligned}
\f$</center><br>
where \f$\mathcal{T}_h\f$ is the set of element \f$K\f$ forming the mesh of \f$\Omega\f$. <br>
We now look for \f$u_h \in V_h\f$ such that:
<br><center>\f$
  \begin{aligned}
    \forall v_h\in V_h, a\left( u_h,v_h \right)=l\left( v_h \right).
    \end{aligned}
\f$</center><br>

# Code description {#QSLaplaciancode}

This section is here to declare that we want to use the namespace \feel, to
passe the command line options to the created environnement and add some
informations (basics \feel options, application name).
~~~~~~{.cpp}
using namespace Feel;
Environment env( _argc=argc, _argv=argv,
                 _desc=feel_options(),
                 _directory=".",
                 _about=about(_name="qs_laplacian",
                 _author="Feel++ Consortium",
                 _email="feelpp-devel@feelpp.org"));
~~~~~~
We have to define the mesh, the approximation space and our test and trial
functions.
~~~~~~{.cpp}
auto mesh = unitSquare();
auto Vh = Pch<1>( mesh );
auto u = Vh->element();
auto v = Vh->element();
~~~~~~
We create now our bilinear and linear forms, we add the homogeneous Dirichlet
conditions and solve the discretized (linear) system.
~~~~~~{.cpp}
auto l = form1( _test=Vh );
l = integrate(_range=elements(mesh),
              _expr=id(v));

auto a = form2( _trial=Vh, _test=Vh );
a = integrate(_range=elements(mesh),
              _expr=gradt(u)*trans(grad(v)) );

a+=on(_range=boundaryfaces(mesh), _rhs=l, _element=u,
      _expr=constant(0.) );
a.solve(_rhs=l,_solution=u);
~~~~~~
\feel provides the possibility to save the results:
~~~~~~{.cpp}
auto e = exporter( _mesh=mesh );
e->add( "u", u );
e->save();
return 0;
~~~~~~

# Complete code {#QSLaplacianCompleteCode}

\snippet qs_laplacian.cpp global

# First execution & visualization {#QSLaplacianExec}

To test that part of code, please go to:
~~~~~~
cd $FeelppBuildDir/quickstart
~~~~~~

and execute the code, by:
~~~~~~
./feelpp_qs_laplacian
~~~~~~

This will produce several files in directory `$HOME/feel/qs_laplacian/np_1/`:
~~~~~~
  feel.geo
  feel.msh
  qs_laplacian.case
  qs_laplacian.u-1_0.001
~~~~~~  

You can visualize the results using any Ensight file reader, such as Paraview,
opening <tt>qs_laplacian-paraview-1.sos</tt>.
~~~~~~
  paraview qs_laplacian-paraview-1.sos
~~~~~~  

You may have a look to the options provided by the application
~~~~~~  
  ./feelpp_qs_laplacian --help
~~~~~~  


as well as the options provided by the Feel++ library
~~~~~~  
  ./feelpp_qs_laplacian --help-lib
~~~~~~  
