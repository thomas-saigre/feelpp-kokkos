// -*- mode: javascript -*- vim:set ft=javascript:
{
  "Name": "QuickStart - Model - Tutorial",
  "Model": "Dummy",
  "Description":"Anisotropic diffusion - Model framework",
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
    "fluid": //Marker on the mesh
    {
      "name": "Watter", // Name of the material - no reason to be the same as the marker
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
      "filename":"$feelpp_builddir/quickstart/laplacian/concrete.json"
    }
  },
  "BoundaryConditions":
  {
    "heat":
    {
      "dirichlet":
      {
        "left":
        {
          "expr":"2"
        },
        "wall_in":
        {
          "expr":"(x<0.55)*2+(x>0.55*4):x"
        },
        "wall_out":
        {
          "expr":"3"
        },
        "cylinder":
        {
          "expr":"cos(x)*sin(y):x:y"
        },
        "right":
        {
          "expr":"x:x"
        }
      }
    }
  }, // BoundaryConditions
  "PostProcess":
  {
    "Fields":["diffused","k11","k33"]
  }
}

