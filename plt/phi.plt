Nx= ` sed -n "/#define Nx / p" ../rps.h | cut -f3 -d" " `
Ny= ` sed -n "/#define Ny / p" ../rps.h | cut -f3 -d" " `
NF= ` sed -n "/#define NF / p" ../rps.h | cut -f3 -d" " `
NS= ` sed -n "/#define NS / p" ../rps.h | cut -f3 -d" " `

set terminal png size Nx+55, Ny+55 crop
ext="png"
unset xtics
unset ytics
unset colorbox

set xrange  [1:Nx]
set yrange  [1:Ny]
set cbrange [0:NS]
set border
set size ratio -1
unset key

set palette defined ( 0 "#ffffff",\
                      1 "#ff0000",\
                      2 "#0000ff",\
                      3 "#ffff00" )

i= 1
while (i <= NF ){
	set output sprintf("phi-%d.%s", i, ext)
	plot sprintf("../dat/phi-%d.dat", i) \
	     u ($1+1):($2+1):($3) matrix w image
	i= i+ 1
}
unset output
