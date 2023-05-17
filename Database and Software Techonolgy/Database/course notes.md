In this course we use data from [dvdrental.sql](Data/dvdrental.sql)

# Content

- [Content](#content)
- [Pre-requirements for Windows](#pre-requirements-for-windows)
	- [Download and Install Mysql](#download-and-install-mysql)
	- [Optional\* Download and Install DBeaver](#optional-download-and-install-dbeaver)
	- [Open or stop Mysql service](#open-or-stop-mysql-service)
	- [Try Mysql in command line](#try-mysql-in-command-line)
- [Query](#query)
	- [SELECT \& FROM \& WHERE \& LIMIT \& AS](#select--from--where--limit--as)
	- [Special Operators](#special-operators)
	- [GROUP BY \& HAVING](#group-by--having)
	- [ORDER BY](#order-by)
- [Relational Set Operations](#relational-set-operations)
	- [Join Tables](#join-tables)
- [Datatypes](#datatypes)
	- [Data type conversion](#data-type-conversion)
- [Built-in Functions](#built-in-functions)
	- [Strings](#strings)
	- [Numeric](#numeric)
	- [Date and Time](#date-and-time)
	- [if()](#if)
- [Create and Delete Databases](#create-and-delete-databases)
	- [Column constraints](#column-constraints)
- [Functions and Procedures](#functions-and-procedures)
	- [Function](#function)
	- [Procedure](#procedure)
	- [IF THEN ELSE](#if-then-else)
	- [Simple LOOP](#simple-loop)
- [Database Design](#database-design)
	- [Entity-Relationship Diagram (ERD)](#entity-relationship-diagram-erd)
	- [Database Normalization](#database-normalization)
		- [0NF -\> 1NF](#0nf---1nf)
		- [1NF -\> 2NF](#1nf---2nf)
		- [2NF -\> 3NF](#2nf---3nf)
		- [Denormalization](#denormalization)
	- [Database Indexing](#database-indexing)
- [Database Transactions](#database-transactions)
	- [Transaction Requirements – ACID](#transaction-requirements--acid)
	- [Transaction Atomicity and Durability](#transaction-atomicity-and-durability)
	- [Transaction States](#transaction-states)
	- [Concurrent Transaction Common Problems](#concurrent-transaction-common-problems)
	- [Transaction Isolation Levels](#transaction-isolation-levels)
	- [Serializable Schedule](#serializable-schedule)
	- [Transaction management](#transaction-management)
- [Practice](#practice)

# Pre-requirements for Windows

## Download and Install Mysql

Download Mysql from https://dev.mysql.com/downloads/installer/

![Download Mysql](Pictures/Download%20Mysql.png)  
_do not select the web version_

follow the instructions (default, default, default...)

## Optional\* Download and Install DBeaver

Download DBeaver from https://dbeaver.io/. It's like an IDE for databases which greatly eaiser the editing of sql and database.

## Open or stop Mysql service

The are two ways:

1. Through GUI (recommended for noobs)

   ![open Services](Pictures/Open%20Services.png)  
   _find_ **_Services_**

   ![Services](Pictures/Services.png)  
   _set as Manual and start service (stop service to reduce performance cost)_

2. Through command line (recommended for pros)

   ![cmd](Pictures/cmd.png)  
   _Run cmd as administrator_

   ```cmd
   # To enable mysql service, type
   net start mysql80
   # if it doesn't work, type
   net start mysql
   # To stop mysql service, type
   net start mysql80
   # if it doesn't work, type
   net stop mysql
   ```

## Try Mysql in command line

![Env](Pictures/Environment%20Variables.png)  
_add Mysql to Path_

```cmd
# To enter mysql mode, type
mysql
# If it doesn't work, type
mysqlsh
# To exit mysql mode, type \quit
```

# Query

```sql
show databases;
use dvdrental;
show tables;
```

## SELECT & FROM & WHERE & LIMIT & AS

```sql
select
	*
from
	staff
where
	first_name = "Mike";
```

```sql
select
	film_id,
	title,
	length,
	length * 60 as length_in_secs
from
	film
limit 5;
```

## Special Operators

SQL allows the use of special operators in conjunction with the `WHERE` clause. These special operators include

- `BETWEEN` Used to check whether an attribute value is within a range
- `IN` Used to check whether an attribute value matches any value within a value list
- `LIKE` Used to check whether an attribute value matches a given string pattern
- `IS NULL` Used to check whether an attribute value is null

```sql
-- Find out customers whose last name start with J.
select
	*
from
	customer
where
	last_name like "J%";
```

## GROUP BY & HAVING

- `GROUP BY` groups the selected rows based on one or more attributes
- `HAVING` chooses the grouped rows (by GROUP BY clause) based on a condition

```sql
select
	customer_id,
	staff_id,
	COUNT(*),
	SUM(amount)
from
	payment
group by
	customer_id,
	staff_id;
```

```sql
-- What is the minimal length (>46) for films with different rating ?
select
	rating,
	MIN(length)
from
	film
group by
	rating
having
	MIN(length) >46;
```

## ORDER BY

`ORDER BY` orders the selected rows based on one or more attributes. Can be followed by `ASC` or `DESC`

```sql
select
	*
from
	actor
order by
	first_name,
	last_name,
	actor_id;
```

# Relational Set Operations

## Join Tables

![SQL joins1](Pictures/SQL%20joins1.jpg)

![SQL joins2](Pictures/SQL%20joins2.jpg)

In MySQL, we use `UNION` instead of `UNION`, `INTERSECT`, and `EXCEPT`. `UNION` is set strict and no duplicates; if you want to keep duplicates, you can use `UNION ALL`.

```sql
-- find out actor whose first name is ‘Joe’ and customer whoes first name is ‘Lisa’.
select
	first_name,
	last_name
from
	actor
where
	first_name = "Joe"
union
select
	first_name,
	last_name
from
	customer
where
	first_name = "Lisa";
```

```sql
-- inner join table city and country with country_id.
select
	*
from
	city
inner join country on
	city.country_id = country.country_id;
```

Difference between `IN` and `ON`: `IN` is followed by a table while `ON` is followed by a conditional statement.

# Datatypes

- Character and text
  - `CHAR(fixed_len)` len<=255, fixed-length character strings. Strings shorter than expected will be padded with spaces to reach the fixed length.
  - `VARCHAR(max_len)` Variable-length character strings.
  - `TEXT` Character large object (other DMBSs "CLOB").
  - `BLOB` Binary large object. Can store images, sounds, videos, PDF files, Word files, etc.
- Numeric
  - `INT`/`INTEGER` from -2,147,483,648 to 2,147,483,647.
  - `BOOL`/`BOOLEAN` 0 (false) or 1 (true)
  - `DECIMAL(m,d)` fixed-point, fixed number of digits; m is total digits (1~65), d is digits right of the decimal (0~30)
  - `FLOAT`/`DOUBLE` floating-point, up to 7/15 significant digits, less precise than DECIMAL but can store larger/smaller values
  - `UNSIGNED` only +, doubles the maximum of the datatype, e.g. `UNSIGNED INT` `UNSIGNED DECIMAL`
- Date and time
  - `DATE` yyyy-mm-dd, from 1000-1-1 through 9999-12-31
  - `TIME` hh:mm:ss, from -838:59:59 through 838:59:59
  - `DATETIME` Combination of `DATE` + `TIME`, yyyy-mm-dd hh:mm:ss, from 1970-1-1 to 9999-12-31
  - `TIMESTAMP` Similar to `DATETIME`, but from 1970-1-1 to 2037-12-31. Can automatically change date by user time zone
  - `YEAR[(4)]` e.g. "2021", "2000"

`TIMESTAMP` and `DATETIME` can keep track of when a row was inserted or last updated

## Data type conversion

```sql
cast(expression as cast_ type)
```

# Built-in Functions

## Strings

```sql
select
	concat('a', space(10), 'b'),
	-- 'a          b'
	length('very good'),
	-- 9
	upper('very good'),
	-- 'VERY GOOD'
	lower('VERY GOOD'),
	-- 'very good'
	reverse('very good'),
	-- 'doog yrev'
```

## Numeric

```sql
select
	round(-3.14),
	-- -3
	ceiling(-3.14),
	-- -3
	floor(-3.14),
	-- -4
	abs(-3.14),
	-- 3.14
	sign(-3.14),
	-- -1
	rand(),
	-- a random float number, [0.0, 1.0)
	rand(),
	-- another random float number
	rand(123),
	-- rand() with seed
	power(3.14, 3),
	-- 30.959144
```

## Date and Time

```sql
set @t = "2021-11-28 20:23:51"; -- setting a variable

select
	current_date(),
	current_time(),
	current_timestamp(),
	utc_date(),
	utc_time(),
	year(@t),
	month(@t),
	dayofmonth(@t),
	dayofweek(@t);

select
	extract(year from @t),
	extract(day_second from @t);

select
	date_add(@t, interval 1 month),
	date_sub(@t, interval 1 day);

select
	datediff("2021-11-21", "2021-11-1"),
	-- returns the number of days
	to_days("2021-11-21"),
	-- returns the number of days since the year 0. Not reliable for dates <1582
	time_to_sec("0:10");
	-- returns the number of seconds since midnight 00:00
```

## if()

```sql
select
	title,
	rating,
	if(rating != "R",
	"good film",
	"x") as good_movie
from
	film
```

# Create and Delete Databases

```sql
create database coursedb;
create table Stu(
	stu_id int not null,
	name varchar(30) default "Not available",
	primary key (stu_id));
drop table Stu;
drop database coursedb;
```

## Column constraints

- `NOT NULL` NULL values not allowed
- `UNIQUE` no duplicates
- `AUTO INCREMENT` e.g. for an integer column, each new insertion would add 1 to it
- `DEFAULT default_value` convenient to have a default value
- `CHECK(P)` check the data value being entered into a record
- `PRIMARY KEY` A valid relation (table) should have a primary key. By default, `PRIMARY KEY` == `NOT NULL` + `UNIQUE`
- `FOREIGN KEY` A field (or collection of fields) that refers to the `PRIMARY KEY` in another table

```sql
create table table_name(
	column_name_1  type  column_constraints,
	column_name_2  type  column_constraints,
	…,
	[constraint name] primary key (column_name_1),
	[constraint name] foreign key (column_name_2) references table_name_2 (column_name_1),
	check(column_name_2>2))
```

Referential Integrity ensures that a value that appears in one relation for a given set of attributes also appears for a certain set of attributes in another relation.

# Functions and Procedures

## Function

return values and can be run like built-in functions

```sql
delimiter // -- change default delimiter from ";" to "//"
create function my_add(x integer, y integer)
returns integer
deterministic -- state same result on same input, not essential
	begin
		return x + y;
	end //
delimiter ; -- new delimiter "//"

select my_add(1,2); -- test
```

## Procedure

do not return values (`IN`/`OUT`/`INOUT` parameters) and can be run using `CALL` keyword

```sql
delimiter //
create procedure get_film()
deterministic
begin
	select
		film_id,
		title
	from
		film;
end//
delimiter ;

call get_film();
```

> Warning: Use "Execute script" instead of "Execute SQL statement" in DBeaver to avoid error.

## IF THEN ELSE

```sql
delimiter //
create procedure my_compare(a int, b int)
deterministic
begin
	if a > b then
		select
			"a is larger than b";
	elseif a = b then
		select
			"a equals b";
	else
		select
			"a is smaller than b";
	end if;
end//
delimiter ;

call my_compare(10, 20);
```

## Simple LOOP

```sql
delimiter //
create procedure cumsum(N int)
deterministic
begin
	declare s int default 0;
	declare i int default 1;
	my_loop: loop
		set s = s + i;
		select
			i as added,
			s as result;
		set i = i + 1;
		if i>N then
			leave my_loop;
		end if;
	end loop;
end //
delimiter ;

call cumsum(100);
```

# Database Design

**_Database requirements_** are statements that define the details and constraints of the data and metadata, which can be represented in a **_conceptual database model_**, such as **_Entity-Relationship (ER) model_**. The result of ER modeling is an **_ER diagram (ERD)_**.

## Entity-Relationship Diagram (ERD)

We use a modified version of **_Peter Chen’s Notation_**. [View full info](Courseware/L4%20Database%20design%20and%20E-R%20model.pdf)

## Database Normalization

Normalization is a process to improve the design of relational databases, mainly to reduce data redundancy while preserving information. Normal form (NF) is a set of particular conditions upon table structures.

### 0NF -> 1NF

> 1. Remove duplicated rows.
> 2. Eliminate multivalued columns.

A table is in 1NF if each row is unique and not duplicated. Within each row, each value in each column must be single valued.

### 1NF -> 2NF

> Create an additional relation for each set of partial dependencies.
>
> 1. The portion of the primary key in partial dependency => primary key of the new table (becomes a foreign key in original table).
> 2. The columns determined in partial dependency => columns of the new table (removed from original table).
>
> The original table remains after the process of normalizing to 2NF, but no longer contains the partially dependent columns.

A table is in 2NF if it is in 1NF and does not contain **_*partial dependencies*_** (a column of a relation is functionally dependent on a portion of a composite primary key). Table has a single-column primary key <=> Table is in 2NF.

### 2NF -> 3NF

> Create additional relations for each set of transitive dependencies in a relation.
>
> 1. The transitively determinant nonkey column in the original table => the primary key of a new table.
> 2. Move the determined nonkey columns to the new table.
>
> The original table remains after normalizing to 3NF, but it no longer contains the transitively dependent columns

A table is in 2NF if it is in 2NF and does not contain **_*transitive functional dependencies*_** (nonkey columns functionally determine other nonkey columns).

### Denormalization

Denormalization is reversing the effect of normalization by joining normalized relations into a relation that is not normalized in order to improve query performance.

## Database Indexing

Indexing is a mechanism for increasing the speed of data search and data retrieval on relations with a large number of records.

- **_Linear Search_** O(n) in the worst case
  not indexed
  ![Linear Search](Pictures/Linear%20Search.jpg)

- **_Binary Search_** O(log(n))
  creates an additional index table (sorted + pointer), and allows binary search on it and then points back to the original column (unsorted) to increase the speed of search and retrieval on the columns that are being indexed.
  ![Binary Search](Pictures/Binary%20Search.jpg)

- **_Hash Index_** O(1)
  is useful when files are not sequential. Data in the system distributes to storage spaces called buckets depending on the key value calculated by hash function.
  ![Hash Index](Pictures/Hash%20Index.jpg)

  - Very efficient at equality queries (column==value).
  - Take constant time, independent of the number of rows in a table.
  - Not efficient at inequality queries (eg. <, <=, >, <=, between, in, not in, like).
  - Require more space than range indexes.

- **_B-tree Index_** O(log(n))
  B-tree generalizes the binary search tree to allow more than 2 branches in the nodes. The index tree is stored separately from the data. The lower-level leaves contain the pointers to the actual data rows. [More info about B-tree](https://www.cnblogs.com/qixinbo/p/11048269.html)
  - Range indexes are efficient at processing inequality queries (eg. <, <=, >, <=, between, in, not in, like).
  - Not fast for equality queries.

```sql
create index index_name
[using {btree | hash}]
on table_name (column_name [asc | desc],
...);
```

# Database Transactions

Database operations have two types:

- **_Read(X)_** query
- **_Write(X)_** insertion, deletion, update

Database transactions have two types:

- **_Read-only_** only read(X) operations
- **_Read-Write_** involves write(X) operations

```sql
begin;
update
	accounts
set
	balance = balance - 100.00
where
	name = 'Bob';
update
	accounts
set
	balance = balance + 100.00
where
	name = 'Alice';
commit;
```

**_Consistent Database State_** all data integrity constraints satisfied

- **_integrity rules_** e.g. primary key uniqueness, foreign key references, transaction completeness (enforced by DBMS)
- **_business rules_** e.g. sum of account balance remains 0 after inter-account money transfer (enforced by programmer)

A transaction must begin with a consistent database state, and end with another consistent state. But the intermediate state during a transaction could be inconsistent.

## Transaction Requirements – ACID

- **_Consistency_** On database state, a transaction can only bring it from one consistent state to another by preventing data corruption.
- **_Atomicity_** A transaction’s operations should be executed as a single "unit" altogether (all-or-none).
- **_Durability_** Results of a successful transaction are permanently stored in the system (even in case of power loss or system failures).

> The above is about a single transaction, called CAD requirements. In reality, multiple transactions can occur at the same time and access the same data items. Thus, we have ACID requirements for multiple transactions.

- **_Isolation_** Transactions are executed independently/isolated from each other. Intermediate results of a transaction is not visible to others.

## Transaction Atomicity and Durability

- **_Atomicity_** Transaction in “all-or-none” execution mode
  - **_committed_** Transaction initiates and can complete its execution successfully
  - **_aborted_** Transaction fails at somewhere and can not complete successfully. It then proforms a rollback, all its executions undone
- **_Durability_** Once a transaction has been committed, the effects can not be undone by aborting it

## Transaction States

- **_Active_** the initial state; the transaction begins from here.
- **_Partially Committed_** after the final statement has been executed.
- **_Failed_** after the discovery that normal execution can not proceed.
- **_Aborted_** the transaction rolled back and restored to previous state.
- **_Committed_** after successful completion.

![Transaction States](Pictures/Transaction%20States.jpg)

## Concurrent Transaction Common Problems

- **_Lost Update_** ("modified after write", write-write)  
   two concurrent transactions update the same data element, and one of the updates is lost (overwritten by the other transaction)
  ![Lost Update](Pictures/Lost%20Update.jpg)
  T1 and T2 read the same data and update the data concurrently. The results submited by T2 cause the lost of update by T1.

- **_Dirty Read_** ("modified before read", write-read-rollback)  
   a transaction reads data from a row that has been modified by another running transaction (but not yet committed)
  ![Dirty Read](Pictures/Dirty%20Read.jpg)
  Just before T1 reads some data, T2 updates the same data. However, after that, T2 performs a rollback due to some reason. Now the data read by T1 is inconsistent with the data in the database.

- **_Non-repeatable Read_** ("modified between two reads", read-write-read)  
   a transaction reads the same data element twice, but the data element is changed by another transaction between the two reads
  ![Non-repeatable Read](Pictures/Non-repeatable%20Read.jpg)
  T1 reads some data, T2 then updates the data, so when T1 reas the data again, the data is inconsistent with previous ones.

- **_Phantom Read_** ("modified after read", read-write)  
   a transaction queries the table, but new rows are added or removed by another transaction to the records being read
  ![Phantom Read](Pictures/Phantom%20Read.jpg)
  T1 reads some data based on some conditions, then T2 inserts some new data that matches the condition. (if T1 searches for data with the same condition, more records are returned)

## Transaction Isolation Levels

- **Serializable** the most restrictive one.
- **_Repeatable Read_** allows only committed data to be read and further requires that, between two reads of a data item by a transaction, no other transaction is allowed to update it.
- **_Read Committed_** allows only committed data to be read, but does not require repeatable reads. For instance, between two reads of a data item by the transaction, another transaction may have updated the data item and committed.
- **_Read Uncommitted_** allows uncommitted data to be read. It is the lowest isolation level allowed by SQL.

| Isolation Level  | Dirty Read | Lost Update | Non-repeatable Read | Phantom Read |
| ---------------- | ---------- | ----------- | ------------------- | ------------ |
| Serializable     | N          | N           | N                   | N            |
| Repeatable Read  | N          | N           | N                   | Y            |
| Read Committed   | N          | Y           | Y                   | Y            |
| Read Uncommitted | Y          | Y           | Y                   | Y            |

## Serializable Schedule

- **_Serializable Schedule_** Interleaved execution of transactions that are equivalent to some serial schedule of these transactions
- **_Equivalent Schedules_** Two schedules that yield the same results on the same transactions

> If two operations on the same data has at least one "write" in them, then they can not swap, otherwise will cause a conflict (loss of equivalence) before and after swapping.
>
> 1. I = read(Q), J = read(Q);
> 2. I = read(Q), J = write(Q);
> 3. I = write(Q), J = read(Q);
> 4. I = write(Q), J = write(Q);
>
> Case 1 to case 4 have different results if we swap the order, so I and J operations are conflict in above case 2~4.

- **_(Conflict) Equivalence_** means a set of schedules can be transformed into each other by a series of swaps of nonconflicting instructions.
- **_(Conflict) Serializability_** means a schedule is (conflict) equivalent to a serial schedule.

[Further explaintion in Chinese](https://blog.csdn.net/u013288190/article/details/121276904)

## Transaction management

- **_Autocommit Mode_** default mode in MySQL
  - Each statement is a transaction, as if it were surrounded by `BEGIN` and `COMMIT`
  - If an error occurs during statement execution, the statement is automatically rolled back (can not control it using `ROLLBACK`)
- **_Transaction Mode_** use `BEGIN` and `COMMIT` to switch to transaction mode
  - Supports multiple statements/operations
  - With `BEGIN`, autocommit is disabled until the transaction ends with `COMMIT` or `ROLLBACK`

# Practice

- to dump a database named dvdrental
  ```bash
  cd "C:\Program Files\MySQL\MySQL Server 8.0\bin"
  mysqldump -u root -p --databases dvdrental > my_database.sql
  ```
