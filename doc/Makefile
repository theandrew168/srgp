all     : all_X  all_MAC srgp.quikref

all_X   : X_srgp.dvi X_srgp.ps X_srgp.txt

all_MAC : MAC_srgp.dvi MAC_srgp.ps MAC_srgp.txt

all_mu  : mu.dvi mu.txt 

.SUFFIXES: .dvi .tex .ps


X_srgp.dvi: srgp.tex
	echo "\def\platform{\X11platform}" > /tmp/srgp.tex
	cat tex_macros srgp.tex >> /tmp/srgp.tex
	tex /tmp/srgp
	/bin/mv srgp.dvi X_srgp.dvi
	/bin/rm /tmp/srgp.tex

X_srgp.txt: srgp.tex 
	echo "\X11platform" > /tmp/srgp.tex
	cat srgp.tex >> /tmp/srgp.tex
	detex < /tmp/srgp.tex | \
	      sed  -e 's/\`\`/\"/g'  -e s/\\\'\\\'/\\\"/g  > X_srgp.txt
	/bin/rm /tmp/srgp.tex

MAC_srgp.dvi: srgp.tex
	echo "\def\platform{\Macplatform}" > /tmp/srgp.tex
	cat tex_macros srgp.tex >> /tmp/srgp.tex
	tex /tmp/srgp
	/bin/mv srgp.dvi MAC_srgp.dvi
	/bin/rm /tmp/srgp.tex

MAC_srgp.txt: srgp.tex
	echo "\Macplatform" > /tmp/srgp.tex
	cat srgp.tex >> /tmp/srgp.tex
	detex < /tmp/srgp.tex | \
	      sed  -e 's/\`\`/\"/g'  -e s/\\\'\\\'/\\\"/g  > MAC_srgp.txt
	/bin/rm /tmp/srgp.tex

mu.dvi: mu.tex
	cat tex_macros mu.tex > /tmp/mu.tex
	tex /tmp/mu
	/bin/rm /tmp/mu.tex

mu.txt: mu.tex
	detex < mu.tex | \
	      sed  -e 's/\`\`/\"/g'  -e s/\\\'\\\'/\\\"/g  > mu.txt

.dvi.ps :
	dvips $* -o $*.ps

srgp.quikref: srgp.3
	nroff -man srgp.3 > srgp.quikref
