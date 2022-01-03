A=[4 -1 -2
-1 2 -1
-2 -1 3];
b = [1
0
1];

lu(A)

[L, U] = lu(A)

y = inv(L) * b

x = inv(U) * y
