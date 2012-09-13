SHELL = /bin/bash
PERL = perl
DOC=code-clone
DOC_TEX = $(patsubst %,%.tex,$(DOC))

# Check if gnuplot supports histograms
HAVEGPLOT = $(shell (echo "help histograms" | gnuplot 2>&1 | grep -q "cluster" && echo yes || (echo no)))

SECTIONS=code-clone \
	 abstract \
	 intro \
	 nphardness \
	 algo \
	 example \
	 analysis \
	 ext \
	 concl \
	 appendix \

# This line left blank.

SECTIONS_TEX = $(patsubst %,%.tex,$(SECTIONS))

FIGS = 
FIG_PSTEXS = $(patsubst %,figures/%.pstex,$(FIGS))
FIG_PSTEX_TS = $(patsubst %,figures/%.pstex_t,$(FIGS))

BIBS = allpapers
BIBS_BIB = $(patsubst %,%.bib,$(BIBS))
DOC_BBL = $(patsubst %,%.bbl,$(DOC))

OTHERS = Makefile supertech-sig.sty plain-url.bst sig-alternate.cls \
         plain-url.bst flushend.sty clrscode4e.sty morefloats.sty

# Plot with gnuplot in data/
DATA_FILES = 

# PLot with gnupot in ./ (must do here because gnuplot has trouble with directory switching)
DATA_FILES_HERE = 

DATA_EPS_FILES = $(patsubst %, data/%.eps, $(DATA_FILES)) $(patsubst %,%.eps, $(DATA_FILES_HERE))

# Figures gotten out of Microsoft PowerPoint.
PRNFIGS = 
EPSFIGS = $(PRNFIGS)
FIG_EPS = $(patsubst %,figures/%.eps,$(EPSFIGS))

# DIFFFILES := $(wildcard tps-data/*.diff) $(wildcard mit-data/*.diff)
XHIST     := 

EPSHIST   := $(XHIST:.hist=.eps)
FIG_EPS	  += $(EPSHIST)

default: $(DOC).pdf
.PRECIOUS: %.dvi
.PHONY: default all fast dvi print view clean bbl love pub pdf ps
fast all: $(DOC).ps $(DOC).dvi
$(DOC).dvi: 
dvi: $(DOC).dvi
ps: $(DOC).ps
pdf: $(DOC).pdf
print: $(DOC).ps
	lpr $(DOC).ps
view: $(DOC).dvi
ifeq ($(USER),cel) 
	open $(DOC).pdf &
else	
	xdvi -s 7 $(DOC) &
endif

bbl: $(FIG_PSTEXS) $(FIG_PSTEX_TS)
	latex $(DOC)
	bibtex --min-crossrefs=9999 $(DOC)

$(DOC).bbl: $(BIBS_BIB) $(DOC_TEX) $(SECTIONS_TEX) $(OTHERS)  $(FIG_PSTEXS) $(FIG_PSTEX_TS)
	latex $(DOC)
	bibtex --min-crossrefs=9999 $(DOC)

$(DOC).dvi: $(DOC_TEX) $(SECTIONS_TEX) $(FIG_EPS) $(DOC_BBL) $(OTHERS) $(FIG_PSTEXS) $(FIG_PSTEX_TS) $(DATA_EPS_FILES)
$(DOC).ps:  $(DOC).dvi

# implementation.dvi: implementation.tex setup.tex supertech.sty

# This is less annoying than the run_latex script, since it doesn't print so much and it runs faster.
# Algorithm:  run latex, but don't print the output to the terminal.
# If you see the word "Citation" in the log, the run bibtex and run latex again (don't print latex log out yet)
# If you see "Label(s) may have changed" then run latex a third time (still don't print the the latex log)
# Finally, print the latex log
# When running bibtex, be sure to use --min-crossrefs=9999
%.dvi: %.tex
	@echo latex $(patsubst %.tex,%,$<)
	@latex $(patsubst %.tex,%,$<)
	@if fgrep -e "Citation" $(patsubst %.tex,%.log,$<) | fgrep -v "???" >/dev/null; then echo bibtexing and latexing again because of an undefined citation; echo bibtex --min-crossrefs=9999 $(patsubst %.tex,%,$<); bibtex --min-crossrefs=9999 $(patsubst %.tex,%,$<); echo latex $(patsubst %.tex,%,$<) ; latex $(patsubst %.tex,%,$<) ; fi
	@if fgrep -e "Label(s) may have changed" $(patsubst %.tex,%.log,$<) > /dev/null; then echo Latexing again because labels changed.; echo latex $(patsubst %.tex,%,$<); latex $(patsubst %.tex,%,$<); fi

%.pstex: %.fig Makefile
	fig2dev -L pstex $($(patsubst %.fig,FIG_MAG_%,$<)) $< $@

%.pstex_t: %.fig Makefile
	fig2dev -L pstex_t -p $(patsubst %.fig,%.pstex,$<) $($(patsubst %.fig,FIG_MAG_%,$<)) $< $@
# nsf says use -P pdf -t letter to avoid using type 3 fonts. 
# However there is a problem with the fl ligature, and I cannot fix it byu going the other route
# Rehdat bugzilla Bug 66721 reports that passing -G0 to dvips will fix this problem.
# DVIPS = dvips -P download35 -t letter -G0 -Pcmz
DVIPS = dvips -Ppdf -t letter -G0 #-j0
# Lately, people suggest doing

#DVIPS = dvips -P download35 -t letter
#DVIPS = dvips

%.ps: %.dvi
	$(DVIPS) $(patsubst %.ps,%,$@) -o

# Method for creating .eps figures from PowerPoint source
#  - Print from PowerPoint to PostScript printer
#  - Set "Print to file" and "Current slide"
#  - Transfer resulting .prn file to Linux
#  - Run script below to create .eps

%.eps: %.prn Makefile
	fixps $< -o $(patsubst %.prn, %.ps, $<)
	ps2epsi $(patsubst %.prn, %.ps, $<) $@

%.eps: %.fig Makefile
	fig2dev -L eps $< $@

%.pdf: %.ps
	ps2pdf14 -dPDFSETTINGS=/prepress -dEmbedAllFonts=true $< $@
	test ! -f .xpdf-running || xpdf -remote $(DOC)-server -reload

# Build eps file from gnuplot
data/%.eps: data/%.gnuplot data/%.data
	(cd data; gnuplot $(patsubst data/%.gnuplot, %.gnuplot, $<))

# Build here
ifdef REPLOT
heat_2D_P_speed_cmp.eps: heat_2D_P_speed_cmp.gnuplot
heat_2D_NP_span.eps: heat_2D_NP_span.mdat
heat_2D_P_span.eps: heat_2D_P_span.mdat
dfd_span: dfd_span.mdat
%.eps: %.gnuplot
	gnuplot $<
else
%.eps:  %.gnuplot
	touch $@
endif

# tm.bbl: tm.bib proposal.tex deliverables.tex technical.tex latex8.bst
#	bibtex --min-crossrefs=9999 proposal

prebuilt: $(EPSHIST)
	@for file in $(EPSHIST); do \
		cp $$file $$file.prebuilt; \
		echo "cp $$file $$file.prebuilt"; \
	done

clean:
	rm -f *.aux *.ps *.dvi *.bbl *.blg *.tmp *.log *.pstex *.pstex_t *~ \
	$(patsubst %,%.ps,$(PRNFIGS)) $(patsubst %,%.eps,$(PRNFIGS)) $(DOC).pdf \
	$(EPSHIST) $(XHIST) coststable.tex resultstable.tex $(FIG_EPS)

love:
	@echo "Not war?"

xpdf: $(DOC).pdf
	if test -f .xpdf-running; then                 \
		xpdf -remote $(DOC)-server -quit;      \
		sleep 1;                               \
	fi
	touch .xpdf-running
	(xpdf -remote $(DOC)-server $(DOC).pdf; rm -f .xpdf-running) &

pub: $(DOC).pdf $(DOC).ps
	cp $(DOC).pdf focs-submission/focs21r-tang.pdf
	cp $(DOC).ps focs-submission/focs21r-tang.ps
	cat $(SECTIONS_TEX) >focs-submission/focs21r-tang.tex
	perl extractbib.pl focs-submission/focs21r-tang.tex allpapers.bib focs-submission/focs21r-tang.bib

ignore:
	rm -f .svnignore
	for file in '*.aux' '*.bbl' '*.blg' '*.log' '*.dvi' '*.bak' \
			.xpdf-running $(DOC).ps $(DOC).pdf $(FIG_EPS); do \
		echo "$$file" >> .svnignore; \
	done
	svn ps svn:ignore -F .svnignore .
	rm -f .svnignore
