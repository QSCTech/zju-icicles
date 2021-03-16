#! /bin/bash

# ----------------------------------------------------------------
# " author : Lin Juyi , college of ISEE, ZHEJIANG UNIVERSITY 1263810658@qq.com"
# " latest update time : 2020/ 12/7 "
# " created time : 2020/11/14  for ICCAD class, homework 4_4_3, problem 4  "
# Usage:
# ./prb4.sh
# ----------------------------------------------------------------

bingUrl='https://cn.bing.com/'
# first, download the bing website html file named 'index.html'
wget $bingUrl
# the picture name is inserted in  the string named 'background-image'
file=`sed -n '3p'  index.html| awk  '{print $4}'| awk -F '"' '{print $2}' `
# the whole file link
obj_url=${bingUrl}${file}
echo $obj_url 
# rename the picture
filename=`date '+%m.%d'`
# download the picture
wget $obj_url -O /home/luke/$filename.jpg
rm index.html

# to make this shell script autorun every day, we should use `crontab -e`
# then add 0 12 * * * ~/scripts/pro4.sh  每天中午/sbin/service crond start