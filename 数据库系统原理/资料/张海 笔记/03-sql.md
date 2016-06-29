# SQL

## Background

* DDL (Data Definition Language)

* DML (Data Manipulation Language)

* Integrity

* View definition

* Transaction control

* Embedded SQL and dynamic SQL

* Authorization

## Data Definition

Basic types:

* char(n) / character(n): Fixed-length.

* varchar(n) / character varying(n): Variable-length.

* int / integer: Subset, machine dependent.

* smallint: Small subset, machine dependent.

* numeric(p, d): Fixed-point. p digits (plus a sign), d of the p digits are to the right of the decimal point.

* real, double precision: Floating-point, machine dependent.

* float(n): floating-point, with precision of at least n digits.

* date: YYYY-M-d

* time: HH:mm::ss.n

* timestamp: date + time

```sql
CREATE TABLE table_name (column_name data_type,..., constraint, ...)

constraint:

* NOT NULL

* PRIMARY KEY

* FOREIGN KEY column_name REFERENCES foreign_table_name[(foreign_column_name)]

* CHECK (predicate)

INSERT INTO table_name values (column_value, ...)

DELETE FROM table_name WHERE predicate

DROP TABLE table_name

ALTER TABLE table_name ((ADD | MODIFY) column_name, data_type | DROP column_name)

CREATE [UNIQUE] INDEX index_name on table_name (attribute, ...)

DROP INDEX index_name
```

## Basic Structure of SQL Query

```sql
SELECT [DISTINCT | ALL] (expression [[AS] new_column_name], ... | [table_name.]*) FROM table_name [new_table_name], ... [WHERE predicate] [GROUP BY column_name, ... [HAVING expression_with_aggregate_allowed]] [ORDER BY column_name [ASC|DESC], ...]
```

ALL, ASC is the default.

predicate: AND, OR, NOT, BETWEEN.

BETWEEN predicate: expression [NOT] BETWEEN expression_1 AND expression_2

() for tuple, can be compared, from start to end.

String:

* SQL uses ' for strings. ' in strings is escaped by ''.

* LIKE: % for *, _ for ?. \% and \? for literal.

* Concatenation: ||

* lower(), upper()

## Duplicates

Some SQL defaults to the multiset version of relational algebra.

## Set operations

Set operation removes duplicates by default, add ALL to preserve duplicates.

```sql
UNION [ALL]
INTERSECT [ALL]
EXCEPT [ALL]
```

## Aggregate Functions

* AVG

* MIN

* MAX

* SUM

* COUNT

    COUNT([DISTINCT] expression)

    But COUNT(*) only.

When aggregate function is used, column must be in GROUP BY before it is selected.

HAVING clause is evaluated after GROUP BY, so that aggregate functions can be used; but WHERE clause is evaluated before GROUP BY.

Use "IS [NOT] NULL" instead of "= NULL".

Result of operations involving NULL is natural; NULL result in WHERE clause is treated as false.

All aggregate operations except count(*) ignore tuple with null values on the aggregated attributes.

## Nested Subqueries

Commonly nested in where.

Use IN or NOT IN for testing set membership.

Use SOME(), ALL() for set comparison. SOME = IN, NOT SOME != NOT IN

Use [NOT] EXISTS() for testing empty relation.

Use [NOT] UNIQUE() for testing whether tuples are unique.

## View

```sql
CREATE VIEW view_name [(column_name, ...)] AS SELECT ...
```

Can hide data.

Local view:

* Derived relation: Every derived table must have its own alias.

    ```sql
    SELECT ... FROM (SELECT ...) AS local_view_name [(...)] ...
    ```

* Use WITH.

    ```sql
    WITH local_view_name (...) AS SELECT ...
    SELECT ... FROM ... local_view_name ...
    ```

    A query can have multiple WITH clauses, and each clause can reference the one defined before.

## Modification

Nested SELECT will only be executed once if it does not contain variables from the outer SELECT.

```sql
DELETE FROM table_name WHERE ...

INSERT INTO table_name [(...)] VALUES (...)

INSERT INTO table_name (SELECT ...)

UPDATE (table_name | view_name) SET column_name = new_column_data ...  [WHERE ...]
```

Can only update row-column views (Views on a single table with view columns corresponding to table columns).

Case:

```sql
CASE
    WHEN condition
    THEN value_1
    ELSE value_2
END
```

## Transaction

Commit / Rollback

Atomicity, Isolation, Consistency, Durability.

```sql
BEGIN ATOMIC
END
```

## Join

Type:

* (INNER) JOIN

* LEFT/RIGHT/FULL (OUTER) JOIN

Condition:

* NATURAL

* ON predicate

* USING (column_name, ...)
