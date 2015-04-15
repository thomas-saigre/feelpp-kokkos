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
      "k11": "42"
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
    "Force":["cylinder"],
    "PressureDifference":
    {
      "x1":"{0.15,0.2}",
      "x2":"{0.25,0.2}"
    }
  }
}

