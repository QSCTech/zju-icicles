# Entity-Relationship Model

Entity set: Set of entities.

Extension: The actual collection of entities belonging to the entity set.

Attribute: Descriptive property.

Value: Value for each of its attributes.

Domain: Domain of attribute.

* Simple / Composite: Can have sub-parts.

* Single-valued / Multi-valued: single value or a list of values.

* Derived: Can be inferred from base.

Relationship: Association among several entities.

Relationships set: Set of relationships of the same type.

Relationship instance: Association between the named entities.

Role: The function that an entity plays in a relationship.

Recursive relationship set: the same entity set participates in a relationship set more than once, in different roles.

Descriptive attributes: A relationship may also have descriptive attributes.

Degree of relationship set: Usually binary

Mapping cardinality: The number of entities to which another entity can be associated via a relationship set.

* One to one

* One to many

* Many to many

Participation: Total, partial

In general, any non-binary relationship can be represented using binary relationships by creating an artificial entity set.

Weak entity set: Entity set that does not have a primary key.

The existence of a weak entity set depends on the existence of a identifying entity set or owner entity set.

Weak entity sets must relate to the identifying entity set via a total, one-to-many relationship set from the identifying to the weak entity set.

The discriminator or partial key (分辨符或部分码) of a weak entity set is the set of attributes that distinguishes among all those entities in a weak entity set that depend on one particular strong entity.

The primary key of a weak entity set is formed by the primary key of the strong entity set on which the weak entity set is existence dependent, plus the weak entity set’s discriminator.

## Extended E-R features

Specialization:

Disjoint, Completeness (Total, partial)

Aggregation: Treat relationship as an abstract entity, allow relationships between relationships.

## Design

1. Requirement analysis

2. Conceptual design

3. Logical design

4. Physical design

E-R design decisions:

* Attribute or entity set

    * Single-value => Attribute

* Entity set or relationship set

    * Action that occurs between entities => Relationship set

## Representation

* Strong entity set => Table

* Composite attribute => Multiple attributes

* Multi-valued attribute => Separate table

* Weak entity set => Table, with primary key coined by primary key of identifying set and partial key

* Relationship set => Table, with foreign keys and its descriptive attributes

* Specialization => Tables with additional attributes, or one table with all possible attributes.

## Reduction

* One to total many (one) relationship set, merge one of relationship set into many side, reducing the relationship table.

* Weak entity set, merge relationship set into weak entity set.


