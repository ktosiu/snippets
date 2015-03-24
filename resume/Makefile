SRC = $(wildcard *.md)
PDFS = $(SRC:.md=.pdf)
DOCXS = $(SRC:.md=.docx)
HTML=$(SRC:.md=.html)

PANDOCARGS = --latex-engine=xelatex --variable fontsize=12pt

all: $(PDFS) $(DOCXS) $(HTML)

pdf: $(PDFS) pdfall
docx: $(DOCXS)
html: $(HTML)

pdfall:
	pandoc resume_zouxu_zhCN.md resume_zouxu_enUS.md $(PANDOCARGS) -H header.tex -V papersize:'a4paper' -f markdown -t latex -o resume_zouxu.pdf

%.pdf: %.md
	pandoc $< $(PANDOCARGS) -H header.tex -V papersize:'a4paper' -f markdown -t latex -o $@

%.docx: %.md
	pandoc $< -o $@

%.html: %.md
	pandoc $< -t html -c resume.css -o $@

clean:
	rm -rf *.pdf *.html *.docx *.log auto
