prologues:=3;
verbatimtex
%&latex
\documentclass{minimal}

\begin{document}
etex

outputtemplate := "fig.mps";
beginfig(0);

r = 1cm;
R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (-0.866025, 0.500000) scaled r;
d[1][1] = (-0.866025, -0.500000) scaled r;
d[1][2] = (0.866025, -0.500000) scaled r;
d[1][3] = (0.866025, 0.500000) scaled r;
d[2][0] = (0.953181, 1.496195) scaled r;
d[2][1] = (-0.953181, 1.496195) scaled r;
d[2][2] = (-1.850833, 0.673648) scaled r;
d[2][3] = (-1.850833, -0.326352) scaled r;
d[2][4] = (-1.508813, -1.266044) scaled r;
d[2][5] = (1.573132, -1.207107) scaled r;
d[2][6] = (1.866025, 0.500000) scaled r;

fill small withcolor .7 * white;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 3:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 6:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
draw subpath(0.666667, 0.777778) of (big shifted d[1][0]) withcolor .3 * white;
draw subpath(6.444444, 7.333333) of (big shifted d[1][1]) withcolor .3 * white;
draw subpath(4.666667, 5.666667) of (big shifted d[1][2]) withcolor .3 * white;
draw subpath(3.222222, 3.333333) of (big shifted d[1][3]) withcolor .3 * white;
draw subpath(4.391151, 4.555556) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(0.000000, 3.608849) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(7.444444, 7.608849) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(0.391151, 3.777778) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(2.111111, 4.666667) of (big shifted d[2][2]) withcolor .3 * white;
draw subpath(3.333333, 5.111111) of (big shifted d[2][3]) withcolor .3 * white;
draw subpath(3.777778, 7.777778) of (big shifted d[2][4]) withcolor .3 * white;
draw subpath(4.333333, 8.000000) of (big shifted d[2][5]) withcolor .3 * white;
draw subpath(0.000000, 1.116986) of (big shifted d[2][5]) withcolor .3 * white;
draw subpath(6.450320, 8.000000) of (big shifted d[2][6]) withcolor .3 * white;
draw subpath(0.000000, 1.888889) of (big shifted d[2][6]) withcolor .3 * white;

endfig;


outputtemplate := "fig_reg.mps";
beginfig(1);

numeric r, R;
r = 1cm;
R = 3r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (-0.866025, 0.500000) scaled r;
d[1][1] = (-0.866025, -0.500000) scaled r;
d[1][2] = (0.866025, -0.500000) scaled r;
d[1][3] = (0.866025, 0.500000) scaled r;
d[2][0] = (0.953181, 1.496195) scaled r;
d[2][1] = (-0.953181, 1.496195) scaled r;
d[2][2] = (-1.850833, 0.673648) scaled r;
d[2][3] = (-1.850833, -0.326352) scaled r;
d[2][4] = (-1.508813, -1.266044) scaled r;
d[2][5] = (1.573132, -1.207107) scaled r;
d[2][6] = (1.866025, 0.500000) scaled r;


for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed withdots scaled 0.2;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 3:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed withdots scaled 0.2;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 6:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed withdots scaled 0.2;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
draw d[1][0]--d[0][0];
draw d[1][1]--d[0][0];
draw d[1][2]--d[0][0];
draw d[1][3]--d[0][0];
draw d[2][0]--d[1][3];
draw d[2][1]--d[1][0];
draw d[2][2]--d[1][0];
draw d[2][3]--d[1][1];
draw d[2][4]--d[1][1];
draw d[2][5]--d[1][2];
draw d[2][6]--d[1][3];
for i := 0 step 1 until 6:
  draw d[2][i]--(d[2][i] scaled (R / abs(d[2][i])));
endfor;

pickup pencircle scaled 0.25;
for i := 0 step 1 until 6:
  draw d[0][0]--d[2][i] dashed evenly;
endfor;

pickup pencircle scaled 0.5;
pickup pencircle;
draw subpath(0.666667, 0.777778) of (big shifted d[1][0]) withcolor .5 * white;
draw subpath(6.444444, 7.333333) of (big shifted d[1][1]) withcolor .5 * white;
draw subpath(4.666667, 5.666667) of (big shifted d[1][2]) withcolor .5 * white;
draw subpath(3.222222, 3.333333) of (big shifted d[1][3]) withcolor .5 * white;
draw subpath(4.391151, 4.555556) of (big shifted d[2][0]) withcolor .5 * white;
draw subpath(0.000000, 3.608849) of (big shifted d[2][0]) withcolor .5 * white;
draw subpath(7.444444, 7.608849) of (big shifted d[2][1]) withcolor .5 * white;
draw subpath(0.391151, 3.777778) of (big shifted d[2][1]) withcolor .5 * white;
draw subpath(2.111111, 4.666667) of (big shifted d[2][2]) withcolor .5 * white;
draw subpath(3.333333, 5.111111) of (big shifted d[2][3]) withcolor .5 * white;
draw subpath(3.777778, 7.777778) of (big shifted d[2][4]) withcolor .5 * white;
draw subpath(4.333333, 8.000000) of (big shifted d[2][5]) withcolor .5 * white;
draw subpath(0.000000, 1.116986) of (big shifted d[2][5]) withcolor .5 * white;
draw subpath(6.450320, 8.000000) of (big shifted d[2][6]) withcolor .5 * white;
draw subpath(0.000000, 1.888889) of (big shifted d[2][6]) withcolor .5 * white;

endfig;


outputtemplate := "traversal.mps";
beginfig(2);


numeric r, R;

r = 2cm;
R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (-0.866025, 0.500000) scaled r;
d[1][1] = (-0.866025, -0.500000) scaled r;
d[1][2] = (0.866025, -0.500000) scaled r;
d[1][3] = (0.866025, 0.500000) scaled r;
d[2][0] = (0.953181, 1.496195) scaled r;
d[2][1] = (-0.953181, 1.496195) scaled r;
d[2][2] = (-1.850833, 0.673648) scaled r;
d[2][3] = (-1.850833, -0.326352) scaled r;
d[2][4] = (-1.508813, -1.266044) scaled r;
d[2][5] = (1.573132, -1.207107) scaled r;
d[2][6] = (1.866025, 0.500000) scaled r;
for i := 0 step 1 until 0:
  pickup pencircle scaled 0.25;
  draw small shifted d[0][i];  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 3:
  pickup pencircle scaled 0.25;
  draw small shifted d[1][i];  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 6:
  pickup pencircle scaled 0.25;
  draw small shifted d[2][i];  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[0][0]--d[1][2];
drawarrow d[0][0]--d[1][3];
drawarrow d[1][3]--d[2][0];
drawarrow d[1][0]--d[2][1];
drawarrow d[1][0]--d[2][2];
drawarrow d[1][1]--d[2][3];
drawarrow d[1][1]--d[2][4];
drawarrow d[1][2]--d[2][5];
drawarrow d[1][3]--d[2][6];

label.rt(btex$D_1$etex, d[0][0] shifted (r/6, 0));
label.lrt(btex$D_2$etex, d[1][3]);
label.rt(btex$D_3$etex, d[2][6]);
label.urt(btex$D_4$etex, d[1][3]);
label.top(btex$D_5$etex, d[2][0]);
label.ulft(btex$D_6$etex, d[1][3]);
label.top(btex$D_7$etex, d[0][0] shifted (0, r/8));
label.urt(btex$D_8$etex, d[1][0]);
label.top(btex$D_9$etex, d[2][1]);
label.ulft(btex$D_{10}$etex, d[1][0] shifted (0, r/8));
label.lft(btex$D_{11}$etex, d[2][2]);
label.llft(btex$D_{12}$etex, d[1][0]);
label.lft(btex$D_{13}$etex, d[0][0] shifted (-r/8, 0));
label.top(btex$D_{14}$etex, d[1][1] shifted (0, r/8));
label.lft(btex$D_{15}$etex, d[2][3]);
label.llft(btex$D_{16}$etex, d[1][1] shifted (-r/8, 0));
label.llft(btex$D_{17}$etex, d[2][4]);
label.lrt(btex$D_{18}$etex, d[1][1]);
label.bot(btex$D_{19}$etex, d[0][0] shifted (0, -r/8));
label.llft(btex$D_{20}$etex, d[1][2]);
label.lrt(btex$D_{21}$etex, d[2][5]);
label.urt(btex$D_{22}$etex, d[1][2]);

endfig;


outputtemplate := "only_inner.mps";
beginfig(3);


numeric r, R;

r = 1cm;
R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.866025, 0.500000) scaled r;
d[1][1] = (-0.866025, 0.500000) scaled r;
d[2][0] = (0.953181, 1.496195) scaled r;
d[2][1] = (-0.953181, 1.496195) scaled r;
for i := 0 step 1 until 0:
  fill big shifted d[0][i] withcolor .9 * white;endfor;

for i := 0 step 1 until 1:
  fill big shifted d[1][i] withcolor .9 * white;endfor;

for i := 0 step 1 until 1:
  fill big shifted d[2][i] withcolor .9 * white;endfor;

for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  pickup pencircle scaled 0.5;
endfor;


fill small withcolor .7 * white;
pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];

pickup pencircle scaled 0.5;
draw small shifted ((-1.772333, 0.922618) scaled r);
pickup pencircle scaled 0.25;
draw big shifted ((-1.772333, 0.922618) scaled r) dashed evenly scaled 0.5;

endfig;


outputtemplate := "pentagon.mps";
beginfig(4);

numeric r;
r = 5cm;
pair a, b, c, d, e, f, m;
a = (0, 0);
b = (r, 0) rotated 50;
e = (r, 0) rotated 130;
c = (r, 0) rotated 100 shifted b;
d = (fullcircle scaled (2 * r) shifted c) intersectionpoint (fullcircle scaled (2 * r) shifted e);

m = .5[b, e];
f = b shifted e;

draw a--b--c--d--e--cycle;
draw b--f--e dashed evenly;

dotlabel.bot(btex$A$etex, a);
dotlabel.rt(btex$B$etex, b);
dotlabel.urt(btex$C$etex, c);
dotlabel.ulft(btex$D$etex, d);
dotlabel.lft(btex$E$etex, e);
dotlabel.top(btex$F$etex, f);

endfig;

outputtemplate := "pentagon_wrong.mps";
beginfig(5);

numeric r;
r = 5cm;
pair a, b, c, d, e, f, m, p;
a = (0, 0);
b = (r, 0) rotated 80;
e = (r, 0) rotated 100;
c = (r, 0) rotated 75 shifted b;
d = (fullcircle scaled (2 * r) shifted c) intersectionpoint (fullcircle scaled (2 * r) shifted e);

m = .5[b, e];
f = b shifted e;
p = whatever[a, f] = whatever[c, d];

draw a--b--c--d--e--cycle;
% draw b--f--e dashed evenly;
draw b--p--e dashed evenly;

dotlabel.bot(btex$A$etex, a);
dotlabel.rt(btex$B$etex, b);
dotlabel.urt(btex$C$etex, c);
dotlabel.ulft(btex$D$etex, d);
dotlabel.lft(btex$E$etex, e);
% dotlabel.top(btex$F$etex, f);
dotlabel.top(btex$P$etex, p);
label.llft(btex$>\frac{\pi}{3}$etex, p);
label.lrt(btex$>\frac{\pi}{3}$etex, p);
label.lft(btex$1$etex, .5[d, e]);
label.rt(btex$1$etex, .5[b, c]);
label.top(btex$<1$etex, .5[d, p]);
label.top(btex$<1$etex, .5[c, p]);
label.urt(btex$<1$etex, .5[b, p]);
label.ulft(btex$<1$etex, .5[e, p]);

endfig;


outputtemplate := "case-%c.mps";
beginfig(1);

% ld psi = deg(100);
% ld v1u2 = deg(50);
% ld u1v2 = deg(40);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.766044, 0.642788) scaled r;
d[1][1] = (-0.766044, 0.642788) scaled r;
d[2][0] = (0.766044, 1.642788) scaled r;
d[2][1] = (-0.592396, 1.627595) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[2][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.444444, 2.965040) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(1.063437, 2.444444) of (big shifted d[2][1]) withcolor .3 * white;

endfig;


beginfig(2);

% ld psi = deg(100);
% ld v1u2 = deg(90);
% ld u1v2 = deg(50);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.766044, 0.642788) scaled r;
d[1][1] = (-0.766044, 0.642788) scaled r;
d[2][0] = (1.408832, 1.408832) scaled r;
d[2][1] = (-0.766044, 1.642788) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[1][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.000000, 3.777778) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(2.444444, 2.734267) of (big shifted d[1][0]) withcolor .3 * white;
draw subpath(7.793172, 8.000000) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(0.000000, 2.555556) of (big shifted d[2][1]) withcolor .3 * white;

endfig;

beginfig(3);

% ld psi = deg(100);
% ld v1u2 = deg(80);
% ld u1v2 = deg(70);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.766044, 0.642788) scaled r;
d[1][1] = (-0.766044, 0.642788) scaled r;
d[2][0] = (1.266044, 1.508813) scaled r;
d[2][1] = (-1.108065, 1.582480) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[1][1])) dashed evenly;
drawarrow d[1][1]--((big shifted d[1][0]) intersectionpoint (big shifted d[1][1])) dashed evenly;
drawarrow d[1][1]--((big shifted d[1][1]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[1][1]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.111111, 4.000000) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(2.666667, 3.111111) of (big shifted d[1][0]) withcolor .3 * white;
draw subpath(0.888889, 1.111111) of (big shifted d[1][1]) withcolor .3 * white;
draw subpath(7.777778, 8.000000) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(0.000000, 2.777778) of (big shifted d[2][1]) withcolor .3 * white;

endfig;

beginfig(4);

% ld psi = deg(140);
% ld v1u2 = deg(50);
% ld u1v2 = deg(50);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.939693, 0.342020) scaled r;
d[1][1] = (-0.939693, 0.342020) scaled r;
d[2][0] = (0.597672, 1.281713) scaled r;
d[2][1] = (-0.597672, 1.281713) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[2][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.444444, 2.815631) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(1.184369, 2.555556) of (big shifted d[2][1]) withcolor .3 * white;

endfig;

beginfig(5);

% ld psi = deg(130);
% ld v1u2 = deg(80);
% ld u1v2 = deg(60);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.906308, 0.422618) scaled r;
d[1][1] = (-0.906308, 0.422618) scaled r;
d[2][0] = (1.165127, 1.388544) scaled r;
d[2][1] = (-0.819152, 1.418813) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[1][0]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.111111, 4.333333) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(7.444444, 8.000000) of (big shifted d[2][1]) withpen (pencircle scaled 2) withcolor white;
draw subpath(0.000000, 2.666667) of (big shifted d[2][1]) withpen (pencircle scaled 2) withcolor white;
draw subpath(3.000000, 3.222222) of (big shifted d[1][0]) withcolor .3 * white;
draw subpath(7.444444, 8.000000) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(0.000000, 2.666667) of (big shifted d[2][1]) withcolor .3 * white;

endfig;

beginfig(6);

% ld psi = deg(123);
% ld v1u2 = deg(67);
% ld u1v2 = deg(67);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.878817, 0.477159) scaled r;
d[1][1] = (-0.878817, 0.477159) scaled r;
d[2][0] = (0.974663, 1.472555) scaled r;
d[2][1] = (-0.974663, 1.472555) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[0][0])) dashed evenly;
drawarrow d[0][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[0][0])) dashed evenly;
drawarrow d[0][0]--((big shifted d[0][0]) intersectionpoint (big shifted d[1][1])) dashed evenly;
drawarrow d[1][1]--((big shifted d[0][0]) intersectionpoint (big shifted d[1][1])) dashed evenly;
drawarrow d[1][1]--((big shifted d[1][1]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[1][1]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.255556, 4.544444) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(3.211111, 3.300000) of (big shifted d[1][0]) withcolor .3 * white;
draw subpath(1.966667, 2.033333) of (big shifted d[0][0]) withcolor .3 * white;
draw subpath(7.455556, 8.000000) of (big shifted d[2][1]) withpen (pencircle scaled 2) withcolor white;
draw subpath(0.000000, 2.744444) of (big shifted d[2][1]) withpen (pencircle scaled 2) withcolor white;
draw subpath(0.700000, 0.788889) of (big shifted d[1][1]) withcolor .3 * white;
draw subpath(7.455556, 8.000000) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(0.000000, 2.744444) of (big shifted d[2][1]) withcolor .3 * white;

endfig;

beginfig(7);

% ld psi = deg(130);
% ld v1u2 = deg(90);
% ld u1v2 = deg(90);
numeric r;
r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
d[0][0] = (0.000000, 0.000000) scaled r;
d[1][0] = (0.906308, 0.422618) scaled r;
d[1][1] = (-0.906308, 0.422618) scaled r;
d[2][0] = (1.328926, 1.328926) scaled r;
d[2][1] = (-1.328926, 1.328926) scaled r;
for i := 0 step 1 until 0:
  draw small shifted d[0][i];  pickup pencircle scaled 0.25;
  draw big shifted d[0][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[1][i];  pickup pencircle scaled 0.25;
  draw big shifted d[1][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

for i := 0 step 1 until 1:
  draw small shifted d[2][i];  pickup pencircle scaled 0.25;
  draw big shifted d[2][i] dashed evenly scaled 0.5;
  pickup pencircle scaled 0.5;
endfor;

pickup pencircle;
drawarrow d[0][0]--d[1][0];
drawarrow d[0][0]--d[1][1];
drawarrow d[1][0]--d[2][0];
drawarrow d[1][1]--d[2][1];
for i := 0 step 1 until 1:
draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));
endfor;
drawarrow d[2][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[2][0]) intersectionpoint (big shifted d[1][0])) dashed evenly;
drawarrow d[1][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[0][0])) dashed evenly;
drawarrow d[0][0]--((big shifted d[1][0]) intersectionpoint (big shifted d[0][0])) dashed evenly;
drawarrow d[0][0]--((big shifted d[0][0]) intersectionpoint (big shifted d[1][1])) dashed evenly;
drawarrow d[1][1]--((big shifted d[0][0]) intersectionpoint (big shifted d[1][1])) dashed evenly;
drawarrow d[1][1]--((big shifted d[1][1]) intersectionpoint (big shifted d[2][1])) dashed evenly;
drawarrow d[2][1]--((big shifted d[1][1]) intersectionpoint (big shifted d[2][1])) dashed evenly;

pickup pencircle scaled 1.5;
draw subpath(1.000000, 4.111111) of (big shifted d[2][0]) withcolor .3 * white;
draw subpath(2.777778, 3.222222) of (big shifted d[1][0]) withcolor .3 * white;
draw subpath(1.888889, 2.111111) of (big shifted d[0][0]) withcolor .3 * white;
draw subpath(0.777778, 1.222222) of (big shifted d[1][1]) withcolor .3 * white;
draw subpath(7.888889, 8.000000) of (big shifted d[2][1]) withcolor .3 * white;
draw subpath(0.000000, 3.000000) of (big shifted d[2][1]) withcolor .3 * white;

endfig;

end