Method References
=================

A *method reference* is a value that refers to an existing 
[method](methods.html). Methods are referenced much like fields, using a dot:

    <expression>.<methodName>

For instance:

@SOURCE(
    class Example {
        @class
        function positive(x:Int):Int {
            return x > 0
        }
    }

    def numbers := [1, -5, 19, 3, -9, -52]
    def positiveNumbers := numbers.filter(Example.positive)
)

The expression `Example.positive` is a static reference to the function. Passing
this function to the `filter` function uses it as a predicate to filter out all
non-positive numbers from the list, resulting in `[1, 19, 3]`.

Ambiguous References
--------------------

As methods can be overloaded, method references may be ambiguous. For instance,
the code:

@SOURCE(
    def write := Console.writeLine -- error, ambiguous!
)

does not compile, because there are several overloads of the method 
`Console.writeLine` with various parameters. Ambiguous references are only 
errors if there is not enough context to determine the desired type; assigning
the reference to a variable with the correct type, passing the value to a method
expecting a specific method type, casting to the desired method type, and so
forth will all resolve the ambiguity.

@SOURCE(
    def write1 := Console.writeLine->(String)=&>() -- explicit cast, works!
    def write2:(String)=&>() := Console.writeLine  -- expected type, works!
)

Instance Methods
----------------

The examples so far have demonstrated references to class methods. Instance
methods are slightly more complicated, as they need an object instance to 
operate on. There are two ways to do this. You may reference the method directly
in an instance of the object, in which case the method always applies to that
instance:

@SOURCE(
    def max0 := 0.max -- reference to Int.max function applied to 0
)

Now `max0` is a function you can call, such as `max0(-5)` (yielding `0`) or
`max0(12)` (yielding 12).

You may also reference the method as if it were a class method:

@SOURCE(
    def max := Int.max -- reference to Int.max function with no instance
)

This produces a method reference which takes an extra parameter: the instance to
be operated on. The first parameter of this method reference is the `self` that
the method is to operate on, and all other parameters of the method follow 
normally. Our `max` variable above can be called as `max(89, 42)`, which is 
evaluated the same way that `89.max(42)` would be and yields `89`.

Operator Methods
----------------

Overloaded operators are ordinary methods in Panda, and can be referenced just
as any other method can be. The `panda.core.Int32` class defines the 
`+(Int):Int` instance method, and thus the following can be written:

@SOURCE(
    def add := Int.+ -- (Int, Int)=>(Int), adds two numbers
    Console.writeLine(add(9, 5)) -- displays '14'

    def add10 := 10.+ -- (Int)=>(Int), adds 10 to its argument
    Console.writeLine(add10(25)) -- displays '35'
)