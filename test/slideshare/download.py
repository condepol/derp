#!/usr/bin/env python3
#
# wow
#  very hacker
# such download
#    much terms and conditions
#
# http://www.slideshare.net/MalteLandwehr/slideshare-download <- easy .swf slides.
# http://www.slideshare.net/BobRadvanovsky/project-shine-findings-report-dated-1oct2014 <- mysterious '.ssd' file, todo
#
# this > http://paste.atilla.org/cu9zbqI&ln
##!/bin/bash
##XML=`curl $1 | grep 'meta name="thumbnail"' | sed -r -e 's/.*content="(.+?)".*/\1/' -e 's/ss_thumbnails\///' -e 's/(.+phpapp[0-9]+).+/\1.xml/'`
##SLIDES=`curl "$XML" | sed 's/>/>\n/g' | grep 'Src="' | sed -r -e 's/.*Src="(.+?)".*/\1/g'`
##for SLIDE in $SLIDES; do
##        wget $SLIDE
##done


import os
import sys
import requests

if __name__ == '__main__':
  url = sys.argv[1]
  folder = 'slides' if len(sys.argv) < 3 else sys.argv[2]

  # download page
  response = requests.get(url)
  print('{} {}'.format(response.status_code,url))
  line = [l for l in response.text.splitlines() if '<meta name="thumbnail"' in l][0]
  uri = line.split('content="')[1].split('" />')[0]
  print('Base uri : «{}»'.format(uri))
  
  # cut everything after -phpapp0[12]
  prefix, suffix = uri.strip().split('-phpapp')
  phpapp_version = suffix.split('-')[0]
  
  # remove the ss_thumbnails/ part
  prefix = ''.join(prefix.split('ss_thumbnails/'))
  
  # add xml
  xml_uri = '{}-phpapp{}.xml'.format(prefix,phpapp_version)
  print(xml_uri)
  
  # download xml
  xml_response = requests.get(xml_uri)
  print('{} {}'.format(xml_response.status_code, xml_uri))
  xml = xml_response.text
  
  # create folder
  if not os.path.exists(folder):
    os.mkdir(folder)

  # iterate over slides
  counter = 1
  for slide in xml.split('<Slide'):
    if 'Src="' in slide:
      slide_uri = slide.split('Src="')[1].split('" />')[0]
      slide_response = requests.get(slide_uri)
      print('{} {}'.format(slide_response.status_code, slide_uri))
      with open('{}/slide-{:03d}_{}'.format(folder,counter,slide_uri.split('/')[-1]),'wb') as o:
        o.write(slide_response.content)
      counter += 1
    else:
      print('Skipping «{}»'.format(slide))
