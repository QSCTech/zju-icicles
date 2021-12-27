//Next, try to support Double/Float/String type for binary tree?
abstract class Set[A] {
  def incl(a: A): Set[A]
  def contains(a: A): Boolean
}

class NonEmpty[A](elem: A, left: Set[A], right: Set[A], 
  lessThan: (A, A) => Boolean) extends Set[A] {
  def contains(x: A): Boolean =
    if (lessThan(x, elem)) left contains x //assign to left
    else if (lessThan(elem, x)) right contains x //assign to right
    else true

  def incl(x: A): Set[A] =
    if (lessThan(x, elem)) new NonEmpty[A](elem, left incl x, right, lessThan)
    else if (lessThan(elem, x))
      new NonEmpty[A](elem, left, right incl x, lessThan)
    else this
}

class Empty[A] (lessThan: (A, A) => Boolean) extends Set[A] {
  def contains(x: A): Boolean = false
  def incl(x: A): Set[A] = 
    new NonEmpty[A](x, new Empty[A](lessThan), new Empty[A](lessThan), lessThan)
}

//compare with Doubles
def dless(x: Double, y: Double): Boolean = {
  if (x < y) true
  else false
}

//compare with Floats
def fless(x: Float, y: Float): Boolean = {
  if (x < y) true
  else false
}

//compare with Strings
def sless(x: String, y: String): Boolean = {
  if (x.compare(y) < 0) true
  else false
}

///// create a Double binary tree with (1.0, 2.5, -4.3, 3.14, 1.7)
val ld = List(1.0, 2.5, -4.3, 3.14, 1.7)
val etd = new Empty[Double] (dless)
var btd = etd.incl(1.0)
var i = 0
for (x <- ld) {
  if (i==0) {
    //do nothing
  } else {
    btd = btd.incl(x)
  }
  i = i + 1
}
//btd now is the new tree with many Double elements
//try btd.contains(3.14), btd.contains(-4.3), btd.contains(2.0),...


///// create a String binary tree with some words
val ls = List("abc", "efg", "X12yo", "World", "21maN")
val ets = new Empty[String] (sless)
var bts = ets.incl("abc")
var i = 0
for (x <- ls) {
  if (i==0) {
    //do nothing
  } else {
    bts = bts.incl(x)
  }
  i = i + 1
}
//bts now is the new tree with many String elements
//try bts.contains("abc"),...

