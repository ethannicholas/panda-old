Operators
=========

An *operator* is a special symbol that performs an operation on one or two
*operands* and produces a *result*. For instance, in the expression `7 + 3`
the operator is `+` (addition), the two operands are `7` and `3`, and the result
is `10`. Panda operators come in several categories:

<a name="arithmetic"></a>
Arithmetic
----------

* `+` (add): `2 + 3` is `5`
* `-` (subtract): `5 - 3` is `2`
* `*` (multiply): `4 * 3` is `12`
* `/` (divide): `9 / 2` is `4.5`
* `//` (integer divide): `9 // 2` is `4`
* `%` (remainder): `9 % 2` is `1`
* `^` (exponent): `8 ^ 3` is `512`

Panda's arithmetic operators operate on [numbers](basicTypes.html#numbers), and 
always produce at least an `Int32` value, even if the [types](types.html) you 
are operating on are smaller than that. If either of the two operands is `Real`, 
the result is `Real`. If either of the two operands is 64 bits long, the result 
is 64 bits long. Thus `Int8 * Int16 = Int32`, `Int64 * Real32 = Real64`, and 
`Real32 * Int32 = Real32`.

Note that Panda's division operator always produces a `Real` result, even if you 
are dividing two integers. If you want to perform an integer division, you must 
use the integer divide (`//`) operator.

<a name="range"></a>
Range
-----

* `..` (exclusive range): `0 .. 4` is `[0, 1, 2, 3]`
* `...` (inclusive range): `0 ... 4` is `[0, 1, 2, 3, 4]`

The range operators generate a list of numbers given a start, end, and optional
step value. The full syntax is:

    <start> ..|... <end> [by <step>]

For example, `Console.writeLine(0 ... 10 by 2)` displays `[0, 2, 4, 6, 8, 10]`.
The only difference between the two range operators is that the inclusive range 
operator (`...`) includes the end value, and the exclusive range operator (`..`)
excludes the end value. The range operators are particularly useful when paired
with the [`for` loop](statements.html#for), as they give you a means of 
iterating over an arbitrary range of numbers.

Note that the range operators count upwards by default, so `10 ... 0` yields an
empty list because the start is greater than the end. Use a negative step value
to count backwards, as in `10 ... 0 by -1`.

<a name="shift"></a>
Shift
-----

* `<<` (shift left): `5 << 2` is `20`
* `>>` (arithmetic shift right): `-20 >> 2` is `-5`
* `>>>` (logical shift right): `-20 >>> 2` is `0b00111111111111111111111111111011`

The *shift left* operator shifts the bits in a [number](basicTypes.html#numbers) 
to the left, inserting zero bits on the right. Left shifting by `n` bits is 
equivalent to multiplying by `2^n` with no overflow checking.

The right shift operators shift the bits in a number to the right, differing in
how the sign bit is handled. The *arithmetic shift right* operator extends the
sign bit, so that a negative number remains negative after being shifted. The 
*logical shift right* operator shifts in zeroes, so negative numbers will become 
positive after being shifted one or more bits. Both arithmetic and logical shift 
right will behave identically for positive numbers.

<a name="comparison"></a>
Comparison
----------

* `=` (equal): `12 = 12` is `true`
* `!=` (not equal): `12 != 12` is `false`
* `>` (greater than): `5 > 5` is `false`
* `>=` (greater than or equal): `5 >= 5` is `true`
* `<` (less than): `-12 < 2` is `true`
* `<=` (less than or equal): `2 <= -12` is `false`

The comparison operators all follow standard arithmetic rules and produce a 
`Bit` result, either true or false. The `=` operator checks for *equality* 
rather than *identity*; in other words `string1 = string2` checks whether the 
two strings have the same value (the same sequence of characters), not whether 
they are actually the same string object.

<a name="identity"></a>
Identity
--------

* `==` (identity): `new MutableString() == new MutableString()` is `false`
* `!==` (not identity): `new MutableString() == new MutableString()` is `true`
* `-?>` (instance of): `"hello"-?>(String)` is `true`
* `-!>` (not instance of): `"hello"-!>(Int)` is `true`

The *identity* operator checks whether two objects are in fact the same object.
The `new MutableString() == new MutableString()` returns `false` because two
distinct `MutableString` objects are being created. They are `equal`, because
they contain the same (zero-length) sequence of characters, but they are not
`identical`, because they are two distinct objects. Identity is a seldom-used
operation; you will very likely almost always want to compare objects for 
equality rather than for identity.

The identity / not identity operators are not allowed to operate on 
[value](value.html) objects. The identity of vale objects is not guaranteed; the 
compiler may choose to fold equal instances into a single instance, and 
depending on the identity of value objects is therefore always dangerous. 
Furthermore, the compiler is permitted to compile value objects in such a way
that they do not even *have* an identity, rendering an expression like `5 == 5` 
meaningless.

The *instance of* and *not instance of* operators check to see whether an object
(or `null`) is a member of a given type. The value `"hello"` is indeed an 
instance of the class `String`, so the expression `"hello"-?>(String)` evaluates 
to `true`. The type name being checked must be surrounded by parentheses. `null`
is considered to be a member of every nullable type and not a member of any
non-nullable type.

<a name="logic"></a>
Logic
-----

* `&` (logical and): `true & false` is `false`
* `|` (logical or): `(1 > 2) | (6 < 7)` is `true`
* `~` (logical exclusive or): `true ~ true` is `false`
* `!` (logical not): `!true` is `false`

The logical operators implement the standard boolean logic functions. All four
logical operators require [`Bit`](basicTypes.html#Bit) operands and produce a 
`Bit` value.

### Short-Circuiting

The *logical and* and *logical or* operators are `short-circuiting`: that is, 
they do not evaluate the right-hand operand unless they need to. If the 
left-hand operand of a logical and is `false`, then the result of the logical 
and is `false` no matter what the right-hand operand evaluates to, and the so 
the right-hand operand is not evaluated. Likewise, if the left-hand operand of a 
logical or is `true`, then the result of the logical or is `true` no matter what 
the right-hand operand evaluates to, and so the right-hand operand is not 
evaluated.

<a name="bitwise"></a>
Bitwise
-------

* `&&` (bitwise and): `0b101 && 0b110` is `0b100`
* `||` (bitwise or): `0b101 || 0b110` is `0b111`
* `~~` (bitwise exclusive or): `0b101 ~~ 0b110` is `0b011`
* `!!` (bitwise not): `!!0` is `-1`

The bitwise operators implement the standard boolean logic functions bit-by-bit
on two integers. Unlike the logical operators, the bitwise operators always
evaluate both of their operands.

<a name="cast"></a>
Cast
----

* `->` (cast): `object->(String)` casts `object` to a `String`

The cast operator tells the compiler to treat an object as being a different
[type](types.html). For instance, in

    var x:Object := "Hello"
    processString(x)

assuming `processString` is declared to take a single parameter of type 
`String`, this code will produce the message `no match found for method 
processString(panda.core.Object)`. As far as the compiler is concerned, the
variable `x` has type `Object`, and so one cannot call the method 
`processString` on it.

Since the value `x` holds is actually a `String`, we can inform the compiler of
this via the *cast* operator:

    processString(x->(String))

This statement *casts* `x` to the type `String` (note that the parentheses 
around the type name are required). Casting doesn't actually change the value; 
it just instructs the compiler to assume that it is a different type. For 
safety, these casts are normally verified at runtime, but it is possible to
disable safety checks during compilation.

Note that Panda's behavior towards casting numbers differs from most other
programming languages. For instance, in C you can cast the number `3716` to an
8-bit value as follows:

    printf("%d\n", (int8_t) 3716);

Result: `-124`

This result happens due to *integer overflow*: the value `3716` is too big to
fit into a value of type `int8_t`, and so C happily truncates the value and 
gives you whatever bits are left over.

The Panda equivalent:

    Console.writeLine(3716->(Int8))

results in an error because `3716` will not fit into an `Int8`. To perform a
truncating numeric conversion in Panda, you need to use the *convert* operator.

**IMPLEMENTATION NOTE**: numeric casts aren't actually range checked yet, but 
it's coming. Right this second a numeric cast and a numeric conversion are
handled the same.

<a name="convert"></a>
Convert
-------

* `->>` (convert): `781->>(String)` is `"781"`

The *convert* operator coerces a value from one [type](types.html) into another. 
For instance, converting a number into a `String` produces a string 
representation of the number. Note that the parentheses around the type name are
required.

For numeric types converting to numeric types, the convert operator is 
implemented by the compiler and performs the same conversions as casting does in 
C, so `3716->>(Int8)` yields `-124` just as does the equivalent C code `(int8_t) 
3716`. For all other conversions, the convert operator is implemented via
[operator overloading](operatorOverloading.html).

All objects have a "convert to `String`" operator, and many classes provide
other useful conversions (for instance, you may convert a `String` to an
`Array<Char>` or to an `Int`).

<a name="index"></a>
Index
-----

* `[]` (index): `a[12]`
* `[]:=` (indexed assignment): `a[12] := 3`

The *index* operator is used to reference elements in [arrays](arrays.html),
while the *indexed assignment* operator modifies array elements. As with other
operators, these operators may be [overloaded](operatorOverloading.html) to
allow user-defined objects to be indexed. For example, `HashMap` overloads the 
`[]` and `[]:=` operators so that it can be indexed in the same fashion as an 
array.

<a name="slice"></a>
Slice
-----

* '[..]' (slice): `a[4..13]`, `a[0.. by 3]`
* `[..]:=` (slice assignment): `a[4 .. 13] := [1, 2, 3]`, `a[.. by 2] := values`

The *slice* operator returns a subrange of a list. Slice takes two indices, both
of which are optional, and returns the subrange from the first index (inclusive)
to the second index (exclusive). By default, every value between the start index 
(inclusive) and end index (exclusive) is included in the resulting list. An 
optional *step* value may be introduced with the `by` keyword, which causes 
elements to be skipped over; for instance `by 2` takes every other element and 
`by 3` takes every third element.

If the first index is omitted, it is treated as `0` (if the step is positive) or 
the list's length minus 1 (if the step is negative). If the second index is 
omitted, it is treated as the list's `length` (if the step is positive) or -1
(if the step is negative). Thus `[.. by -1]` will return a reversed copy of the
list.

Given `var a := [0, 1, 2, 3, 4]`,

* `a[1 .. 3]` is `[1, 2]`
* `a[..3]` is `[0, 1, 2]`
* `a[2..]` is `[2, 3, 4]`
* `a[..]` is `[0, 1, 2, 3, 4]`
* `a[.. by -1]` is `[4, 3, 2, 1, 0]`
* `a[.. by 2]` is `[0, 2, 4]`
* `a[3 .. 1 by -1] is `[3, 2]`

All of these results are distinct copies of the list data; `a[..]` is rougly
equivalent to `a.copy`.

Slice assignment replaces the sliced elements of the list with new data, such 
that

    a[2..] := [6, 7]

yields the array `[0, 1, 6, 7]`. If you specify a step value (`by <expression>`)
on a slice assignment, the number of elements selected by the slice must be the
same as the number of elements you are assigning to the slice. For instance,

    var a := [0 .. 10 by 1]->>(Array<Int>)
    a[.. by 2] := [20 .. 25]
    Console.writeLine(a)

yields
  
    [20, 1, 21, 3, 22, 5, 23, 7, 24, 9]

The slice and slice assignment operators are defined on 
[`List`](api/panda.collections.List.html) (and therefore also 
[`Array`](arrays.html)) by default. `String` also provides an implementation of
slice for extracting substrings, and `MutableString` provides both slice and 
sliced assignment. 

The various `Int` types provide class-level slice operators which allow you to 
create ranges of numbers or characters. For instance, `Int[0..200]` returns a 
list of the integers `0` to `199`, and `Int[0..]` returns a list from `0` to 
`Int.MAX`.

You may provide implementations on your own classes via 
[operator overloading](operatorOverloading.html). To avoid confusion, be 
sure to follow the same semantics described above.

Operator Precedence
-------------------

See [expressions](expressions.html#precedence) for a description of operator
precedence.