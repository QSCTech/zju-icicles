1.输入借书证卡号 显示该借书证所有已借书籍 (返回, 格式同查询模块) 2.输入书号：如果该书还有库存，则借书成功，同时库存数减一。否则输出该书无库存，且输出预计最快的归还时间。Database System

实验5	

完成了图书查询结果排序功能. 

## 1系统整体架构

 本项目使用Java语言开发， maven管理依赖。

### 工程结构

```python
myLab5
├── .idea 
├── databooks # 存储多批导入图书的数据
├── pom.xml # 确定包依赖
├── logs # log4j日志记录文件
├── src
│   ├── java/org.lab5
│   │   ├── entity # 存储对应数据库的实体类
│   │   │   ├── Book
│   │   │   ├── Card
│   │   │   ├── Admin # 管理员类
│   │   │   ├── queryCondition # 针对区间查询，继承Book类加入两个属性传入mybatis
│   │   │   ├── Record # 借书记录
│   │   ├── admin # 管理员登陆后的一些方法
│   │   ├── Main # 程序入口
│   │   ├── admin # 借书， 还书，查询三个方法
│   ├── resources
│   │   ├── bookMapper.xml # 操作book数据库的sql语句
│   │   ├── cardMapper.xml
│   │   ├── adminMapper.xml
│   │   ├── recordMapper.xml
│   │   ├── log4j.properties # log4j的配置文件
│   │   ├── mybatis-config.xml # mybatis的配置文件
```

选项4个, 1 ,管理员登陆 2 图书查询 3 借书 4 还书

管理员登陆后可以: 入库, 借书证管理

管理员 admin.  实体类  Emp 存储信息

图书实体类 Book 存储信息

 用户normaluser  .借书证实体类 User 存储信息

借书记录类 Record 存储信息

## 2程序设计中采用的技术

#### jdbc

DBC是Java DataBase Connectivity的缩写，它是Java程序访问数据库的标准接口。

使用Java程序访问数据库时，Java代码并不是直接通过TCP连接去访问数据库，而是通过JDBC接口来访问，而JDBC接口则通过JDBC驱动来实现真正对数据库的访问。

例如，我们在Java代码中如果要访问MySQL，那么必须编写代码操作JDBC接口。注意到JDBC接口是Java标准库自带的，所以可以直接编译。而具体的JDBC驱动是由数据库厂商提供的，例如，MySQL的JDBC驱动由Oracle提供。因此，访问某个具体的数据库，我们只需要引入该厂商提供的JDBC驱动，就可以通过JDBC接口来访问，这样保证了Java程序编写的是一套数据库访问代码，却可以访问各种不同的数据库，因为他们都提供了标准的JDBC驱动.

实际上，一个MySQL的JDBC的驱动就是一个jar包，它本身也是纯Java编写的。我们自己编写的代码只需要引用Java标准库提供的java.sql包下面的相关接口，由此再间接地通过MySQL驱动的jar包通过网络访问MySQL服务器，所有复杂的网络通讯都被封装到JDBC驱动中，因此，Java程序本身只需要引入一个MySQL驱动的jar包就可以正常访问MySQL服务器.

使用JDBC的好处是：

- 各数据库厂商使用相同的接口，Java代码不需要针对不同数据库分别开发；
- Java程序编译期仅依赖java.sql包，不依赖具体数据库的jar包；
- 可随时替换底层数据库，访问数据库的Java代码基本不变。

root的密码: nlchcg123

我们不直接写JDBC的resultset， 而是用mybatis包装，可以直接操作实体类。 

#### mybatis

1、jdbc写查询返回resultset是不释放连接的，操作不好就容易出现死锁。mybatis框架的查询是自动释放连接的

2、jdbc防止SQL注入是比较麻烦的，mybatis防止SQL注入写起来比较简单的

3、jdbc写SQL会把SQL写到java代码中，如果在生产环境里，无法快速修改SQL，而mybatis的SQL在xml文件中，生产环境中可以修改xml后，重启即生效。

4、mybatis有默认缓存机制，对查询进行了缓存，jdbc缓存你还得自己实现。

5、最显而易见的益处是mybatis连接数据库编码更快。

MyBatis 是一款优秀的持久层框架，它支持定制化 SQL、存储过程以及高级映射。MyBatis         避免了几乎所有的 JDBC 代码和手动设置参数以及获取结果集。MyBatis可以使用简单的 XML 或注解来配置和映射原生类型、接口和 Java 的 POJO（Plain Old Java Objects，普通老式 Java 对象）为数据库中的记录。

MyBatis的查询结果集都是自动映射封装的，单行查询将数据库一条数据封装成对应的Java对象。多行查询，先将每一行封装成对象，再将每个对象添加到集合中，最后返回一个List集合对象。

#### 范围查询

新增加了一个类叫做queryCondition.java，并让该类继承Books类,里面属性是Year2,Price2,并生成get、set方法。 利用mybatis中的<where> 和 <if> 标签， 实现动态SQL不确定条件的查询。

传入样例

```
null,EE,null,null,2021,2028,null,91.0,91.5
book18,EE,CS18,PUB18,	2011,2028, author18,91.0,99.2
 ,EE, , ,2021,2028, ,,105
```

#### log4j

利用常用的SLF4j作为日志接口.

输出日志，而不是用`System.out.println()`，有以下几个好处：

1. 可以设置输出样式，避免自己每次都写`"ERROR: " + var`；
2. 可以设置输出级别，禁止某些级别输出。例如，只输出错误日志；
3. 可以重定向到文件，这样可以在程序运行结束后查看日志；
4. 可以按包名控制日志级别，只输出某些包打的日志；

## 3 数据库表结构的描述

Book( ISBN , Category, Title, Publisher, Year, Author, Price, Total, Inventory) 主键ISBN

LibCard（cid, name, unit, category）主键卡号,

Records(ISBN, cid, BorrowTime, Due, AID)  外键书号. 外键管理员id,

Book

| 属性      | 数据类型     |      |          |
| --------- | ------------ | ---- | -------- |
| ISBN      | varchar(100) | 主键 | not null |
| Category  | varchar(100) |      |          |
| Title     | varchar(100) |      |          |
| Publisher | varchar(100) |      |          |
| pubyear   | int          |      |          |
| Author    | Varchar(100) |      |          |
| Price     | ∂double      |      |          |
| Total     | int          |      | not null |
| Inventory | int          |      | not null |

```sql
CREATE TABLE lab5.Book (
	ISBN varchar(50) NOT NULL,
	Category varchar(100) NULL,
	Title varchar(100) NULL,
	Publisher varchar(100) NULL,
	pubYear INT NULL,
	Author varchar(100) NULL,
	Price INT NULL,
	Total INT NOT NULL,
	Inventory INT NOT NULL
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8mb4
COLLATE=utf8mb4_0900_ai_ci;
ALTER TABLE lab5.Book ADD CONSTRAINT Book_PK PRIMARY KEY (ISBN);
```

LibCard

| 属性     | 数据类型     |               |      |
| -------- | ------------ | ------------- | ---- |
| cid      | int          | 主键,not null |      |
| name     | Varchar(100) | not null      |      |
| unit     | Varchar(100) |               |      |
| category | Varchar(10)  | not null      |      |

```sql
CREATE TABLE lab5.LibCard (
	cid INT auto_increment NOT NULL,
	name varchar(100) NOT NULL,
	unit varchar(100) NULL,
	category varchar(10) NOT NULL,
	CONSTRAINT LibCard_PK PRIMARY KEY (cid)
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8mb4
COLLATE=utf8mb4_0900_ai_ci;
```

Administrator

| 属性     | 数据类型     |      |          |
| -------- | ------------ | ---- | -------- |
| AID      | int          | 主键 | not null |
| password | Varchar(100) |      | not null |
| Name     | Varchar(100) |      |          |
| Contact  | Varchar(100) |      |          |

```sql
CREATE TABLE lab5.Administrator (
	AID INT NOT NULL,
	password varchar(100) NOT NULL,
	Name varchar(100) NULL,
	Contact varchar(100) NULL
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8mb4
COLLATE=utf8mb4_0900_ai_ci;
ALTER TABLE lab5.Administrator ADD CONSTRAINT Administrator_PK PRIMARY KEY (AID);
```

Records

| 属性       | 数据类型     |      |      |
| ---------- | ------------ | ---- | ---- |
| ISBN       | Varchar(100) | 外键 |      |
| cid        | int          | 外键 |      |
| BorrowTime | DATE         |      |      |
| Due        | DATE         |      |      |
| AID        | int          | 外键 |      |

```sql
CREATE TABLE lab5.Records (
	ISBN varchar(100) NOT NULL,
	cid INT NOT NULL,
	BorrowTime DATE NOT NULL,
	Due DATE NULL,
	AID INT NOT NULL
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8mb4
COLLATE=utf8mb4_0900_ai_ci;
ALTER TABLE lab5.Records ADD CONSTRAINT Records_FK FOREIGN KEY (ISBN) REFERENCES lab5.Book(ISBN) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE lab5.Records ADD CONSTRAINT Records_FK_1 FOREIGN KEY (cid) REFERENCES lab5.LibCard(cid) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE lab5.Records ADD CONSTRAINT Records_FK_2 FOREIGN KEY (AID) REFERENCES lab5.Administrator(AID) ON DELETE CASCADE ON UPDATE CASCADE;
```



##### 













## 4 每个功能模块的演示

### 功能模块

| 模块名称   | 功能描述                                                     |
| :--------- | :----------------------------------------------------------- |
| 管理员登陆 | 输入管理员ID，密码；登入系统 或 返回ID/密码 错误。           |
| 图书入库   | 1. 单本入库 2. 批量入库：图书信息存放在文件中，每条图书信息为一行。一行中的内容如下（书号，类别，书名，出版社，年份，作者，价格，数量） Note: 其中年份、数量是整数类型；价格是两位小数类型；其余为字符串类型 Sample: (book_no_1, CS, ComputerArchitecture, xxx, 2004, xxx, 90.00, 2) |
| 图书查询   | 要求可以对书的类别，书名，出版社，年份(年份区间)，作者，价格(区间) 进行查询，支持同时查询多个条件。返回最多前五十条符合条件的图书信息。每条图书信息包括以下内容: ( 书号, 类别, 书名, 出版社, 年份, 作者, 价格, 总藏书量, 库存 )； 可选要求: 可以按用户指定属性对图书信息进行排序. (默认是书名) |
| 借书       | 1.输入借书证卡号 显示该借书证所有已借书籍 (返回, 格式同查询模块) 2.输入书号：如果该书还有库存，则借书成功，同时库存数减一。否则输出该书无库存，且输出预计最快的归还时间。 |
| 还书       | 1.输入借书证卡号：显示该借书证所有已借书籍 (返回, 格式同查询模块) 2.输入书号：如果该书在已借书籍列表内，则还书成功，同时库存加一。否则输出出错信息。 |
| 借书证管理 | 增加或删除一个借书证。                                       |



#### 杂项

 Code | Generate ⌘ N to open the popup menu with available

使用 OGNL 语法表达式，在 OGNL 语法表达式中不能直接写符号，需要要使用其转义后的字符

解决Cannot determine value type from string 'xxx'的方法有2种

- 实体加无参构造函数
- mapper.xml中查询的数据库字段属性的类型要和有参构造器的字段类型一一匹配；查询字段的个数要和有参构造器个数一样

like. 