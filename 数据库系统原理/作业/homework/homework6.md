5.24, 

Consider the relation, r, shown in Figure 5.22. Give the result of the following query: 

```sql
select building, room number, time_slot_id, count(*) 
from r 
group by rollup (building, room number, time_slot_id)
```

group by rollup

The statement will calculate the aggregation of values in the column c4 based on the hierarchy d1 > d2 > d3.

D1,d2,d3 

D1,d2 null  

d1 null, null  各个building 的数量

Null null  null:  所有的数量。

| building | room number | time_slot_id | Count(*) |
| -------- | ----------- | ------------ | -------- |
| Garfield | 359         | A            | 1        |
| Garfield | 359         | B            | 1        |
| Saucon   | 651         | A            | 1        |
| Saucon   | 651         | C            | 1        |
| Painter  | 705         | D            | 1        |
| Painter  | 403         | D            | 1        |
| Garfield | 359         | Null         | 2        |
| Saucon   | 651         | null         | 2        |
| Painter  | 705         | null         | 1        |
| Painter  | 403         | null         | 1        |
| Garfield | null        | null         | 2        |
| Saucon   | null        | null         | 2        |
| Painter  | null        | null         | 2        |
| Null     | null        | Null         | 6        |

6.1,

Construct an E-R diagram for a car insurance company whose customers own one or more cars each. Each car has associated with it zero to any number of recorded accidents. Each insurance policy covers one or more cars and has one or more premium payments associated with it. Each payment is for a particular period of time, and has an associated due date, and the date when the payment was received.

customer 和 cars   own 联系集， 一对多

车和事故， 发生联系集

![image-20220419104159017](/Users/juyilin/Library/Application Support/typora-user-images/image-20220419104159017.png)

 6.2,

Consider a database that includes the entity sets student, course, and section from the university schema and that additionally records the marks that students receive in different exams of different sections. 

a. Construct an E-R diagram that models exams as entities and uses a ternary relationship as part of the design. 

使用三元关系schema 在附录里

![image-20220419003819721](/Users/juyilin/Library/Application Support/typora-user-images/image-20220419003819721.png)

b. Construct an alternative E-R diagram that uses only a binary relationship between student and section. Make sure that only one relationship exists between a particular student and section pair, yet you can represent the marks that a student gets in different exams.

![image-20220419003244315](/Users/juyilin/Library/Application Support/typora-user-images/image-20220419003244315.png)

 6.21,

Consider the E-R diagram in Figure 6.30, which models an online bookstore. 

a. Suppose the bookstore adds Blu-ray discs and downloadable video to its collection. The same item may be present in one or both formats, with differing prices. Draw the part of the E-R diagram that models this addition, showing just the parts related to video. 

首先看图， 书是author写的， publisher出版的， 购物篮contain。 仓库stock

加了一个video， video 也可以购物篮contain。 仓库stock

第一题应该是只用画出video， 然后光盘不用画， 

video就是超类，可以进行一般化。

![image-20220418235842618](/Users/juyilin/Library/Application Support/typora-user-images/image-20220418235842618.png)

b. Now extend the full E-R diagram to model the case where a shopping basket may contain any combination of books, Blu-ray discs, or downloadable video.

discs， 也可以购物篮contain。 仓库stock。

![image-20220419001521645](/Users/juyilin/Library/Application Support/typora-user-images/image-20220419001521645.png)

 6.22

Design a database for an automobile company to provide to its dealers to assist them in maintaining customer records and dealer inventory and to assist sales staff in ordering cars.

Each vehicle is identified by a vehicle identification number (VIN). Each individual vehicle is a particular model of a particular brand offered by the company (e.g., the XF is a model of the car brand Jaguar of Tata Motors). Each model can be offered with a variety of options, but an individual car may have only some (or none) of the available options. The database needs to store information about models, brands, and options, as well as information about individual dealers, customers, and cars. 

Your design should include an E-R diagram, a set of relational schemas, and a list of constraints, including primary-key and foreign-key constraints.

为汽车公司设计一个数据库，提供给经销商dealer，帮助他们维护客户记录和经销商库存，并协助销售人员订购汽车。

vehicle。有vin 属性， 超类是model。

model的超类 brand，  和company 有offer 联系集。 vehicle是全部参与到offer联系集。 

模型 实体集   和 品牌 实体集有联系集，  

model和 option 实体集有offer联系集

dealer 实体集，和car 有inventory的联系集。

customers 实体集和 car 有buy的联系集。

cars 实体集和 option 实体集有offer联系集。

option可能是联系集的一个属性。

![image-20220419234713800](/Users/juyilin/Library/Application Support/typora-user-images/image-20220419234713800.png)

primary key demonstrates as underline.

brand（<u>bid</u>, name, company）
model(<u>model_id</u>,name,bid,option_id) foriegn key(bid) references brand(bid),foreign key(option_id) reference model(option_id)
option(<u>option_id</u>,content) 
car(<u>vin</u>,model_id,option_id) foreign key(model) reference model(model_id), foreign key(option_id) reference model(option_id)
customer(<u>cust_id</u>,name,phone)
dealer(<u>d_id</u>,address,name)
inventory(<u>d_id,vin</u>)  foreign key(d_id) references dealer(d_id), foreign key (vin) references car(vin)



