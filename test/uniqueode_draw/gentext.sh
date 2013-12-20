#!/bin/bash
width=$((42 * ${#1}))
height=100
convert -size ${width}x${height} canvas:white -font /usr/share/texlive/texmf-dist/fonts/truetype/public/dejavu/DejaVuSansMono.ttf -pointsize 50 -draw "text 0,50 '$1'" -channel RGB -fill black my_text.png
