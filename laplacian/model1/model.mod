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
      "k11": "42",
      "k12": "0",
      "k13": "0",
      "k22": "0",
      "k23": "0",
      "k33": "0",
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
        "inflow":
        {
          "expr":"4*Um*y*( H-y )/H^2:y:Um:H"
        },
        "wall":
        {
          "expr":"0"
        },
        "cylinder":
        {
          "expr":"0"
        }
      },
      "Neumann":
      {
        "outlet":
        {
          "expr":"{0,0,0,0}"
        }
      }
    }
  }, // BoundaryConditions
  "PostProcess":
  {
    "Force":["cylinder"],
    "PressureDifference":
    {
      "x1":"{0.15,0.2}",
      "x2":"{0.25,0.2}"
    }
  }
}

