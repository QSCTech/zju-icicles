trait Animal {
  def fitness: Int
}

trait Mammal extends Animal

class Zebra (f:Int, s: Int) extends Mammal {
  def fitness = f
  val zebraStrip = s
}

trait Giraffe extends Mammal

//who is fitter?
def selection [A <: Animal](a1: A, a2: A): A =
  if (a1.fitness > a2.fitness) a1 else a2

val z1 = new Zebra(2, 3)
val z2 = new Zebra(4, 5)

val zebras: Array[Zebra] = Array(z1, z2)

val zf = selection[Zebra](z1, z2) //select one fitter

//next is not allowed: since Array[T] is invariant to T
//val mammals: Array[Mammal] = zebras

//however, if Field is covariant to T, that is,
class Field[+A <: Animal] (a: A) {
  def get = "An area plus " + a.fitness * 3 //just a play
  //prt() reserved for second try on [A] argument; the first line won't work.
  //def intru(elem: A) = elem.toString + ": invades the area of " + get
  def intru[U >: A](elem: U) = elem.toString + ": invades the area of " + get
}

val zebra_field_1 = new Field[Zebra](z1)
val zebra_field_2 = new Field[Zebra](z2)

//then, next is fully allowed.
val mammal_field_1: Field[Mammal] = zebra_field_1

//however, if Field is defined with no +A but A, it won't be allowed either.
//may try to change Field class definition?
//class Field[A <: Animal] (a: A) {
//  def get = "An area plus " + a.fitness * 3 //just a play
//}

mammal_field_1.get //report as mammal area
zebra_field_1.get //report as zebra area
zebra_field_2.get //report as zebra area

//however again, if Field is defined as with +A and the method intru()
//has an A in its argument, we'll see it won't work again.
//the A in its argument should be change to U>: A, with elem: U
mammal_field_1.intru[Mammal](z1)
mammal_field_1.intru[Mammal](z2)

