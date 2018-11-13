FT= ` sed -n "/#define FT / p" ../rps.h | cut -f3 -d" " `
Nx= ` sed -n "/#define Nx / p" ../rps.h | cut -f3 -d" " `
Ny= ` sed -n "/#define Ny / p" ../rps.h | cut -f3 -d" " `
NF= ` sed -n "/#define NF / p" ../rps.h | cut -f3 -d" " `

if (FT==0){
	set terminal png size Nx+56, Ny+47 crop
	ext="png"
	unset xtics
	unset ytics
	unset colorbox
}
if (FT==1){
	set terminal pdfcairo font "Times, 10" size 8.4cm, 7.0cm
	ext="pdf"
	set xtics  offset  0.0, 0.2 (0, Nx/4, Nx/2, 3*Nx/4, Nx)
	set ytics  offset  0.2, 0.0 (0, Ny/4, Ny/2, 3*Ny/4, Ny)
}

set xrange  [1:Nx]
set yrange  [1:Ny]
set cbrange [0:1 ]
set cbtics offset -0.8, 0.0
set border
set size ratio -1
unset key

set palette gray

i= 1
while (i <= NF ){
	set output sprintf("emp-%d.%s", i, ext)
	plot sprintf("../dat/phi-%d.dat", i) \
	     u ($1+1):($2+1):($3) matrix w image
	i= i+ 1
}
unset output
