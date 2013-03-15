#!/usr/bin/python

import sys
import os
import urllib
import time
import random


def im2url(imageid, farm, server, secret, size="t"):
    if size:
        url = "http://farm%s.static.flickr.com/%s/%s_%s_%s.jpg" % (farm, server, imageid, secret, size)        
    else:
        url = "http://farm%s.static.flickr.com/%s/%s_%s.jpg" % (farm, server, imageid, secret)
    return url


def download(url, result_file):
    try:
        web_file = urllib.urlopen(url)
        data = web_file.read()
    except:
        print "Unexpected error:", sys.exc_info()[0]
        return False
    fout = open(result_file, 'wb')
    fout.write(data)
    fout.close()
    return True

if __name__ == '__main__':
    source_file = 'img_id.txt'
    #size = 't'
    size = None
    result_dir = 'img'
    
    print 'downloaded images will be saved at', result_dir
    if not os.path.exists(result_dir):
        os.makedirs(result_dir)
        
    for i,line in enumerate(open(source_file).readlines()):
        [imageid, farm, server, secret] = str.split(line.strip())
        result_file = os.path.join(result_dir, imageid + '.jpg')
        if os.path.exists(result_file):
            print result_file, 'exists!'
            continue
        print '%d: getting image %s ...' % (i, line)
        url = im2url(imageid, farm, server, secret, size=size)        
        download(url, result_file)
        waiting = random.uniform(3, 5)
        time.sleep(waiting)
        
                
    
