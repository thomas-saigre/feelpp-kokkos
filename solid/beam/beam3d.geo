h = 1;
L = 5;
R = 1;

Point(1) = {0, R, 0, h};
Point(2) = {0, -R, 0, h};
Point(3) = {L, R, 0, h};
Point(4) = {L, -R, 0, h};

Line(1) = {1, 2};
Line(2) = {2, 4};
Line(3) = {4, 3};
Line(4) = {3, 1};

Line Loop(5) = {1, 2, 3, 4};
Plane Surface(6) = {5};
Extrude{0,0,1}{ Surface{6};  }
Extrude{0,0,1}{ Surface{28};  }


//Physical Line("clamped") = {1};
Physical Line("tip") = {10};

Physical Surface("clamped") = {15,37};
Physical Surface("pressure") = {19,41};
Physical Volume("Copper") = {1};
Physical Volume("Iron") = {2};


