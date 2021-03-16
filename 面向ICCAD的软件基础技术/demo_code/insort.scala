//InsertionSort program works with Rational class

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

val compareRationals: (Rational, Rational) => Int = 
  (x: Rational, y: Rational) => {
    if (x.numer*y.denom > y.numer*x.denom) 1
    else if (x.numer*y.denom == y.numer*x.denom) 0
    else -1
  }

implicit val rationalOrder: Ordering[Rational] =
  new Ordering[Rational] {
    def compare(x: Rational, y: Rational): Int = compareRationals(x, y)
 }


def insertionSort[T](xs: List[T])(implicit ord: Ordering[T]): List[T] = {
  def insert(y: T, ys: List[T]): List[T] =
    ys match {
      case Nil => y :: Nil
      case z :: zs =>
        if (ord.lt(y, z)) y :: z :: zs
        else z :: insert(y, zs)
    }

  xs match {
    case Nil => Nil
    case y :: ys => insert(y, insertionSort(ys)(ord))
  }
}

//have tried,
//val l = List[String]("aadf", "fdewf", "12312", "eretgr", "13SFS")
//insertionSort[String](l)
//it reports a sorted result,
//List(12312, 13SFS, aadf, eretgr, fdewf) 

//have tried,
val half = new Rational(1, 2)
val third = new Rational(1, 3)
val fourth = new Rational(1, 4)
val rationals = List(third, half, fourth)
insertionSort(rationals)
//it reports a sorted result,
//List(1/4, 1/3, 1/2)

