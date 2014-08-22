Types
=====

A *type* is a kind of data, such as `String` or `Int32`. The primitive Panda
types are described under [basic types](basicTypes.html). Every type has an
associated [class](classes.html), but more than one type may map to the same
class: for instance, `String` and `String?` are two distinct types, 
but are the same class (`panda.core.String`).

The full syntax for a class type is:

`<class>[<parameters>][?]`

Example: `Array<Int64>?` (nullable array of `Int64`s)

`<class>` is the name of any Panda class, such as `Int32` or `String`. Class
names may or may not be [fully qualified](packages.html#fullyQualified).

The `<parameters>` are an optional comma-separated list of types, surrounded by
angle brackets (`<type1, type2>`). Parameters will eventually be used by Panda
generic types, but at the moment parameters are only used by 
[`Array`](arrays.html).

The optional question mark at the end of a type name identifies the type as 
being [*nullable*](nonNullability.html). Without a trailing question mark, the
type is non-nullable and thus [`null`](null.html) is not a legal value for the
type.

Every [expression](expressions.html) in Panda has a type. Panda uses
[type inference](typeInference.html) to automatically determine the types of
[fields](fields.html) and [variables](variables.html).

The run-time type of a value is not necessarily the same as its compile-time
type. For instance, in the code:

    var s:Object := getString()

presuming that `getString()` does as its name suggests and returns a `String`,
then the variable `s` will contain a `String` and thus have a run-time type of 
`String`. But as its type was explicitly declared as `Object`, it has a
compile-time type of `Object`. You therefore could not write:

    processString(s)

because you would be passing an `Object` to a method expecting a `String`. A
[cast](operators.html#cast) instructs the compiler to treat an object as a
different compile-time type; in this case you could write:

    processString(s->(String))

in order to make this call. Of course, in this case it would have been better to 
simply declare `s` as being the right type to begin with!

<a name="methodTypes"></a>
Method Types
------------

In addition to the class types described above, [methods](methods.html) have
types. The type of a function encapsulates its parameter types and return type 
in the form `(<parameterTypes>)=>(<returnType>)`, e.g.:

    (Real, Real)=>(Real)

This type represents a function taking two `Real` parameters and returning a
`Real` result, as in:

    @class
    function add(x:Real, y:Real):Real {
        return x + y
    }

Methods which are not functions (i.e. they potentially have side effects) have
a slightly different signature:

    (Real, Real)=&>(Real)

The ampersand in the middle of the arrow signifies "and other effects", as a
method may perform unspecified other actions. Methods may also be declared to 
not return a value, in which case the return type is left blank. The signature 
of the `System.exit(Int)` method, for example, is:

    (Int)=&>()

signifying that it takes a single `Int` as a parameter, has side effects, and
does not return a value.

Function types such as `(Int)=>(Int)` may be used in contexts where the 
equivalent method type (in this case `(Int)=&>(Int)`) is expected, but the
reverse is not true.

Instance methods and functions (as opposed to `@class` methods and functions)
have an additional, hidden parameter: their first parameter is `self`. Therefore
the type of the `String.startsWith(String)` function is:

    (String, String)=>(Bit)

The first parameter is `self` and the second is the declared parameter of the
function.

This means that the code:

    def startsWith := String::startsWith(String)
    Console.writeLine(startsWith("Hello, World!", "Hello"))

is equivalent to:

    Console.writeLine("Hello, World!".startsWith("Hello"))

In a variadic method, the variadic parameter will appear as a `ListView`. For
instance, the method:

    class Foo {
        method writeAll(s:String...) {
            ...
        }
    }

has type:

    (Foo, ListView<String>)=&>()

The first parameter type (`Foo`) is the implicit `self` parameter, because
`writeAll` is an instance method in the class `Foo`, and the second parameter is
a `ListView` containing all of the variadic parameters.

**IMPLEMENTATION NOTE:** ListView isn't implemented yet, as it's blocked on
generics. Right this second variadics are actually an Array.

Because inline methods and lambdas can capture values, and those values can 
potentially be mutable, methods can end up being either mutable or immutable. 
The types described above are mutable, permitting both immutable and mutable 
values to be assigned to them. To restrict a method type to immutable method 
values only, add an asterisk (`*`) after the arrow:

    ()=>(Int) -- mutable function
    ()=&>(Int) -- mutable method
    ()=>*(Int) -- immutable function
    ()=&>*(Int) -- immutable method

Tuple Types
-----------

The type of a [tuple](tuples.html) is described by a parenthesized list of type
names:

    var tuple:(Object, Int)
    tuple := ("Tuple", 12)

Tuples must contain at least two types. Tuples are never modifiable, but will
only be considered immutable if all of the values they contain are also 
immutable.