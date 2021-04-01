sealed trait Symbol
case class Note(name: String, duration: String, octave: Int) extends Symbol
case class Rest(duration: String) extends Symbol

val symbol1: Symbol = Note("C", "Quarter", 3)
val symbol2: Symbol = Rest("Whole")

def symbolDuration(symbol: Symbol): String =
  symbol match {
    case Note(name, duration, octave) => duration
    case Rest(duration) => duration
  }

println(symbolDuration(symbol1))
println(symbolDuration(symbol2))

sealed trait NoteName
case object A extends NoteName
case object B extends NoteName
case object C extends NoteName
case object D extends NoteName
case object E extends NoteName
case object F extends NoteName
case object G extends NoteName

case class FixNote(name: NoteName, duration: String, octave: Int) extends Symbol
val symbol3: Symbol = FixNote(A, "Half", 4)
val symbol4: Symbol = FixNote(G, "Half", 4)
