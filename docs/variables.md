Variables
=========

Declaration
-----------

A Panda variable is introduced with the statement:

`var <name>[:<type>][:= <value>]`

Thus, you could create a variable `x` of type `Int` with the value `12` as
follows:

`var x:Int := 12`

Panda can *infer* the type of the variable by looking at the variable's initial
value. Since `12` is obviously an integer, you can simply write:

`var x := 12`

and Panda will infer that `x` is an integer without specifically being told so. 
Type inference will never make `Int` variables smaller than 32 bits, so in 
the case of `var x := 12`, `x` will be assigned the type `Int32` despite the 
fact that `12` will fit into an `Int8`.

You may also declare just the variable's type and omit the value:

`var x:Int`

This creates an uninitialized variable.

Variables may be named any valid [identifier](identifiers.html).

Referencing
-----------

You use, or reference, the value of a variable simply by writing its name. For
instance,

    var x := 12
    Console.writeLine("The value of x is: " + x)

Result: `The value of x is: 12`.

Referencing an uninitialized local variable is a compile-time error; you must
give local variables a value before referencing them.

    var x:Int
    Console.writeLine("The value of x is: " + x)

Result: `Test.panda:2:43: variable 'x' may not have been assigned`

Scope
-----

Variables are visible only within the block or class in which they are declared.
Panda does not have global variables; the highest scope in Panda is the class. 
It is not legal to redefine a local variable from a scope in which it is 
visible.

Assigning
---------

To change the value of a variable, use the *assignment operator* (`:=`):

    var x := 10
    Console.write("x started out as " + x)
    x := 20
    Console.writeLine(", but ended up as " + x)

Result: `x started out as 10, but ended up as 20`

It is legal to use the variable's old value in order to compute its new value.
For instance, `x := x + 1` sets `x` to its old value plus one, or in other words
it increments `x` by one.

Statements like `x := x + 1` are so common that Panda supports a shorthand
notation called *compound assignment operators*. This allows you to merge the
addition (`+`) operator and the assignment (`:=`) operator together to form
the compound `assignment-with-add` operator (`+=`). The statement 
`x := x + 1` can be rewritten as `x += 1`, and means the exact same thing: take
the value of `x`, add one to it, and store this new number into `x` (or more
concisely, "add one to `x`").

There is a corresponding compound operator for each arithmetic, logical, and
bitwise operator. The full set of Panda assignment operators is:

* `:=` (assignment)
* `+=` (assignment-with-add)
* `-=` (assignment-with-subtract)
* `*=` (assignment-with-multiply)
* `/=` (assignment-with-divide)
* `//=` (assignment-with-integer-divide)
* `%=` (assignment-with-remainder)
* `^=` (assignment-with-exponent)
* `<<=` (assignment-with-shift-left)
* `>>=` (assignment-with-arithmetic-shift-right)
* `>>>=` (assignment-with-logical-shift-right)
* `&=` (assignment-with-logical-and)
* `|=` (assignment-with-logical-or)
* `~=` (assignment-with-logical-xor)
* `&&=` (assignment-with-bitwise-and)
* `||=` (assignment-with-bitwise-or)
* `~~=` (assignment-with-bitwise-xor)

Note that assignments are statements, not expressions. While it is legal in C to
use assignments as expressions such as:

    printf("%d\n", x += 5)

the Panda equivalent is not legal:

    Console.writeLine(x += 5) -- won't compile, x += 5 is not an expression

Scope
-----

Variables may have one of three *scopes*:

* Block - a variable declared inside of a block of code is visible only within
  that block, and only after its declaration
* Instance - variables declared inside of a class are instance-scoped by 
  default; these variables are also known as [*fields*](fields.html). Each
  individual instance of an object class contains its own copies of 
  instance-scoped variables.
* Thread - variables declared with the 
  [`@thread` annotation](annotations.html#thread) are thread-scoped. These
  variables are visible from anywhere (using the form `ClassName.fieldName`), 
  but each thread "sees" an independent copy of the variable.

There is no higher scope; there are no class-level or global variables in Panda.
Eliminating global mutable state eliminates a whole host of problems that come
with it when writing multithreaded software.