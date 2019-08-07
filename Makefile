default :
	@echo MAKING... SRGP optimized '(-O)' library
	(cd src/srgp; make clean CFLAGS=-O)
	@echo MAKING... example programs
	(cd examples; make PROG=show_patterns)
	(cd examples; make PROG=X_demo_anim)
	(cd examples; make PROG=test_locator)
	(cd examples; make PROG=testcolor_and_resize)
	(cd examples; make PROG=testrubber)
	(cd examples; make PROG=testeditkeyboard)
	(cd examples; make PROG=testpaint)
	(cd examples; make PROG=testpixmap)
	(cd examples; make PROG=testtimestamp)
	(cd doc; make)
