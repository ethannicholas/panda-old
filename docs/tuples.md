Tuples
======

A *tuple* is an ordered sequence of two or more values, which (unlike in an
[array](arrays.html)) may be of different types.

@SOURCE(
    def tuple := ("Tuple", 12)
)

The individual elements in a tuple are extracted using the index operator, just
like with arrays:

@SOURCE(
    def tuple := ("Tuple", 12)
    --BEGIN
    Console.writeLine(tuple[0]) -- writes "Tuple"
)

If the index is a constant integer (as in `tuple[0]`), the type is determined by
the element at that index: in this case, `tuple[0]` has type `panda.core.String`
and `tuple[1]` has type `panda.core.Int32`. 

If the index is not a constant, as in `tuple[i]`, the compile-time type is 
determined from  the union of all of the tuple's element types. In this case, 
the most specific type that could represent both `panda.core.String` and 
`panda.core.Int32` is `panda.core.Value`, so `tuple[i]` has compile-time 
type `panda.core.Value`.

Multiple Assignment
-------------------

You may assign into multiple variables simultaneously in order to extract values
from a tuple.

@SOURCE(
    def tuple := ("Tuple", 12)
    def string, int := tuple
    Console.writeLine(string) -- writes "Tuple"
    Console.writeLine(int)    -- writes "12"
)

This is especially useful for functions which return tuples:

@SOURCE(
    function position():(Real, Real) {
        -*REPLACE:...*---dummy comment
        return (0, 0)--SKIP
    }

    def x, y := position()
)

The number of variables must equal the number of tuple elements. You may ignore
tuple values you do not care about using an underscore ('_') as the "name" of a
value:

@SOURCE(
    def _, x, _ := ("ignored", "I'm x!", "ignored")
)
