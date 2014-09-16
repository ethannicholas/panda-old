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
is the implicit `self` parameter, and the second parameter is the explicit
parameter (the string to search for). The following code snippet demonstrates 
how such method references work:

@SOURCE(
    def example := "Hello, World!"
    def replace := String::replace(String, String)
    Console.writeLine(replace(example, "Hello", "Goodbye"))
)

This displays `Goodbye, World!`. Note that the replace function is declared to
take two parameters, but when calling it in this fashion we pass in three
parameters: `self`, followed by its two declared parameters. This code is 
equivalent to:

@SOURCE(
    def example := "Hello, World!"
    Console.writeLine(example.replace("Hello", "Goodbye"))
)

Method references may also refer to operators. For instance, we can obtain a 
reference to the addition operator defined in the `Int` class:

@SOURCE(
    def add := Int::+
    Console.writeLine(add(12, 17))
)

This displays `29`. The built-in operators defined on the numeric classes are
particularly useful in combination with `ListView` functions such as `map`, 
`fold`, and `combine`:

@SOURCE(
    Console.writeLine((2 ... 10).fold(Int::*))
)

This combines the numbers 2 through 10 using the `Int::*` function; in other
words, it computes the factorial of 10. To add two arrays of numbers together,
we can `combine` using the `Int::+` operator:

    -- FIXME combine isn't actually implemented yet
    def list1 := [37, 12, -5]
    def list2 := [8, 9, 14]
    Console.writeLine(list1.combine(list2, Int::+))

This displays `[45, 21, 9]`.


Method References and Overriding
--------------------------------

Calls to references to overridden method are appropriately resolved at runtime.
For instance, given the code:

@SOURCE(
    class Super {
        method hello() {
            Console.writeLine("Super says hello!")
        }
    }

    class Sub : Super {
        @override
        method hello() {
            Console.writeLine("Sub says hello!")
        }
    }

    def sub := new Sub()
    def hello := Super::hello
    hello(sub)
)

This program creates a reference to `Super::hello` and then invokes it on an
object of type `Sub`. Given the reference to `Super::hello`, you might expect 
this to display:

    Super says hello!

but since `Sub` overrides the `hello` method, the subclass implementation is 
invoked, and the program actually displays:

    Sub says hello!