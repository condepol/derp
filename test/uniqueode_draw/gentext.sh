#!/bin/bash
width=$((42 * ${#1}))
height=100
# /usr/share/texlive/texmf-dist/fonts/truetype/public/dejavu/DejaVuSansMono.ttf
font="/usr/local/texlive/2013/texmf-dist/fonts/truetype/public/dejavu/DejaVuSansMono.ttf"
convert -size ${width}x${height} canvas:white -font ${font} -pointsize 50 -draw "text 0,50 '$1'" -channel RGB -fill black my_text.png
