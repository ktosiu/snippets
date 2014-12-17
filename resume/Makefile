SRC = $(wildcard *.md)
PDFS = $(SRC:.md=.pdf)
DOCXS = $(SRC:.md=.docx)
HTML=$(SRC:.md=.html)

PANDOCARGS = --latex-engine=xelatex

all: clean $(PDFS) $(DOCXS) $(HTML)

pdf: $(PDFS)
docx: $(DOCXS)
html: $(HTML)

%.pdf: %.md
	python resume.py tex < $< | pandoc $(PANDOCARGS) -H header.tex -V papersize:'a4paper' -o $@

%.docx: %.md
	pandoc $< -o $@

%.html: %.md
	python resume.py html < $< | pandoc -t html -c resume.css -V pagetitle:'Paul Waring - CV' -o $@

clean:
	rm *.pdf *.html *.docx
