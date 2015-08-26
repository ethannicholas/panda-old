Expressions
===========

An *expression* is, in simple terms, "something which has a value". Numbers and
strings are expressions. Numbers plus numbers are expressions, and so are
function calls. More formally, expressions can be:

A single term, such as:

* A number
* A string literal
* A `Bit` literal
* [null](null.html)
* [self](self.html)
* A variable reference
* A [method](methods.html) or [function](functions.html) call
* An [object instantiation](new.html)
* An [array literal](arrays.html#simple)
* An [inline method](inlineMethods.html)
* A [method reference](method references.html)

Or a compound expression, such as:

* (`<expression>`) (parenthesized expressions)
* `<expression>` `<binaryOperator>` `<expression>` (arithmetic, logic, etc.)
* `<unaryOperator> <expression>` (unary minus, logical not, bitwise not)
* `<expression>.<field>` (field access)
* `<expression>[<expression>]` (array index)
* `<expression>[<range>]` (slice)

<a name="precedence"></a>
Precedence
----------

In standard mathematics, the expression "1 + 6 * 7" evaluates to 43: you are
supposed to perform the multiplication first, and then the addition. This is
formalized in the notion of *operator precedence*; that is, certain 
[operators](operators.html) (such as multiplication) have a higher priority than 
other operators (such as addition).

Panda's operator precedence, from highest to lowest, is:

1. `.`, `->`, `->>`, `-?>`, `-!>`, `()`, `[]`
2. `^`
3. `-` (unary), `!`, `!!`
4. `*`, `/`, `//`, `%`, `<<`, `>>`, `&&`, `~~`
5. `+`, `-` (binary), `||`
6. `..`, `...`
7. `=`, `!=`, `==`, `!==`, `>`, `<`, `>=`, `<=`
8. `&`, `~`,
9. `|`