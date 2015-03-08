dim = 2;
h = 0.025;
hscale = 2;
hcyl= h/hscale;
shape="cylinder";
//shape="square";
H = 0.41;
D = 0.1;
R = 0.05;
L = 2.2;
xc = 0.2;
yc = 0.2;

Point(1) = {0,0,0,h};
Point(2) = {L,0,0,h};
Point(3) = {L,H,0,h};
Point(4) = {0,H,0,h};

Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};

Line Loop(20)={1,2,3,4};

// cylinder
If ( StrCmp(shape, "cylinder" ) == 0 )
  Point(5) = {xc,yc,0,hcyl};
  Point(6) = {xc+R,yc,0,hcyl};
  Point(7) = {xc-R,yc,0,hcyl};
  Point(8) = {xc,yc+R,0,hcyl};
  Point(9) = {xc,yc-R,0,hcyl};
  
  Point( 11 ) = {0.1, 0.2, 0, hcyl};
  Point( 12 ) = {0.2, 0.3, 0, hcyl};
  Point( 13 ) = {0.2, 0.1, 0, hcyl};
  Point( 14 ) = {L, 0.1, 0, hcyl};
  Point( 15 ) = {L, 0.3, 0, hcyl};
  
  Circle(5) = {6,5,8};
  Circle(6) = {8,5,7};
  Circle(7) = {7,5,9};
  Circle(8) = {9,5,6};
EndIf
If ( StrCmp(shape, "square" ) == 0)
  // square : 
  X = 0.15; 
  Y = 0.15; 
  Point(5) = {X,Y,0,hcyl}; 
  Point(6) = {X,Y+D,0,hcyl}; 
  Point(7) = {X+D,Y+D,0,hcyl}; 
  Point(8) = {X+D,Y,0,hcyl}; 
  Line(5) = {8,7}; 
  Line(6) = {7,6}; 
  Line(7) = {6,5}; 
  Line(8) = {5,8}; 
EndIf

Line Loop(21) = {5,6,7,8};
Plane Surface(30) = {20,-21};

If ( dim == 2 )
  Physical Line("inflow") = {4};
  Physical Line("wall") = {3,1};
  Physical Line("cylinder") = {5,6,7,8};
  Physical Line("outflow") = {2};
  
  Physical Surface("fluid")={30};
EndIf

If ( dim == 3 )
  out[]=Extrude {0,0,H} {  Surface{30}; };
  
  out[1]=30;
  Surface Loop(55) = {out[]};
  Volume(1) = {55};
  
  Physical Surface("inflow") = {55};
  Physical Surface("wall") = {30,43,51,72};
  Physical Surface("cylinder") = {59,63,67,71};
  Physical Surface("outflow") = {47};
  Physical Volume("fluid")={1};
EndIf

