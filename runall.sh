#!/bin/bash

(cd PropertiesSU2 && make clean && make && ./createTables.out)
(cd PropertiesCP && python createTable.py)
(cd Presentation && pdflatex presentation.tex)

