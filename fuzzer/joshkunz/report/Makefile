.PHONY: build buildn open clean zip

# The file we want to view
view = report

build: $(view).pdf open
buildn: *.pdf

%.pdf: %.tex
	pdflatex $*.tex

open: $(view).pdf
	if [ `uname` = "Darwin" ];\
		then open $(view).pdf;\
		else evince $(view).pdf;\
	fi

clean:
	-rm *.log *.aux *.out
