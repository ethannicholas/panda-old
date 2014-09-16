Basic Types
===========

All [types](types.html) in Panda are subclasses of 
[`panda.core.Object`](objects.html), but some basic types are so integral to 
programming that they enjoy special treatment within the compiler. All of these
types are in the [package](packages.html) `panda.core`, so that e.g. the 32-bit
integer type has the fully-qualified name `panda.core.Int32`, but it is almost 
always referred to by the simple name `Int32`.

<a name="numbers"></a>
Numbers
-------

Panda numbers come in three basic flavors, `Int` (signed integer), `UInt`
(unsigned integer), and `Real` (floating point), in several sizes. The following
number types are supported:

* `Int8` - 8 bit signed integer, range -128 to 127
* `Int16` - 16 bit signed integer, range -32,768 to 32,767
* `Int32` - 32 bit signed integer, range -2,147,483,648 to 2,147,483,647
* `Int64` - 64 bit signed integer, range -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
* `UInt8` - 8 bit unsigned integer, range 0 to 255
* `UInt16` - 16 bit unsigned integer, range 0 to 65,535
* `UInt32` - 32 bit unsigned integer, range 0 to 4,294,967,296
* `UInt64` - 64 bit unsigned integer, range 0 to 18,446,744,073,709,551,615
* `Real32` - 32 bit floating point number, range -3.4 x 10^38 to 3.4 x 10^38
* `Real64` - 64 bit floating point number, range -1.7 x 10^308 to 1.7 x 10^308
* `Int` - alias of `Int32`
* `UInt` - alias of `UInt32`
* `Real` - alias of `Real64`

Numbers may be represented in programs using any of the following:

* Integers, e.g. `7361` or `-65`
* Reals, e.g. `12.5` or `.3451`
* Exponential notation, e.g. `1.2e10` (1.2 x 10^10) or `0.1e-5` (0.1 x 10^-5)
* Hexadecimal with a leading `0x`, e.g. `0x1B6A`
* Binary with a leading `0b`, e.g. `0b1110001`

<a name="Bit"></a>
Bit
---

`Bit` is Panda's boolean logic type. `Bit` has exactly two possible values, 
`true` or `false`, represented by the literal words `true` and `false` in a 
program. Bit values are generally produced by the 
[logical operators](operators.html#logic), and are often used in
[control statements](statements.html) such as [`if`](statements.html#if),
[`while`](statements.html#while), and [`do`](statements.html#do).

<a name="Char"></a>
Char
----

Panda's character type is internally represented as an unsigned 16 bit number,
but the compiler does not consider `Char` to be a number. This means that you
cannot perform math directly on a character; you must first 
[cast](operators.html#cast) the character to an integer type.

Panda does not have a dedicated `Char` literal syntax. Any single-character
string literal, such as `"Q"`, may be used in a context where a `Char` is
expected. If the type is ambiguous, for instance `foo("A")` when both 
`foo(x:String)` and `foo(x:Char)` exist, `Char` is preferred to `String`. If 
this is not the desired behavior, you may force the literal to be interpreted as
a `String` by casting it, e.g. `"A"->(String)`.

<a name="String"></a>
String
------

Panda strings may be either single- or double-quoted. Within a string, the
following escape sequences are recognized:

* `\n` - a newline (code point 10)
* `\r` - a carriage return (code point 13)
* `\t` - a tab (code point 9)
* `\'` - a literal single quote
* `\"` - a literal double quote
* `\\` - a literal backslash
* `\{...}` - a [*string interpolation*](stringInterpolation.html) expression

Note that a single-character string literal, such as `"A"`, could be interpreted
as a `Char` literal depending upon the context. If this is not the desired 
behavior, you may force the literal to be interpreted as a `String` by casting
it, e.g. `"A"->(String)`.