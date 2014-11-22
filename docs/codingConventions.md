Coding Conventions
==================

These are the conventions used in the Panda codebase itself; anyone wishing to
contribute code to Panda should read and follow these conventions. 

Identifiers
-----------

Clear, descriptive names enhance readability, and Panda strives to maximize 
readability rather than minimize the number of characters typed. Class, method, 
and public variable names are the most visible entities in a Panda program, and 
therefore the most critical to name well. All should have names that clearly 
express their intent and function. If you find yourself naming variables `var1`
and methods `performFunction()`, you should probably spend a bit more effort on
naming.

Class names must always begin with an uppercase letter, with the first letter of
each subsequent word capitalized (`UpperCamelCase`). Method and variable names 
must always begin with a lowercase letter, and likewise have the first letter of
each subsequent word capitalized (`lowerCamelCase`). Constants, including 
enumeration entries, are named in all caps with underscores between words 
(`THIS_IS_A_CONSTANT`). Abbreviations are generally to be avoided, but may be 
acceptable where there is a well-accepted historical precedent (e.g. `sqrt`, 
`cos`). Acronyms such as URL and HTTP appearing within identifiers should be 
rendered as either all-uppercase or all-lowercase. Use lowercase acronyms at the
beginning of variable and method names (`urlString`), uppercase acronyms 
otherwise (`parseXMLDocument()`).

For local variables, short or even single character names may be acceptable if 
the variable's purpose is clear and a longer name would not express its intent 
any better. For instance, in a function `x => x.sqrt` it is reasonable to 
name the parameter `x` because its intent is obvious and 
`theNumberToTakeTheSquareRootOf` (or some other contrived descriptive name) 
would be less, rather than more, readable. `for` loop index variables which are 
not better served by a less generic name should be named `i`, `j`, etc.

Names should never include or reference their type, unless that is what is 
significant about them. For instance, the following code is acceptable:

@SOURCE(
    function getAttribute(s:String):String {
        return "foo"
    }
    function parseHeight(s:String):Int {
        return 42
    }
    --BEGIN
    def heightString := getAttribute("height")
    def height := parseHeight(heightString)
)

In this case, we need to distinguish the raw, unprocessed string form of the 
height from its processed numeric version, so calling this out as heightString 
makes sense. It would not be acceptable to name the height variable 
`heightInt32`; it is presumably the fact that it is a height that makes this 
variable significant, not the fact that it is an `Int32`. Likewise, do not use a
prefix such as an 'm' or underscore to distinguish member variables: Hungarian 
notation has no place in Panda.

Indentation and Spacing
-----------------------

Blocks are indented using four spaces. Tab characters should not be used. If a 
single statement is split across multiple lines, the second and subsequent lines
are to be indented by eight spaces.

Numeric and logical operators should have one space on either side, so you would
write `(x + y) * 3` rather than `(x+y)*3`. The index, dot, cast, and convert 
operators should not use spaces (e.g. `Console.writeln(array[5] + 
"12345"->>(Int)`)). The dot-dot (`..`) in the slice operator should be 
surrounded by spaces if both indices are specified (`[1 .. 5]`) and not 
otherwise (`[1..]`).

Never put more than one statement on a single line.

Classes and methods are separated by a blank line.

When breaking a line in the middle of an expression, the operator goes at the 
end of the line:

@SOURCE(
    class Example {
    var value:Example
    --BEGIN
    @override
    function =(o:Object):Bit {
        return o-?>(Example) & value = o->(Example).value |
                o-?>(String) & value->>(String) = o
    }
    --END
    }
)

Width
-----

Panda's source files use an 80 character line length.

Braces
------

Braces attached to an `if`, `for`, `while`, or `do` statement appear on the same
line as the statement itself, separated by a single space, and the closing brace
is even with the opening statement, e.g.:

@SOURCE(
    def codeIsWellFormatted := true
    --BEGIN
    if codeIsWellFormatted {
        -*REPLACE:...*---dummy comment
    }
)

Optional braces (those enclosing only a single statement) should be included 
when that statement spans multiple lines, and omitted otherwise. "Spans multiple 
lines" includes child statements:  a `for` loop always spans multiple lines due 
to its child statements, even though the `for` itself fits on a single line.

If optional braces are omitted, the statement in question still goes on the next
line, indented. That is, you should write:

@SOURCE(
    def x := 0
    method doSomething() { }
    --BEGIN
    if x > 0
        doSomething()
)

instead of

@SOURCE(
    def x := 0
    method doSomething() { }
    --BEGIN
    if x > 0 doSomething()
)

There should be no other code on the same line as a closing brace. This means 
that if-then-elses should be written as:

@SOURCE(
    def test := true
    --BEGIN
    if test {
        -*REPLACE:...*---dummy comment
    }
    else {
        -*REPLACE:...*---dummy comment
    }
)

and do-while loops as:

@SOURCE(
    def condition := false
    --BEGIN
    do {
        -*REPLACE:...*---dummy comment
    }
    while condition
)

Literals
--------

While Panda allows both "double quoted" and 'single quoted' strings, you should
generally use double quotes. You may use single-quoted strings when necessary to 
avoid having to escape embedded double quotes, for instance in the string `'"'`.

"Magic" numbers and strings should generally be defined as constants, but don't
get carried away. For instance, in

@SOURCE(
    function isEven(x:Int):Bit {
        return x % 2 = 0
    }
)

the magic number `2` is perfectly acceptable because no one reading the code is
going to be confused about what it means or where it came from.

Parentheses
-----------

`assert` and `return` are statements, not methods. Write `assert x > 0` rather 
than `assert(x > 0)`. Likewise, the tests in `if`, `while`, and `do` statements 
do not require parentheses around them as C-derived languages do; these 
superfluous parentheses should be omitted.

It is acceptable (or even preferred) to use unnecessary parentheses to clarify 
order of operations even when operator precedence would have done the same job 
as the parentheses, but extra parentheses should never be placed around an 
entire expression (such as in the aforementioned `assert` example, or in 
`clamp(x, min, (min + 3)))`.

Do not use parentheses for functions which take no arguments. Write 
`"hello".length` rather than `"hello".length()`.  This is especially important 
so your code will continue to compile in the future if length ever becomes a var
instead of a function.

Loops
-----

Unlike most languages, Panda has a built-in infinite loop construct (`loop 
{ ... }`). Use it instead of `while true { ... }` or similar constructs.

Users of other languages may have developed the habit of running loops in 
reverse where possible in the interest of greater efficiency (from, say, 
`length() - 1` down to `0`, so that `length() - 1` is only computed once). This 
is unnecessary in Panda, as loop bounds are only evaluated once and forward and 
backward loops are therefore equally fast. Use forward loops where possible.

Comparison
----------

In comparisons, constants should be on the right. `x > 5` and `string != null`
are much easier to read than `5 < x` and `null != string`.

Types
-----

Optional type declarations should generally be omitted, unless readability 
suffers as a result.

Spaces should not appear between a type name and its modifier symbols, thus a
nullable array of nullable ints should be written `Array<Int?>?`.

Immutability
------------

Panda permits mutability, and of course you may take advantage of it where it
makes sense to do so. 

With that said, immutability is generally strongly preferred to mutability. 
The vast majority of your "variables" should be `def`s, with `var`s relatively
rare and only where they lead to more straightforward code. Most of the classes
you create should extend `Immutable`, only using mutable classes where it 
significantly simplifies the code (and keep in mind that even code which looks
simpler *at first* can be a maintenance nightmare over time). Feel free to make
use of mutable objects as temporary values within methods, but most of your 
public interface should revolve around immutable values.

Functions are strongly preferred to methods, and should be used where possible.
Appropriate use of `@self`, `@limited`, and `@safeReturn` annotations will make
use of functions dramatically easier.

Uses
----

"Use" only single classes, not entire packages. List used classes in 
alphabetical order.

Comments
--------

Code must thoroughly commented. Comments should describe things that are not 
immediately obvious from looking at the code, e.g. in the below code

@SOURCE(
    def x:Int
    --BEGIN
    -- set x to 0
    x := 0
)

the comment is useless, because it does not tell us anything that is not 
immediately apparent from looking at the code. We might instead want to know 
*why* x is being set to zero at this point, and what this represents or
accomplishes. Keep in mind that "obvious" to the author of the code is not 
obvious to others.

Comments used to break code up into sections should have another pair of minus 
signs (--) at the end of the comment, with a single blank line between sections, 
as follows:

@SOURCE(
    -- Parse the document --
    -*REPLACE:...*---dummy comment

    -- Transform the parsed document --
    -*REPLACE:...*---dummy comment

    -- Output the transformed document --
    -*REPLACE:...*---dummy comment
    --END
    class dummy {
    }
)

Documentation Comments
----------------------

Documentation comments are opened and closed by a complete line of equals signs
extending out to column 80. The opening and closing marks should begin in the 
same column as the method, class, or variable being described, and every line of
the comment should also begin in this column. A single blank line should 
separate the body of the documentation comment from the subsequent `@` tokens 
describing its parameters, return value, and so forth. 

All parameters, return value, and possible exceptions must be described. If a 
parameter or return value is nullable, you must specify what meaning a `null` 
has if it is not obvious. If a parameter is `Real,` you must specify how 
infinities and `NaN` are handled (as well as positive / negative zero, if this
is not obvious).

Example:

@SOURCE(
    ============================================================================
    Returns the greater (closest to positive infinity) of its two parameters. 
    Returns `NaN` If either `a` or `b` is `NaN`.
        
    @param a a number
    @param b a number
    @returns the greater of the two parameters
    ============================================================================
    function max(a:Int32, b:Int32):Int32 {
        if a > b
            return a
        else
            return b
    }
)

Every public class or class member must have a complete documentation comment, 
covering all of its parameters, return, possible exceptions, and so forth. 
Private classes and members should also have documentation comments, but this is 
not required if their purpose and usage is obvious at a glance.

Contracts
---------

Except where preconditions specify otherwise, methods are assumed to work on 
every possible value of their parameters. You must always consider all possible 
inputs to your methods: consider that `Real`s may be infinite or `NaN`, `Int`s 
could be zero, negative, or in the billions, nullable values could be `null`, 
`String`s could be zero length, contain null characters or other non-printable 
characters, and so forth. If your method does not handle these possibilities, 
you should either restrict your input types or add preconditions that will fail 
on unsupported values. 

Anywhere your methods make assumptions about parameters, you should make those 
assumptions explicit:  for instance, if you have parameters named `min` and 
`max`, there's a good chance that your method should have a `@pre(max >= min)` 
to back up the implicit assumption. As preconditions are automatically included 
in the documentation, you need only mention your preconditions in doc comments 
if the precondition expression is not obvious. 

Generally speaking you should not be in the habit of describing restrictions on 
possible values ("size cannot be negative") in your documentation, because these
documented restrictions are easily missed and are not enforceable. Instead 
enforce your restrictions at the code level, by choosing appropriate types and 
adding appropriate preconditions, and the restrictions will be both enforced and
documented automatically.

Annotations
-----------

Annotations appear in the same column as the entity they are describing, on
preceding lines (except for `@post` / `@postAnd`, which appear on following
lines). Use only one annotation per line, as in:

@SOURCE(
    class Widget {
    var isReady := true
    var isFurculated := true
    --BEGIN
    ============================================================================
    Frobnozzles a widget until it is furculated.
    ============================================================================
    @private
    @class
    @pre(w.isReady)
    method frobnozzle(w:Widget) {
        -*REPLACE:...*---dummy comment
    }
    @post(w.isFurculated)
    }
)

Annotations should always be listed in a consistent order:

1. `@private` / `@protected` 
2. `@class`
3. `@final`
4. `@override`
5. `@math(...)`
6. `@pre` / `@preOr`

Operator Overloading
--------------------

With great power comes great responsibility. Operator overloading is easily 
abused in languages which support it, and therefore requires a bit of caution to
handle responsibly.

Every Panda operator has a name. For instance, `+` is "add", and `||` is 
"bitwise or". If you redefine an operator to do something other than its name 
indicates, you have committed a mistake equivalent to defining an `add()` method
that does something other than adding. The designers of C++ redefined the 
bitwise shift operators to also function as stream insertion and extraction 
operators, in one stroke both bastardizing these operators and sending a message
to budding C++ programmers that this redefinition was both acceptable and 
expected.

In Panda, this is neither acceptable nor expected. You should always be able to
read an expression such as `a + b` in English as "add b to a" and have it make 
sense even with overloaded operators. For instance, `String` redefines the add 
operator to do something very different (concatenation), but it still makes 
sense when read in English: when told to add the string "World!" to the string 
"Hello ", one is probably not surprised to learn that the answer is "Hello 
World!".

The overridable operators and their names are:

* `+`    (add)
* `-`    (subtract)
* `*`    (multiply)
* `/`    (divide)
* `//`   (integer divide)
* `%`    (remainder)
* `^`    (exponent)
* `<<`   (shift left)
* `>>`   (shift right)
* `=`    (equals)
* `>`    (greater than)
* `>=`   (greater than or equal)
* `<`    (less than)
* `<=`   (less than or equal)
* `&`    (and)
* `|`    (or)
* `~`    (exclusive or)
* `!`    (not)
* `&&`   (bitwise and)
* `||`   (bitwise or)
* `~~`   (bitwise exclusive or)
* `!!`   (bitwise not)
* `[]`   (index)
* `[]:=` (indexed assignment)
* `->>`  (convert)

To make this even more explicit, PandaDoc includes these names in its output, to
hopefully make it clear that it is not acceptable to simply redefine the 
operators to do different things.

SafetyError
-----------

`SafetyError` and its subclasses, as mentioned above, are a sign that your
program is broken. Writing code equivalent to the following:

@SOURCE(
    def list:Array<Object> := []
    method processEntry(o:Object) { }
    --BEGIN
    try {
        var i := 0
        loop {
            processEntry(list[i])
            i += 1
        }
    }
    catch e:IndexOutOfBoundsError {
        -- reached the end of the array
    }
)

will get you soundly flogged. Not only are exceptions incredibly expensive
compared to a simple loop, but `SafetyError` is explicitly not guaranteed: your 
code might have been compiled with array bounds checking disabled, for example.

In a future version of the Panda compiler, guaranteed safety violations (such as
the above example) will generate a compile-time error.

Java Code
---------

The Java code included in Panda presents special challenges because of the sheer
number of duplicate class names (panda.core.Object vs. java.lang.Object,
panda.core.String vs. java.lang.String, etc.), many of which are on important 
and commonly-used classes. Therefore, in the Java code I have to hold to the
somewhat painful requirement that all class names, Panda and Java alike, must be
fully qualified to eliminate ambiguity. This means no imports, and even classes
in java.lang must be fully qualified.

Because the resulting extremely verbose code makes sticking to an 80 character
line length much more difficult, I am more tolerant of long lines in the Java
code.

