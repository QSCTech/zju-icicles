
abstract class IntSet {  //binary tree for Int only
  def incl(x: Int): IntSet
  def contains(x: Int): Boolean
}
//abstract class has no implementation

class NonEmpty(elem: Int, left: IntSet, right: IntSet) extends IntSet {
  def contains(x: Int): Boolean =
    if (x < elem) left contains x //assign to left
    else if (x > elem) right contains x //assign to right
    else true

  def incl(x: Int): IntSet =
    if (x < elem) new NonEmpty(elem, left incl x, right)
    else if (x > elem) new NonEmpty(elem, left, right incl x)
    else this
}

object Empty extends IntSet { //class Empty has singleton instance
  def contains(x: Int): Boolean = false
  def incl(x: Int): IntSet = new NonEmpty(x, Empty, Empty)
}

/////// create a tree with (0,3,4,2,9,1,6)
val le = List(0,3,4,2,9,1,6)
val et = Empty
var bt = et.incl(0)
var i = 0
for (x <- le) {
  if (i==0) {
    //do nothing
  } else {
    bt = bt.incl(x) 
  }
  i = i + 1
}
//bt now is the new tree with many elements
//try bt.contains(1), bt.contains(7),...
