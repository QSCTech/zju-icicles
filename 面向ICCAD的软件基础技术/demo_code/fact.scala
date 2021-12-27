import scala.annotation.tailrec

def factorial(n: Int): Int = {
  @tailrec def iter(x: Int, result: Int): Int =
    if (x==1) result
    else iter(x-1, result*x)

  iter(n, 1)
}

println(factorial(3))
println(factorial(4))
println(factorial(5))
