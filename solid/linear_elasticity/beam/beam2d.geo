h = 0.1;
L = 10;
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

Physical Line("clamped") = {1};
Physical Line("pressure") = {4};
Physical Surface("beam") = {6};
