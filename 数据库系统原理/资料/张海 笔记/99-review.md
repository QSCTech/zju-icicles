<link rel="stylesheet" href="/home/zh/workspace/github/markdown-template/apollo.css">
<script src=/home/zh/workspace/github/markdown-template/mathjax/MathJax.js?config=markdown></script>
<script src="/home/zh/workspace/github/markdown-template/pangu.js"></script>
<script>window.onload = pangu.page_spacing;</script>
<script src="/home/zh/workspace/github/markdown-template/highlight.min.js"></script>
<script>
hljs.configure({classPrefix: ''});
hljs.initHighlightingOnLoad();
</script>

# Review

## Relational Algebra

- Select: $\sigma_{predicate}(relation)$
- Project: $\Pi_{attribute, ...}(relation)$
- Union: $r\cup{s}$
- Set-Difference: $r-s$
- Cartesian product: $r\times{s}$
- Rename: $\rho_{x(A_1, ...)}(E)$ (\$n for n-th attribute)
- Set-Intersection: $r\cap{s}=r-(r-s)$
- Natural Join: $r\bowtie{s}=\Pi_{attribute, ...}(\Sigma_{r.attribute=s.attribute\wedge...}(r\times{s})$
- Theta join: $r\bowtie_\theta{s}=\Sigma_\theta(r\bowtie{s})$
- Division: $r{\div}s$
- Assignment: $name\leftarrow{relation}$
- Generalized Projection: $\Pi_{F_1,F_2,...F_n}(E)$
- Aggregation Function: $_{G_1,G_2,...,G_n}\mathcal{G}_{F_1(A_1) as H_1,F_2(A_2) as H_2,...,F_n(A_n) as H_n}(E)$ (Multiset; Function: avg, count, min, max, *-distint)
- Outer join: Pad result with null, instead of dropping.
    - Left outer join: $r\backslash_{leftouterjoin}s=(r{\bowtie}s)\cup(r-\Pi_R(r{\bowtie}s))\times{(null,...,null)}$
    - Right outer join: $r\backslash_{rightouterjoin}s$
    - Full outer join: $r\backslash_{fullouterjoin}s$
- Delete: $r{\leftarrow}r-E$
- Insert: $r{\leftarrow}r{\cup}E$
- Update: $r{\leftarrow}\Pi_{F_1,F_2,...,F_n}(\sigma_P(r))\cup\Pi_{F_1,F_2,...,F_n}(r-\sigma_P(r))$

    Where $F_i$ is the update function when modification is needed, or original attribute value otherwise.

Find largest/smallest: $\Pi_{attribute}(table)-\Pi_{table.attribute}(\Sigma_{table.attribute&lt;self.attribute}(table\times\rho_{self}(table)))$

Division: $r{\div}s=\Pi_{R-S}(r)-\Pi_{R-S}((\Pi_{R-S}(r){\times}s)-\Pi_{R-S,S}(r))$ ($\Pi_{R-S,S}(r)$ is only for attribute reordering)

## SQL

Division:

```sql
(SELECT R-S FROM r)
EXCEPT
(SELECT R-S FROM (
    (SELECT * FROM (SELECT R-S FROM r), s)
    EXCEPT
    (SELECT * FROM r))
))
```

```sql
SELECT DISTINCT x.A FROM r AS x WHERE NOT EXISTS (
    SELECT * FROM s AS y WHERE NOT EXISTS (
        SELECT * FROM r AS z WHERE (z.A = x.A) AND (z.B = y.B)
    )
)
```

```sql
SELECT A FROM r WHERE B IN (SELECT B FROM s) GROUP BY A HAVING COUNT(*) = (SELECT COUNT(*) FROM t)
```

http://dev.mysql.com/doc/refman/5.7/en/example-maximum-column-group-row.html

Row with group-wise maximum column:

```sql
SELECT * FROM table t1
WHERE column = (
    SELECT MAX(t2.column)
    FROM table t2
    WHERE t1.group = t2.group
)
```

```sql
SELECT t1.* FROM table t1 NATURAL JOIN (
    SELECT group, MAX(column) AS column FROM table GROUP BY group
) AS t2
```
