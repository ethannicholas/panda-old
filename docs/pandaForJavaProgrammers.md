Panda for Java Programmers
==========================

Panda isn't really closely based on any one existing language, but it probably
has more in common with Java than anything else. If you are already familiar 
with Java, learning Panda is relatively straightforward. This document is not
intended to be an exhaustive description of Panda; rather it is a simple 
overview of the differences between Java and Panda with lots of links to 
additional details.

Basics
------

Panda's [class](classes.html) model is very similar to Java's. Each class (other
than `Object`) has a single superclass and any number of 
[superinterfaces](interfaces.html). Unlike Java, everything in Panda is an 
object: you can call methods on numbers, use them in collections, and otherwise 
treat them as full-fledged objects. 

You access fields and call methods in Panda just like in Java:

    // Java
    System.out.println("Hello, World!");

    -- Panda
    Console.writeLine("Hello, World!")

As you can see above, Panda's line comments begin with two dashes (`--`), and 
Panda doesn't have a statement terminator like Java's semicolons. Block comments
begin with dash-star (`-*`) and end with star-dash (`*-`), and Panda uses curly
braces to group statements just like Java does.

Variables
---------

Conceptually, Panda [variables](variables.html) work the same way as their Java
counterparts, but the syntax to create them is different.

    // Java
    String prompt = "Are you sure?";

    -- Panda
    var prompt := "Are you sure?"

Note that the Panda version doesn't include a type. This doesn't mean Panda is
a dynamically-typed language - it just means that it has *type inference*. In
other words, the compiler is smart enough to look at the other side of the 
assignment operator, see a `String` there, and work out that you probably want 
`prompt` to have type `String`.

You can manually specify the type if you want:

    var prompt:Object := "Are you sure?"

In addition to variables, Panda offers [constants](constants.html) and
[defines](defines.html) which are roughly equivalent to Java's `final` variables 
and fields.

Types
-----

Panda's numeric types are `Int8`, `Int16`, `Int32`, `Int64`, their unsigned
equivalents `UInt8`, `UInt16`, `UInt32`, and `UInt64`, and the floating-point
types `Real32` and `Real64`. `Int` is an alias for `Int32` and `Real` is an
alias for `Real64`. Panda's boolean type is named `Bit`.

Panda's type syntax is richer than Java's. In addition to the equivalents of all
Java types (primitives, class names, interfaces, arrays), Panda adds *tuple* 
types (described below) and [method types](types.html#methodTypes), and supports
both nullable and [non-nullable](nonNullability.html) versions of all of these.

Operators
---------

Panda uses `:=` for assignment instead of Java's `=`. Panda uses `=` as its
equality operator, equivalent to the `.equals()` method in Java. The `==`
(identity) operator is similar between Panda and Java, in that it checks whether
two objects have the same identity, but it cannot be used on 
[values](values.html) in Panda, as they do not have an identity.

The basic mathematical operators are the same, except that Panda's division
operator (`/`) always yields a floating-point result. You must use the integer 
division (`//`) operator to get an integral result.

Panda uses `&`, '|', `~', and `!` for logical and, or, xor, and not 
respectively, and `&&`, `||`, `~~`, and `!!` for bitwise and, or, xor, and not.

There is no `>>>` (logical right shift) operator in Panda, as Panda supports
unsigned numbers. A right shift (`>>`) will perform an arithmetic shift on
signed numbers and a logical shift on unsigned numbers.

Panda also provides the very powerful [range](operators.html#range) (`..` or 
`...`), [slice](operators.html#slice) (`[..]`) and 
[convert](operators.html#convert) (`->>`) operators which have no 
direct counterparts in Java, and Panda's operators may be 
[overloaded](operatorOverloading.html).

Strings
-------

Panda strings are much like Java strings, but there are a few important 
differences. In Java, you use single quotes for `char` literals and double
quotes for `String` literals. In Panda, you may use either single or double
quotes for strings. There is no dedicated syntax for `Char` literals: a 
single-character string literal may be treated as either a `String` or a `Char`, 
depending on context.

Panda strings support *string interpolation*, which allows you to embed 
expressions directly into string literals:

    // Java

    int x = 12;
    int y = 16;
    System.out.println(x + " times " + y + " is " + (x * y));

    // Panda
    def x := 12
    def y := 16
    Console.writeLine("\{x} times \{y} is \{x * y}")

String interpolation also gives you complete control over the formatting of the
expression; see the page on [string interpolation](stringInterpolation.html) for
details.

Control Constructs
------------------
The Panda [control constructs](statements.html) are mostly the same as their 
Java equivalents, but Panda doesn't need parentheses around the conditions:

    // Java
    if (health == 0)
        die();

    -- Panda
    if health = 0
        die()

    // Java
    while (!done)
        process();

    -- Panda
    while !done
        process()

    // Java
    do {
        tryConnect();
    }
    while (!connected);

    -- Panda
    do {
        tryConnect()
    }
    while !connected

Panda's `for` loop, on the other hand, is quite different:

    // Java
    for (int i = 1; i <= 10; i++)
        System.out.println(i);
    for (String s : lines)
        processLine(s);

    -- Panda
    for i in 1 ... 10
        Console.writeLine(i)
    for s in lines
        processLine(s)

The start and end values of a range are only evaluated once, and Panda uses type
inference to work out the type of the loop control variable just as you saw with
the `var` keyword. And just as you saw with the `var` keyword, you can manually
specify the types if you so choose:

    for i:Int in 1 ... 10
        Console.writeLine(i)
    for s:String in lines
        processLine(s)

Unlike Java, Panda's `for` loop also allows you to obtain the current index 
while iterating through a list:

    for lineNumber, line in lines {
        ...
    }

The first value is assigned the (zero-based) index into the list, while the
second value is assigned the current list element.

Panda's `switch` statement is similar to Java's, but each `case` is a single
statement or a block. There is no fall-through, and therefore need to no `break` 
out of a `case`. Each case may list multiple values:

    // Java
    switch (state) {
        case CONNECTED:    // fall through
        case ACTIVE:       handleMessage(m);
                           break;
        case DISCONNECTED: // fall through
        case FAILED:       reportError(m);
    }

    -- Panda
    switch state {
        case CONNECTED, ACTIVE:    handleMessage(m);
        case DISCONNECTED, FAILED: reportError(m);
    }

Panda also offers a built-in indefinite loop construct:

    loop {
        Console.writeLine("Hello!")
    }

`loop { ... }` in Panda is equivalent to `while (true) { ... }` in Java.

Methods and Functions
---------------------

Panda [methods](methods.html) are introduced with the `method` keyword:

    // Java
    public boolean remove(String key) {
        ...
    }

    -- Panda
    method remove(key:String):Bit {
        ...
    }

Panda classes, methods, and fields are public by default. You can use the
`@private`, `@package`, and `@protected` [annotations](annotations.html) to 
reduce their visibility.

In addition to methods, Panda also has [functions](functions.html). Functions
are a special kind of method which are not allowed to have side effects; you
should be in the habit of using functions where possible.

Classes
-------

[Classes](classes.html) are defined very similarly to Java:

    // Java
    public class Example extends Parent {
        void doSomething() {
            System.out.println("I do things!");
        }
    }

    -- Panda
    class Example : Parent {
        method doSomething() {
            Console.writeLine("I do things!")
        }
    }

As mentioned above, Panda classes, methods, and fields are public by default.

Constructors
------------

[Constructors](constructors.html) are introduced with the keyword `constructor`,
and the syntax for invoking other constructors is a bit different:

    // Java
    public class Example extends Parent {
        public Example() {
            this("<no name>");
        }

        public Example(String name) {
            super(name)
        }
    }

    -- Panda
    class Example : Parent {
        constructor() {
            constructor("<no name>")
        }

        constructor(name:String) {
            super.constructor(name)
        }
    }

Other than the minor syntax differences, Panda constructors behave more-or-less 
identically to their Java counterparts.

Arrays
------

[Arrays](arrays.html) in Panda use the [generic](generics.html) class `Array`, 
as in `Array<String>`, or its immutable counterpart `ImmutableArray`. 

(This is just an illustration of syntax; there are better ways to write this 
method in both languages.)

    // Java
    int findMaxLength(String[] strings) {
        int max = 0;
        for (int i = 0; i < strings.length; i++)
            max = Math.max(strings[i].length(), max);
        return max
    }

    -- Panda
    method findMaxLength(strings:Array<String>):Int {
        var max := 0
        for i in 0 .. strings.length
            max := strings[i].length.max(max)
        return max
    }

There is also a simple syntax for creating arrays:

    var a := ["String", "Array"]

This will automatically determine the right kind of array to create. In the
previous example an `Array<String>` would have been created, but the compiler
may choose a different type depending on context:

    var a:ImmutableArray<Object> := ["String", "Array"]

In this case the exact same expression results in an `ImmutableArray<Object>`,
because that is the type expected by the context.

For lists of numbers, you can also use the *range* operator to create an array:

    var evens := 0 ... max by 2

Panda's arrays are closer to `java.util.List` than they are to Java's arrays.
They can change size:

    var a := new Array<Int>()
    a.append(1)
    a.append(2)
    a.append(3)

They provide useful functions like `join`:

    Console.writeLine(a.join(":")) -- displays "1:2:3"

And `fold`:

    constant MIN := 1
    constant MAX := 100
    def total := (MIN ... MAX).fold(Int::+)
    Console.writeLine("Sum of the integers from \{MIN} to \{MAX}: \{total}")

    def numbers := [6, 18, 48, -27, 493, 45]
    Console.writeLine("Biggest number: \{numbers.fold(Int::max(Int))}")
    Console.writeLine("Smallest number: \{numbers.fold(Int::min(Int))}")

And `filter`:

    def strings := ["Aardvark", "Antelope", "Bison", "Cheetah", "Dingo"]
    def startsWithA := strings.filter(s => s.startsWith("A"))

They have the powerful [slice operator](operators.html#slice) which allows you
to extract or replace subranges:

    def a := 1 ... 3
    a[0 ... 0] := [100, 101, 102] -- replace the first element with three numbers
    Console.writeLine(a.join(":")) -- displays "100:101:102:2:3"

Tuples
------

Like an array, a [*tuple*](tuples.html) is an ordered sequence of values. Unlike
an array, a tuple is fixed-size and may contain different types of values. 
`("Hello", 5)` is a two-element tuple containing a `String` and an `Int`, and 
you could describe its type as `(String, Int)`. The individual values of the 
tuple are accessed using array-index syntax, e.g. `tuple[0]`.

Tuples may be dissected using multiple assignment:

    def t := ("Hello", 5)
    def greeting, count := t
    Console.writeLine(greeting * count)

This displays `"HelloHelloHelloHelloHello".

Tuples may be broken apart in `for` loops by specifying a parenthesized list of
variable names:

    def numbers := [("One", 1), ("Two", 2), ("Three", 3)]
    for (name, value) in numbers {
        ...
    }

This sort of loop simplifies various common operations:

    // Java
    for (Map.Entry<String, Object> e : map.entries()) {
        String key = e.getKey();
        Object value = e.getValue()
        ...
    }

    -- Panda
    for (key, value) in map.entries {
        ...
    }

First-Class Regular Expressions
-------------------------------

Regular expressions may be embedded in Panda code using the syntax

    #/<regex>/#

For instance, `#/ab*/#` is a regular expression which matches an `a` followed by
any number of `b`'s. The value `#/ab*/#` is an object of type 
`RegularExpression` which can be interacted with directly or passed to various
`String` functions which use regular expressions. Working with regular 
expressions is generally more straightforward than in Java. For instance, to
extract the numbers from the string `"You are at 16, 24"` we could write:

    var numbers := "You are at 16, 24".parse(#/\D*(\d+),\s*(\d+)/#)

That regular expression may look intimidating, but it's quite simple if you 
break it down:

1. `\D*` - match any number of non-digit characters (to skip the text at the 
   beginning)
2. `(\d+)` - match one or more digits, capturing them as a return value
3. `,` - match a literal comma
4. `\s*` - match any amount of whitespace, to skip the space after the comma
5. `(\d+)` - match the second number

The `String.parse()` method returns the capture groups (parenthesized sequences)
in an array and discards the rest of the string. Thus, this code results in the
array `[16, 24]`, which is the two values we were looking for.

First-Class Functions
---------------------

Panda provides [first-class methods](inlineMethods.html) and functions, which
enable very powerful operations to be done quickly and easily. For instance, 
consider the (admittedly contrived) problem of finding all of the numbers in a 
string and adding 2 to them. `String.replace()` has a variant which takes a 
regular expression to search for, and a function which generates the 
replacement text based on the match text. The code:

    def testString := "Do 6 damage to each of 2 different enemies."
    Console.writeLine(testString.replace(#/\d+/#, number => number->>(Int) + 2))

will do the trick. The value `#/\d+/#` is the regular expression `\d+`, meaning
"one or more digits". The value `number => number->>(Int) + 2` is a 
[lambda](inlineMethods.html#lambdas) which takes the matched string, converts
it to a number, and adds two. This results in the text:

    Do 8 damage to each of 4 different enemies.

Panda's lambdas are similar to Java's lambdas, but result in a function object 
rather than an implementation of an interface.

Non-Nullable References
-----------------------

All references in Panda are [non-nullable](nonNullability.html) by default. A 
variable of type `String`, for example, cannot hold the value `null`:

    var name:String := null -- doesn't compile!

To permit `null` as a legal value, you must add a trailing question mark (`?`) 
to make the type nullable:

    // Java
    String name = null;

    -- Panda
    var name:String? := null

Panda will not allow you to use a possibly-null value anywhere where a
non-nullable type is expected:

    def name:String? := possiblyNullValue()
    Console.writeLine(name) -- doesn't compile!

But as long as you prove to the compiler that the value cannot in fact be 
`null`, it works:

    def name:String? := possiblyNullValue()
    if name != null
        Console.writeLine(name) -- now it works!

See the page on [non-nullability](nonNullability.html) for more information.

Contracts
---------

Panda provides [contracts](contracts.html), which are conditions that code must
adhere to, in order to help enforce code quality. Contracts are one of the major
advantages of using Panda and you should try to get in the habit of using
preconditions, postconditions, and invariants often.



more to come...

