h = 0.05;
Mesh.RecombinationAlgorithm=0;
xi = 0;
xf = 2.2;
yi =0;
yf = 0.41;

xc = 0.2;
yc = 0.2;
R = 0.05;

p1 = newp; Point(p1) = {xi,yi,0.0,h};
p2 = newp; Point(p2) = {(xf-xi)/2,yi,0.0,h};
p3 = newp; Point(p3) = {xf,yi,0.0,h};
p4 = newp; Point(p4) = {xf,yf,0.0,h};
p5 = newp; Point(p5) = {(xf-xi)/2,yf,0.0,h};
p6 = newp; Point(p6) = {xi,yf,0.0,h};
l1 = newl; Line(l1) = {p1,p2};
l2 = newl; Line(l2) = {p2,p3};
l3 = newl; Line(l3) = {p3,p4};
l4 = newl; Line(l4) = {p4,p5};
l5 = newl; Line(l5) = {p5,p6};
l6 = newl; Line(l6) = {p6,p1};
l7 = newl; Line(l7) = {p5,p2};
ll1 = newll; Line Loop(ll1) = {l1, -l7, l5, l6};
ll2 = newll; Line Loop(ll2) = {l2,l3,l4,l7};

p5 = newp; Point(p5) = {xc,yc,0.0,h/6};
p6 = newp; Point(p6) = {xc-R,yc,0.0,h/6};
p7 = newp; Point(p7) = {xc,yc+R,0.0,h/6};
p8 = newp; Point(p8) = {xc+R,yc,0.0,h/6};
p9 = newp; Point(p9) = {xc,yc-R,0.0,h/6};
l8 = newl; Circle(l8) = {p6,p5,p7};
l9 = newl; Circle(l9) = {p7,p5,p8};
l10 = newl; Circle(l10) = {p8,p5,p9};
l11 = newl; Circle(l11) = {p9,p5,p6};
ll3 = newll; Line Loop(ll3) = {l8,l9,l10,l11};


s1 = news; Plane Surface(s1) = {ll1,ll3};
s2 = news; Plane Surface(s2) = {ll2};
Physical Line("left") = {l6};
Physical Line("right") = {l3};
Physical Line("wall_in") = {l1,l5};
Physical Line("wall_out") = {l2,l4};
Physical Line("cylinder") = {l8,l9,l10,l11};
Physical Surface("fluid") = {s1};
Physical Surface("concrete") = {s2};
