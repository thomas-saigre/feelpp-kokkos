// -*- mode: javascript -*-
{
  "Name": "Turek",
  "Description":"Fluid flow around a cylinder",
  "Parameters":
  {
    "Um":
    {
      "type":"variable",
      "value":0.3,
      "min":1e-4,
      "max":10
    },
    "H":
    {
      "type":"constant",
      "value":0.41
    }
  },
  "Materials":
  {
    "fluid":
    {
      "name": "Watter",
      "rho": "0",
      "mu": "0",
      "Cp": "0", 
      "Cv": "0", 
      "k11": "1",
      "k12": "0",
      "k13": "0",
      "k22": "3",
      "k23": "0",
      "k33": "5",
      "Tref": "0",
      "beta": "0",
      "C": "0", 
      "young_modulus": "0",
      "nu": "0", 
      "sigma": "0"
    },
    "concrete":
    {
      "filename":"$feelpp_builddir/quickstart/laplacian/concrete"
    }
  },
  "BoundaryConditions":
  {
    "velocity":
    {
      "dirichlet":
      {
        "inlet":
        {
          "expr":"2"
        },
        "wall":
        {
          "expr":"3"
        },
        "cylinder":
        {
          "expr":"cos(x)*sin(y):x:y"
        },
        "outlet":
        {
          "expr":"x:x"
        }
      }
    }
  }, // BoundaryConditions
  "PostProcess":
  {
    "Force":["diffused,k_11,k_33"]
  }
}

