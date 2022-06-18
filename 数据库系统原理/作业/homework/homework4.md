4.7

Consider the employee database of Figure 4.12. Give an SQL DDL definition of this database. Identify referential-integrity constraints that should hold, and include them in the DDL definition

employee 作为主键, works 和manages 都参考他的id . company 作为主键, works 参考他的company name

```sql
create table employee (
    ID int, 
    person_name varchar(50),
    street varchar(50),
    city varchar(50),
	primary key ID);
create table works (
    ID int, 
    company_name varchar(50),
    salary int,
    FOREIGN KEY (ID)
    REFERENCES employee (ID),
    FOREIGN KEY (company_name)
    REFERENCES company (company_name));
create table company (
    company_name varchar(50),
    city varchar(50),
    primary key (company_name));
create table manages (
    ID int, 
    manager_id int,
    FOREIGN KEY (ID)
    REFERENCES employee (ID));
```

4.9

SQL allows a foreign-key dependency to refer to the same relation, as in the following example:

```sql
create table manager (
    employee_ID char(20), 
    manager_ID char(20),
primary key employee ID, 
foreign key (manager_ID) references manager(employee_ID) on delete cascade )
```

Here, employee ID is a key to the table manager, meaning that each employee has at most one manager. The foreign-key clause requires that every manager also be an employee. Explain exactly what happens when a tuple in the relation manager is deleted.

元组（tuple）是关系数据库中的基本概念，关系是一张表，表中的每行（即数据库中的每条记录）就是一个元组，每列就是一个属性。 在二维表里，元组也称为行。

 CASCADE指当删除主表中被引用列的数据时，级联删除子表中相应的数据行。

删除employee_ID, 那么所有对应的manager_ID那些行也会被删除.  

然后, 形成连锁效应,  因为manager_ID 同一行有employee_ID,  继续删除对应的manager_ID, 这样连锁删除



4.12

Suppose a user wants to grant **select** access on a relation to another user. Why should the user include (or not include) the clause **granted by current role** in the grant statement?

假设用户想要授予对另一个用户的关系的选择访问权限。 为什么用户应该在授权语句中包含（或不包含）granted by current role？

创建Role，拥有t1表的查询权限:

创建一个账户，并将role赋给它

包含了granted by current role, 即使用户的role被收回, 另一个用户还是可以有这个role.

