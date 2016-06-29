# Relation Model

## Database Structure

Table (表) / Relation (关系): Cartesian product of domains.

Relationship: Relationship in ER model.

Row (行) / Tuple (元组)

Tuple variable: Variable representing a tuple.

Attribute (属性)

Domain (域): Allowed attribute values.

Atomic (原子): Domain elements cannot be divided.

Null: Value unknown or does not exist, should be eliminated if possible.

## Schema

Database schema (数据库模式): Logical design of the database.

Database instance (数据库实例): Snapshot of the data in the database at a given instant in time.

Relation schema (关系模式): Relation is instance, then relation schema is type definition.

Schema: R = (attribute, ...), definition of a schema.

Instance: r(R) = instance(attribute, ...), instance is a relation on schema.

Use more relations to avoid null.

## Key

A tuple in a relation must be unique.

Superkey (超码): A set of one or more attributes that can uniquely identify a tuple in a relation.

Candidate key (候选码): Minimum superkey.

Primary key (主码): Chosen candidate key, as principal means of identifying tuples within a relation.

Foreign key (外码)：Attribute that is the primary key of another relation. The relation is referencing relation, the other relation is referenced relation.

Schema diagram: Rectangles for relations, relation name, primary key, attributes from top to bottom, arrows for foreign key dependencies.

## Query Language

Query language: Language in which user request information from database.

Procedural query language: User instruct system to get result.

Non-procedural query language: User describe the desired information.

## Fundamental Relational-Algebra

Operations can be composed together.

* Select (选择)

    $$\sigma_{predicate}(relation)$$

    Select tuple that satisfy a given predicate.

* Project (投影)

    $$\Pi_{attribute, ...}(relation)$$

    Return relation with certain attributes left out.

* Union (并)

    $$r{\cup}s$$

    Removes duplicates because result is a set.

    Need to be compatible.

    Compatible:

    * r and s should be of the same arity, i.e. they have same number of attributes.

    * Corresponding domains of r and s should be the same.

* Set-Difference (差)

    $$r-s$$

    Need to be compatible.

* Cartesian product (笛卡尔积)

    $$r{\times}s$$

    Attributes should have distinct names, and relation name prefix can be dropped for simplicity if there is no ambiguity.

    The result relation schema is the concatenation of r's and s'.

    The result relation contains all tuples for which the sub-tuples satisfy.

* Rename (重命名)

    $$\rho_{x(A_1, ...)}(E)$$

    Return E evaluated and give E the name x, optionally rename attributes to A_1, ... if given.

Positional notation: \$n for n-th attribute

## Additional Relational-Algebra

* Set-Intersection

    $$r{\cap}s$$

    $$r{\cap}s=r-(r-s)$$

* Natural Join

    $$r{\bowtie}s$$

    Cartesian product, select with common attribute, remove duplicate attribute.

    Associative

    Theta join

    Natural join with extra predicate for select.

    $$r{\bowtie}_{\theta}s$$

* Division

    $$r{\div}s$$

    When r on R-S have all values in S.

    $r{\div}s=\Pi_{R-S}(r)-\Pi_{R-S}((\Pi_{R-S}(r){\times}s)-\Pi_{R-S,S}(r))$ ($\Pi_{R-S,S}(r)$ is only for attribute reordering)

* Assignment

    $$name \leftarrow $$

## Extended Relational-Algebra

* Generalized Projection

    $$\Pi_{F_1,F_2,...F_n}(E)$$

    Allow function in projection.

* Aggregation Function

    $$_{G_1,G_2,...,G_n}\mathcal{G}_{F_1(A_1) as H_1,F_2(A_2) as H_2,...,F_n(A_n) as H_n}(E)$$

    Input a multiset and output a single value.

    Multiset: Elements not unique, but unordered.

    Function: avg, count, min, max, *-distint.

* Outer join

    Pad result with null, instead of dropping.

    * Left outer join

        $$r{\leftouterjoin}s$$

        Include all rows in left.

        $$(r{\bowtie}s)\cup(r-\Pi_R(r{\bowtie}s))\times{(null,...,null)}$$

    * Right outer join

        $$r{\rightouterjoin}s$$

    * Full outer join

        $$r{\fullouterjoin}s$$

## Null

* Arithmetic operations involving null returns null.

* Comparison operations involving null returns unknown.

* Boolean operations:

    * true and unknown = unknown, false and unknown = false, unknown and unknown  = unknown

    * true or unknown = true, false or unknown = unknown, unknown or unknown  = unknown

    * not unknown = unknown

* Select: Discard row when predicate returns unknown or false.

* Join: According to select, common null returns unknown, so discarded.

* Projection: Null is the same. (Kind of arbitrary)

* Union, Intersection, Difference: Null is the same. (Kind of arbitrary too)

* Generalized projection: As projection.

* Aggregate: Null is the same when grouping, discarded when aggregating.

* Outer join: As join.

## Database Modification

* Delete

    $$r{\leftarrow}r-E$$

* Insert

    $$r{\leftarrow}r{\cup}E$$

* Update

    $$r{\leftarrow}\Pi_{F_1,F_2,...,F_n}(\sigma_P(r))\cup\Pi_{F_1,F_2,...,F_n}(r-\sigma_P(r))$$

    Where $F_i$ is the update function when modification is needed, or original attribute value otherwise.
