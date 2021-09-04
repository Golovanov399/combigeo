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

end