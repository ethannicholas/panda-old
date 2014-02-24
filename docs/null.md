null
====

`null` is a special [keyword](keywords.html) which represents the absence of a 
value. [Types](types.html) are [non-nullable](nonNullability.html) by default, 
meaning that `null` is a not a legal value for types by default. The following 
code therefore will not compile:

    var x:String := null -- won't compile, null is not a String

In order to permit `null`s within a type, the type must be declared *nullable*
by adding a question mark (`?`) to the end of the type.

    var x:String? := null -- compiles fine!

As `null` is a valid `String?` (nullable `String`), but is *not* a valid 
`String` (non-nullable `String`), the nullable `String?` variable `x` may not be
used where a non-nullable `String` is expected:

    var x:String? := null
    Console.writeLine(x) -- doesn't compile. writeLine wants a String, not null

See details on [nullability / non-nullability](nonNullability.html) for how to
handle nullable types where non-nullable types are required.

`null` can be [implicitly cast](implicitCasting.html) to any nullable type.