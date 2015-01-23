(TeX-add-style-hook
 "header"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("geometry" "top=.5in" "bottom=.5in" "left=1in" "right=1in")))
   (TeX-run-style-hooks
    "geometry"
    "tgpagella"
    "xeCJK"
    "titlesec")
   (LaTeX-add-environments
    "nospace")
   (LaTeX-add-saveboxes
    "zerobox")))

