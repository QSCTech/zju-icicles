= Numerical Analysis 24 Fall

== I. Multiple Choice Questions (16 pts)
<i.-multiple-choice-questions-16-pts>
#block[
#set enum(numbering: "1)", start: 1)
+ #strong[Evaluate the function] $f (x) = 2 x^2 - 0.1 x$ at $x = 5.21$ using 4-digit arithmetic with chopping. What is the result?
]

#block[
#set enum(numbering: "(A)", start: 1)
+ 53.75 

+ 53.76 
+ 53.77 
+ 53.74
]

#block[
#set enum(numbering: "1)", start: 2)
+ #strong[Given a symmetric, positive real matrix $A$ and initial eigenvalue guesses $lambda_1^\* , lambda_2^\*$ such that $|lambda_1^\* - lambda_1| > |lambda_2^\* - lambda_2|$,] which iterative method will converge with the best rate?
]

#block[
#set enum(numbering: "(A)", start: 1)
+ $x_n = (A - lambda_1^\* I) x_(n - 1)$ 

+ $x_n = (A - lambda_2^\* I) x_(n - 1)$ 
+ $(A - lambda_1^\* I) x_n = x_(n - 1)$ 
+ $(A - lambda_2^\* I) x_n = x_(n - 1)$
]

#block[
#set enum(numbering: "1)", start: 3)
+ #strong[Which of the following iterative methods is unstable with respect to numerical error growth at $x_0$?]
]

#block[
#set enum(numbering: "(A)", start: 1)
+ $x_(n + 1) = 3 x_n + 2$ 

+ $x_(n + 1) = 1 / 6 x_n + 100$ 
+ $x_(n + 1) = 7 / 8 x_n + 20$ 
+ $x_(n + 1) = 0.1 x_n + 10$
]

#block[
#set enum(numbering: "1)", start: 4)
+ #strong[Given the points $x_0 = 1 , x_1 = 2 , x_2 = 3$, which of the following is not a Lagrange basis function?]
]

#block[
#set enum(numbering: "(A)", start: 1)
+ $- (x - 1) (x - 3)$ 
+ $frac((x - 1) (x - 2), 2)$ 

+ $frac((x - 2) (x - 3), 2)$ 
+ $frac((x - 1) (x - 3), 2)$
]

== II. Fill in the Blanks (30 pts)
<ii.-fill-in-the-blanks-30-pts>
#block[
#set enum(numbering: "1)", start: 1)
+ #strong[For the equation] $5 x^2 + x - 6 = 0$, determine if the following fixed-point iterations starting with $x_0 = 0.9$ are convergent. Fill 'True' if convergent, 'False' if not. (2 pts each)
]

- $x = sqrt(frac(6 - x, 5))$ 

- $x = 6 - 5 x^2$ 
- $x = sqrt(frac(- 3 x^2 - x + 6, 2))$

#block[
#set enum(numbering: "1)", start: 2)
+ #strong[Given points] $x_0 = 1 , x_1 = 2$, and the derivative at $x_0$, determine the three basis polynomials for Hermite interpolation. (2 pts each)]

#block[
#set enum(numbering: "1)", start: 3)
+ #strong[Given the matrix] $mat(delim: "[", 100, 14; 14, 4)$, find its eigenvalues and condition number under the spectral norm. (2 pts each)]

#block[
#set enum(numbering: "1)", start: 4)
+ #strong[To minimize the local truncation error of the formula]
  $ w_(l + 1) = a_0 w_l + a_1 w_(l - 1) + beta h f_(l + 1) $
  for solving the IVP $y' = f (t , y)$, find the values of $a_0$, $a_1$, and $beta$. (2 pts each)]

#block[
#set enum(numbering: "1)", start: 5)
+ #strong[Find the monic polynomials] $phi_k (x)$ (for $k = 0 , 1 , 2$) that are orthogonal on $[0 , 4]$ with respect to the weight function $rho (x) = 1$. (2 pts each)]

== III. Iterative Method Convergence (12 pts)
<iii.-iterative-method-convergence-12-pts>
Given $A = mat(delim: "[", 8, 2; 0, 4)$, $arrow(b) = mat(delim: "[", 2; 1)$, and the iterative method
$ arrow(x)^((k)) = arrow(x)^((k - 1)) + omega (A arrow(x)^((k - 1)) - arrow(b)) $ answer the following:

#block[
#set enum(numbering: "1)", start: 1)
+ #strong[For which values of] $omega$ #strong[will the method converge?]
  (8 pts)

+ #strong[For which values of] $omega$ #strong[will the method converge the fastest?] 
  (4 pts)
]

== IV. Vector Norm Proof (10 pts)
<iv.-vector-norm-proof-10-pts>
Prove that $||X||_1 = sum_(i = 1)^n |X_i|$ is a valid vector norm, where $X_i$ is the $i$-th component of vector $X$.

== V. Richardson Extrapolation (10 pts)
<v.-richardson-extrapolation-10-pts>
Given the formula for the second derivative approximation
$ f^\* (x_0) = frac(f (x_0 + h) - 2 f (x_0) + f (x_0 - h), h^2) - h^2 / 12 f^((4)) (x_0) - h^4 / 360 f^((6)) (xi) , $
derive a better formula to approximate $f'' (x_0)$ with error $O (h^4)$ using Richardson extrapolation.

== VI. Least Squares Fit (12 pts)
<vi.-least-squares-fit-12-pts>
Find the values of $a$ and $b$ such that $y = a x + b x^3$ fits the following data using least squares, weighted by the given weights:

#figure(
  align(center)[#table(
    columns: 4,
    align: (auto,auto,auto,auto,),
    stroke: none,
    [$X$], table.vline(),[1], [2], [3],
    [$Y$], [-4], [24], [6],
    [Weights], [1], [1/4], [1/9],
  )]
  , kind: table
  )

== VII. Region of Absolute Stability (10 pts)
<vii.-region-of-absolute-stability-10-pts>
For the following methods solving Initial-Value Problems for ODEs, calculate the region of absolute stability using the test equation $y' = lambda y$ with $"Re" (lambda) < 0$. Which method is more stable (or are they the same)?

#block[
#set enum(numbering: "1)", start: 1)
+ #strong[Second-order Runge-Kutta implicit method]
  $ W_(i + 1) = w_i + h K_1 , quad K_1 = f (t_i + h / 2 , w_i + h / 2 K_1) $

+ #strong[Adams-Moulton one-step implicit method]
  $ w_(i + 1) = w_i + h / 2 (f_(i + 1) + f_i) $
]