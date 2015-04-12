dim = 2;
h = 0.1;
H = 1;
L = 2;
Point(1) = {0,0,0,h};
Point(2) = {L,0,0,h};
Point(3) = {L,H,0,h};
Point(4) = {0,H,0,h};

Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};

Line Loop(20)={1,2,3,4};

Plane Surface(30) = {20};

If ( dim == 2 )
  Physical Line("inflow") = {4};
  Physical Line("wall") = {3,1};
  Physical Line("outflow") = {2};
  Physical Surface("fluid")={30};
EndIf

If ( dim == 3 )

  Extrude {{L, 0, 0}, {0, 0, 0}, Pi/2} { Surface{30}; }
  Extrude {{L, 0, 0}, {0, 0, 0}, Pi/2} { Surface{47}; }
  Extrude {{L, 0, 0}, {0, 0, 0}, Pi/2} { Surface{64}; }
  Extrude {{L, 0, 0}, {0, 0, 0}, Pi/2} { Surface{81}; }

  Physical Surface("inflow") = {97, 46, 63, 80};
  Physical Surface("wall") = {60, 43, 94, 77};
  Physical Surface("outflow") = {56, 73, 90, 39};

  Physical Volume("fluid")={1,2,3,4};
EndIf
