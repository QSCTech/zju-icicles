# Advanced SQL

## Data Type And Schema

```sql
CREATE TYPE type_name AS data_type_specification
DROP TYPE type_name
CREATE DOMAIN domain_name AS data_type_specification [NOT NULL]
```

Not supported in mysql.

Binary Large Object: BLOB(n (KB|MB))
Character Large Object: CLOC(n (KB|MB))

## Integrity Constraint

NOT NULL

PRIMARY KEY

UNIQUE

CHECK

Referential integrity (subset dependency): Referencing foreign key must exist in referenced relation or be null.

### Cascading Actions

```sql
FOREIGN KEY key_name REFERENCES foreign_table_name [(foreign_key_name)] ON (DELETE | UPDATE) (RESTRICT | CASCADE | SET (NULL | DEFAULT))
```

Foreign key name defaults to primary key of foreign table, and must be primary or unique (candidate).

Integrity constraint constraint is checked at the end of transaction.

### Assertions

```sql
CREATE ASSERTION assertion_name CHECK predicate
```

No FOR ALL X, P(X) syntax provided; so use NOT EXISTS X, such that not P(X)

e.g. NOT EXISTS (SELECT ...)

### Trigger

```sql
CREATE TRIGGER trigger_name (BEFORE | AFTER) (INSERT | DELETE | UPDATE) [OR ...] [OF row_name] ON column_name (REFERENCING OLD (ROW AS old_row_name | TABLE AS old_table_name) /* DELETE, UPDATE */ | REFERENCING NEW (ROW AS new_row_name | TABLE AS new_table_name) /* INSERT, UPDATE */) FOR EACH (ROW | TABLE) WHEN predicate((old_row_name|new_row_name)) BEGIN ATOMIC
...
END
DROP TRIGGER trigger_name
```

Can implement external world actions by using trigger to record actions to be taken in another table.

## Authorization

Authorization on database: Read, Insert, Update, Delete

Authorization on database schema: Index, Resource, Alternation, Drop

* CREATE VIEW

* GRANT privilege_list ON (table_name | view_name) TO user_list [WITH GRANT OPTION]

privilege_list: SELECT [(column_name)], INSERT, UPDATE [(column_name)], DELETE, REFERENCES, ALL [PRIVILEGES], separated by ",".

Graph based authorization and revocation.

No loop should be made.

CRATE ROLE role_name

And then grant privilege to role, and grant role to user.

REVOKE privilege_list ON (table_name | view_name) FROM user_list [RESTRICT | CASCADE]

If user_list involves PUBLIC, all users lose privilege_list except those granted explicitly.

Audit trail: log, TRIGGER or direct support (binlog).

```sql
AUDIT (table_name | view_name | index_name | role_name) BY user_name [BY SESSION | ACCESS] WHENEVER [NOT] SUCCESSFUL
AUDIT (SELECT | INSERT | UPDATE | DELETE) [, ...] ON (table_name | ... | DEFAULT) BY (SESSION | ACCESS) WHENEVER [NOT] SUCCESSFUL
NOAUDIT table_name ...
```

With system user, see table sys.aud$, dba_audit_trail, dba_audit_statement, dba_audit_object.

## Embedded SQL

EXEC SQL ... END_EXEC

Host variables prepended with ":".
