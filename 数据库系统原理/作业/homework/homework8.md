12.13



Suppose you have data that should not be lost on disk failure, and the application is write-intensive. How would you store the data?

磁盘故障不能丢失。

Flash memory 写很慢， 10us。 

RAID5 ， 应用场合为update rate不高， 数据量大。

所以就可以RAID5。 或者用flash 存储。

 13.11

List two advantages and two disadvantages of each of the following strategies for storing a relational database: 

a. Store each relation in one file. 

优点：

1. 查询单个表的时候比较快

2. 结构简单， 单个文件占用空间小

缺点：

1. 多表联合查询的时候比较慢

2. 限制了DBMS的能力

b. Store multiple relations (perhaps even the entire database) in one file.

优点：

1. 多表联合查询的时候比较快
2. DBMS可以有各种优化。

缺点：

1. 查询单个表的时候比较慢。

2. 单个文件占用空间大，而且结构复杂度大。
