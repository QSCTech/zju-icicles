#!/usr/bin/env sh

# ----------------------------------------------------------------
# Author: Zewen-Ye
# Institution: College of Information Science and Electrical Engineering, ZheJiang University
# Usage:
# ./prb4.sh
# ----------------------------------------------------------------


bingUrl='https://cn.bing.com/'
# first, download the bing website html file named 'index.html'
wget $bingUrl
# the picture name is inserted in  the string named 'img src'
file=`cat index.html | grep  'img src' |cut -d '"' -f 2`
# the whole file link
obj_url=${bingUrl}${file}
echo $obj_url 
# rename the picture
filename=`date '+%m.%d'`
# download the picture
wget $obj_url -O /home/lustre/Picture/$filename.jpg
rm index.html

# to make this shell script autorun every day, we should use `crontab -e`
# then add ` 22 22 * * * /home/lustre/hw2/prb4.sh `