# Relation Database Design

## First Normal Form

Atomic: If domain's elements are considered to be indivisible.

A relational schema R is in first normal form (1NF) if the domains of all attributes of R are atomic.

Dealing with non-atomic values:

* Multiple fields

* Separate table

* A single field

## Pitfalls in Relational Database Design

Bad design: Redundant storage, insert / delete / update anomalies.

Decomposition requirements:

* All attribute must appear in the decomposition.

* Lossless join decomposition: Can be joined to form the original one.

## Functional dependency

The functional dependency holds on R if and only if for any legal relations r(R), whenever any two tuples t1 and t2 of r agree on the attributes, they also agree on the attributes , i.e., t1[α] = t2[β] => t1[α] = t2[β].

A functional dependency is a generalization of the notion of a key.

K is a superkey for the relation schema R if and only if K -> R.

K is a candidate key for R if and only if K -> R, and No α in K, α -> R.
Functional dependency set: Set of functional dependencies.

Trivial (平凡) dependency: If it is satisfied by all relations.

In general, α -> β is trivial if β is a subset of α.

Closure of a set of functional dependencies: The set of all functional dependencies logically implied by F, denoted by F^+.

Armstrong's axioms:

* Reflexivity (trivial)

    If β is a subset of α, then α -> β.

* Augmentation

    If α -> β, then γα -> γβ, or γα -> β

* Transitivity

    If α -> β, and β -> γ, then α -> γ.

Sound and complete.

Armstrong's Axioms supplements:

* Union

    A -> B, A -> C => A -> BC: A -> AB, AB -> BC

* Decomposition

    A -> BC => A -> B, A -> C: BC -> B, BC -> C (From Reflexivity)

* Pseudo-transitivity

    A -> B, BC -> D => AC -> D: AC -> BC

Computing F^+:

do {
    for f : F^+ {
        F^+.add(Reflexivity and augmentation applied on f);
    }
    for (f_1, f_2) : F^+ {
        F^+.add(Transitivity applied on (f_1, f_2));
    }
} while (F^+ changed);

Closure of attribute set A: The set of attributes that are functionally determined by A under F, denoted by A^+.

Computing A^+:

A^+ = A;
do {
    for B -> C in F {
        if (A.containsAll(B)) {
            A^+.add(C);
        }
    }
} while (A^+ changed);

Candidate keys can also be inferred from graphs.

Attribute set closure usage:

* Testing for super key

    Check if α contains all attributes of R.

* Testing functional dependencies

    Check if β is in α^+.

* Computing closure of F

    All α -> S for S in α^+ forms F^+.

Canonical cover (正则覆盖):

A minimal set of functional dependencies equivalent to F, denoted by F_c. No redundant FD, nor redundant part of FD.

Extraneous attributes (无关属性):

* Redundant FD that can be inferred.

* Redundant part of FD on left side.

* Redundant part of FD on right side. (Decomposition)

α -> β:

Check if attribute A in α is extraneous: Check if (α - A)^+ on F contains β.

Check if attribute B in β is extraneous: Check if α^+ on F' contains B, where F' = (F - {α -> β}) union {α -> (β - A)}

Computing canonical cover:

do {
    union A->C and B->C to AB->C
    find and delete extraneous attribute
} while (A^+ changed);

## Decomposition

Decomposition requirements:

* All attribute must appear in the decomposition.

    R = R_1 union R_2

* Lossless join decomposition: Can be joined to form the original one.

    {R_1 intersect R_2} -> R_1 or R_2

* Dependency preservation: FD checking can be done within subrelation.

    (union F_i)^+ = F^+

    For every dependency in F, check if one subrelation contains it.

* No redundancy: R_i in Either BCNF, or 3NF

## Boyce-Codd Normal Form

Every functional dependency in F^+, whether it is trival, or lhs is a super key for R.

If F for R does not violate BCNF, then F^+ derived from it will not for R.

可在 F 下判断 R 是否违反 BCNF，但必须在 F^+ 下判断 R 的分解是否违反 BCNF 范式。

BCNF may not preserve functional dependency.

```
result := {R};
    done := false;
    compute F+;
    while (not done) do
        if (there is a schema Ri in result that is not in BCNF)
        then begin
            let α -> β be a nontrivial functional
            dependency that holds on Ri such
            that α -> Ri is not in F+, and α intersect β is empty;
            result := (result – Ri) union (α, β) union (Ri – β);
        end else done := true;
```

Note: Finally, every sub-schema is in BCNF, and the decomposition is lossless-join.

## Third Normal Form

Every functional dependency in F^+, either it is trival, or lhs is a super key for R, or each attribute in (rhs - lhs) is in any candidate key for R.

Ensures decomposition.

If R is BCNF, then R is 3NF.

A schema that is in 3NF but not in BCNF has the problems of repetition of information, and may need to use null values.

If F for R does not violate 3NF, then F^+ derived from it will not for R.

## Multivalued Dependencies


