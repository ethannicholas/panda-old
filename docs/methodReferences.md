Method References
=================

A *method reference* is a value that refers to an existing 
[method](methods.html). Method references are written:

    <ClassName>::<methodName>

or

    <ClassName>::<methodName>(<parameterTypes>)

For instance, you may refer to the `matches(RegularExpression)` method in 
`panda.core.String` using the expressions `String::matches`, 
`String::matches(RegularExpression)`, or even 
`panda.core.String::matches(panda.core.RegularExpression)`.

If there is more than one method with that name, you must specify the method's
parameter types. For instance, there are several variants of the `String`
method `indexOf`, so `String::indexOf` will result in a compile-time error due
to the ambiguity. Specifying the parameter types, for instance 
`String::indexOf(String)`, allows you to specify the particular method variant
you mean.

Keep in mind, as described in [method types](types.html#methodTypes), that 
instance methods take an additional hidden parameter containing the value of
`self`. For instance, `String::indexOf(String)` ostensibly takes only one 
parameter, but actually has type `(String, String)=>(Int?)`. The first parameter
is `self`, and the second parameter is the visible parameter (the string to
search for). The following code snippet demonstrates how such method references
work:

    def example := "Hello, World!"
    def replace := String::replace(String, String)
    Console.writeLine(replace(example, "Hello", "Goodbye"))

This displays `Goodbye, World!`. Note that the replace function is declared to
take two parameters, but when calling it in this fashion we pass in three
parameters: `self`, followed by its two declared parameters. This code is 
equivalent to:

    def example := "Hello, World!"
    Console.writeLine(example.replace("Hello", "Goodbye")

Method references may also refer to operators. For instance, we can obtain a 
reference to the addition operator defined in the `Int` class:

    def add := Int::+
    Console.writeLine(add(12, 17))

This displays `29`. The built-in operators defined on the numeric classes are
particularly useful in combination with `ListView` functions such as `map`, 
`fold`, and `zip`:

    Console.writeLine((2 ... 10).fold(Int::*))

This combines the numbers 2 through 10 using the `Int::*` function; in other
words, it computes the factorial of 10. To add two arrays of numbers together,
we can `zip` using the `Int::+` operator:

    def list1 := [37, 12, -5]
    def list2 := [8, 9, 14]
    Console.writeLine(list1.zip(list2, Int::+))

This displays `[45, 21, 9]`.