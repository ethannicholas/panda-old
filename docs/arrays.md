Arrays
======

An *array* is a list of values. Arrays have [type](type.html)
`panda.collections.Array<elementType>`, where `elementType` is the name of any
Panda type. Example array types are:

* `Array<Int>` - array of `Int`s
* `Array<Int?>` - array of [nullable](nonNullability.html) `Int`s. 
* `Array<Int?>?` - nullable array of nullable `Int`s.
* `Array<Array<String>>` - array of arrays of `String`s

Creating Arrays
---------------

<a name="literals"></a>
### Array Literal Syntax

The simplest way to create an array is the *array literal syntax*:

@SOURCE(
    def a := --SKIP
    [1, 2, 3, 4, 5]
)

This creates a new array containing the five listed numbers. If the array is
being used in a context where the desired type can be inferred, the context
type is used: 

@SOURCE(
    var a:Array<Object> := [1, 2, 3, 4, 5]
)

This creates an array of `Object`s, despite the fact that all of the values are
`Int`s.

If there is no context providing an expected array type, for instance in the 
code:

@SOURCE(
    Console.writeLine([1, 2, 3, 4, 5].class)
)

then the array's type is inferred from its elements. In this case, the output is
`class panda.collections.Array<Int32>`.

### Empty Array

A new, empty array may be created using the syntax:

@SOURCE(
    def a := --SKIP
    new Array<String>()
)

### Initial Length

A new array with an initial length:

@SOURCE(
    def a := --SKIP
    new Array<Int>(30)
)

This will create an array holding 30 copies of the element type's 
[default value](defaultValues.html). In the case of `Int` the default value is
zero, so the resulting array will have 30 zeroes. Arrays of types with no 
default value (non-numeric, non-nullable types) do not possess this constructor
and therefore may not be created in this fashion.

### Values

A new array with a list of values:

@SOURCE(
    def a := --SKIP
    new Array<String>("Hello", "Goodbye")
)

This creates an array containing the listed strings, and is equivalent to the
syntax `["Hello", "Goodbye"]`.

<a name="subrange"></a>
### Subrange of existing array

A new array copied from an existing array:

@SOURCE(
    def array:Array<String> := []
    def a := 
    --BEGIN
    new Array<String>(array, 0, array.length)
)

The three parameters to this constructor are the source array, the offset, and
the length. The offset is the first index of the source array to copy from, and
the length is the number of elements to copy into the resulting array.

For instance,

@SOURCE(
    var a := [1, 2, 3, 4, 5]
    a := new Array<Int>(a, 1, 3)
)

will create a new array with the values `[2, 3, 4]`.

Creating an array in this fashion is very similar to using the 
[slice operator](operators.html#slice), but you can create a different type of 
array, for instance:
    
@SOURCE(
    function foo():Object {
    --BEGIN
    def a:ImmutableArray<String> := ["A", "String", "Array"]
    return new Array<Object>(a, 0, a.length)
    --END
    }
)

The resulting array may differ in mutability (`ImmutableArray` vs. `Array`) or
element type from the source array, with the following restrictions:

* `ImmutableArray` may not be created with mutable elements
* The element type of the source array must be 
  [implicitly castable](implicitCasting.md) to the element type of the
  destination array
* If the source element type is a primitive type, such as `Int32`, the 
  destination array must have the same element type (in other words, you may 
  create an `ImmutableArray<Int32>` from an `Array<Int32>`, but not an 
  `ImmutableArray<Int64>` from an `Array<Int32>`).

Ranges
------

A `range` is a simple way to create a list containing a sequence of numbers:

@SOURCE(
    def a := --SKIP
    -5 ... 5
)

This is equivalent to `[-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5]`. Ranges are
shorthand for the [slice operator](operators.html#slice) applied to the 
appropriate primitive class; in other words `-5 ... 5` is equivalent to 
`Int[-5 ... 5]` and `"0" ... "9"` is equivalent to `Char["0" ... "9"]`.

Just like slicing the `Int` class, the upper bound may be omitted (in which case
it is taken to be `Int.MAX`) and a `by` keyword may be used to specify the step
value. This is the set of all even `Int32` values between 0 and 500:

@SOURCE(
    def a := --SKIP
    0 ... 500 by 2
)

**IMPLEMENTATION NOTE:** Ranges must currently have both bounds specified; the
upper bound may be left unspecified once generics are completed.

Accessing Array Elements
------------------------

Elements of an array may be referenced using the syntax `array[index]`. As with
most programming languages, array indexes begin at zero. For instance,

@SOURCE(
    def numbers := [7, 5, 18]
    Console.writeLine(numbers[1])
)

will display the value `5`.

Likewise,
    
@SOURCE(
    def numbers := [7, 5, 18] --SKIP
    numbers[2] := 12
)

will change the last value in the array from `18` to `12`.

Array.length
------------

The `Array.length` property returns the number of elements in an array.

@SOURCE(
Console.writeLine(["Hello", "Goodbye"].length)
)

Result: `2`

`Array.length` can be assigned to, which will change the length of the array:

@SOURCE(
    def a := new Array<Bit>()
    a.length := 20
)

This creates a new array and sets its length to 20, and is roughly equivalent to
`new Array<Bit>(20)`. Reducing the length of an array will remove elements from
it, whereas increasing its length will add new default-valued entries to it.

For arrays whose elements do not have a default value, the length of the array
may only be decreased, not increased, via this method. Attempting to increase
the length of such an array is a safety violation and will generate a 
`SafetyError` at runtime if safety checks are enabled, or undefined behavior if 
they are not. You must use `append()` (below) to increase the length of such an
array.

Array.append
------------

The `Array.append()` method adds a new element to the end of an array.

@SOURCE(
    var a := [1.2, 6.8]
    a.append(4.5)
    for value in a
        Console.writeLine(value)
)

This will display:

    1.2
    6.8
    4.5

Array.contains
--------------

The `Array.contains()` function performs a linear search and returns whether its
argument is found in the array. For example:

@SOURCE(
    def a := --SKIP
    (1 ... 10).contains(5)
)

will evaluate to `true`.

Array.join
----------

The `Array.join()` function forms a string out of the array's elements. Each
element is converted to a string via its `->>():String` method, and the 
individual strings are joined together separated by a delimiter. For example,

@SOURCE(
    def a := --SKIP
    [1, 2, 3].join(":")
)

yields the string `"1:2:3"`.

Array.fold
----------

The `Array.fold()` function combines elements of the array by applying a binary
function. For instance, we can find the sum of a list of numbers by applying
the addition function:

@SOURCE(
    def a := --SKIP
    [36, 12, 78, 1].fold(Int::+)
)

This results in the sum of the numbers, `127`. First the provided function 
(integer addition) is called on the first and second elements of the list, then
that total is added to the third element, then that total is added to the fourth
element, yielding the sum of the array. Any binary function operating on the
array's element type can be used:

@SOURCE(
    def a := --SKIP
    [48, 2, 18].fold(Int::*) -- yields 1728
)

This variant of `fold()` requires the list to be non-empty. There is another
variant of fold which accepts a "starting value" for the computation:

@SOURCE(
    var numbers := new Array<Int>()
    def a :=
    --BEGIN
    numbers.fold(Int::+, 0)
)

This starts off with a `0`, adds the `0` to the first element of the list (if 
there is one), then that combined total to the second element of the list (if 
there is one), continuing to the end of the list. Since `0` is the additive 
identity, the result will still be the sum of the list's elements, or `0` if the
list is empty. You should generally use this variant of `fold()` where possible,
since it handles empty lists, as in:

@SOURCE(
    function factorial(x:Int):Int {
        -- not the most efficient way to implement this, but elegant!
        return (2 ... x).fold(Int::*, 1)
    }
)

Array.filter
------------

`Array.filter` creates a new array containing only selected members of the list.
Selection is performed by a function returning `true` for values that should be
retained and `false` for values which should be discarded. For instance,

@SOURCE(
    def a := --SKIP
    [1, 17, -8, 14, -32].filter(x => x > 0)
)

filters the list according to the function `x => x > 0`, which is `true` if the
number is positive. The result is thus `[1, 17, 14]`.

Array.apply
-----------

`Array.apply` calls a method on each element of the array. For instance,

@SOURCE(
    def stringArray := new Array<String>() 
    --BEGIN
    stringArray.apply(Console::writeLine(String))
)

will call `Console.writeLine()` once for each string in the array, and is thus
equivalent to:

@SOURCE(
    def stringArray := new Array<String>() 
    --BEGIN
    for string in stringArray
        Console.writeLine(string)
)

Immutable Arrays
----------------

The type `panda.collections.ImmutableArray` is an [immutable](immutable.html) 
version of `Array`. `ImmutableArray` is equivalent to `Array`, but immutable 
arrays may only hold immutable types and they may not be altered after creation.

### Converting Mutability

If you have a mutable array and need an immutable array, or vice-versa, you can
simply convert from one type to the other:

@SOURCE(
    var a:Array<Int> := [1, 2, 3]
    var b:ImmutableArray<Int> := a->>(ImmutableArray<Int>)
)

The [array subrange](#subrange) constructor in both both mutable and immutable 
arrays accepts either kind of array, and can therefore perform a similar
conversion

### Array Literals

[Array literals](#literals) may be mutable or immutable, depending upon the 
context. For example, in the code:

@SOURCE(
    method process(a:ImmutableArray<String>) {
        -*REPLACE:...*---dummy comment
    }

    process(["Some", "Strings"])
)

the type of the array in the call to `process()` is inferred to be 
`ImmutableArray<String>`. Arrays created using the simple array syntax are 
assumed to be mutable unless the context implies otherwise.
