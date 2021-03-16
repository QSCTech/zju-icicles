class Rational(x: Int, y: Int) {
  require(y>0, "denominator must be positive")
  private def gcd(a: Int, b: Int): Int = if (b==0) a else gcd(b, a%b)
  private val g = {
    val v = gcd(x, y)
    if (v>0) v else -v
  }
  def numer = x / g
  def denom = y / g

  //no problem to be values or functions
  //val numer = x / g
  //val denom = y / g

  def + (r: Rational) = 
    new Rational (
      numer * r.denom + r.numer * denom,
      denom * r.denom
    )

  def - (r: Rational) = 
    new Rational (
      numer * r.denom - r.numer * denom,
      denom * r.denom
    )

  def * (r: Rational) = 
    new Rational (numer * r.numer, denom * r.denom)

  def / (r: Rational) = 
    new Rational (numer * r.denom, denom * r.numer)

  def less(that: Rational) = 
    numer * that.denom < that.numer * denom

  def max(that: Rational) =
    if (this.less(that)) that else this

  //auxiliary constructor
  def this(x: Int) = this(x, 1)

  //printing procedure
  override def toString = {
    if (denom==1) numer.toString
    else numer + "/" + denom
  }
}

val x = new Rational (1, 2)
println(x.numer)
println(x.denom)

val y = new Rational (3, 6)
println(y.numer)
println(y.denom)

val z = new Rational (6, 10)
println(z.numer)
println(z.denom)

//gcd is the greatest common divisor
