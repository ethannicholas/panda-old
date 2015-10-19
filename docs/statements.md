Statements
==========

Panda code is comprised of a sequence of *statements*. Statements are executed 
one at a time, in order, except where *control flow statements* specifically 
repeat or skip statements. The following statement types are supported:

<a name="assignment"></a>
Assignment
----------

    <l-value> <assignmentOperator> <value>

An *l-value* is a value which can be assigned to. L-values include variables,
fields, and array elements. The `assignmentOperator` specifies the kind of 
assignment to be performed, either simple assignment (`:=`) or one of the 
compound assignment operators (`+=`, `-=`, `*=`,`/=`, `//=`, `%=`, `^=`, `<<=`,
`>>=`, `>>>=`, `&=`, `|=`, `~=`, `&&=`, `||=`, or `~~=`). Simple assignment 
makes `<l-value>` equal to `<r-value>`, whereas the compound assignment 
operators make `<l-value>` equal to `<l-value> <operator> <r-value>`.

See [Operators](operators.html) for full details on compound assignment.

<a name="methodCalls"></a>
Method Calls
------------

    [<object>.]<methodName>(<parameters>)

A method call statement *invokes* a [method](methods.html). If the context 
`<object>` is omitted, the method will be resolved against [`self`](self.html)
or the current [class](classes.html). The return values of methods called as 
statements are ignored.

[Functions](functions.html) may not be called as statements: the only reason to 
call a method as a statement is for the side effects it may have, and functions 
do not have side effects.

<a name="control"></a>
<a name="if"></a>
if
--

<p><div class="pandacode"><span class="control IF">if</span> &lt;condition&gt; {
    &lt;statements&gt;
}
[<span class="control ELSE">else</span> {
    &lt;statements&gt;
}]</div></p>

The `if` statement makes a decision based on the value of a `Bit` expression. If 
the `Bit` is `true`, the statements under the `if` are executed. If the `Bit` is
`false`, then the statements under the `else` (if there is an `else`) are
executed. The curly braces (`{ }`) are only required if there is more than one
statement in a block. For instance,

@SOURCE(
    var x := getValue()
    if x > 5
        Console.writeLine("x is greater than 5")
    else {
        Console.writeLine("x was less than or equal 5")
        x := 5
    }
    --END
    function getValue():Int {
        return 10
    }
)

<a name="for"></a>
for
---

<p><div class="pandacode">[&lt;label&gt;:] <span class="control FOR">for</span> [&lt;index&gt;,] &lt;value&gt; <span class="control IN">in</span> &lt;collection&gt; {
    &lt;statements&gt;
}</div></p>

The `for` loop iterates over a collection one entry at a time. As a simple 
example, the loop:

@SOURCE(
    for i in 1 ... 5
        Console.writeLine(i)
)

will display the numbers 1 through 5. Any object implementing the [Iterable]
interface may be iterated through, such as this list of strings:

@SOURCE(
    for greeting in ["Hello", "Bonjour", "Konnichi wa"]
        Console.writeLine(greeting)
)

If you need to know which index the loop is currently examining, provide the 
name of an index variable prior to the value variable:

@SOURCE(
    for i, greeting in ["Hello", "Bonjour", "Konnichi wa"]
        Console.writeLine("greeting #\{i} is: \{greeting}")
)

Both the `<index>` and `<value>` may have optional type specifiers, as in
`for i:Int, v:String in ...`.

Adding or removing entries from the collection while the loop is running causes
undefined behavior.

The optional `<label>` on a loop allows `break` and `continue` statements to
refer to loops by name. It is otherwise ignored.

If the collection being iterated over contains [tuples](tuples.html), you can
provide a parenthesized list of variable names to split the tuple into 
separate variables:

@SOURCE(
    def list := [("Five", 5), ("Twelve", 12), ("Forty-two", 42)]
    for (name, value) in list {
        numbers[name] := value
    }
    --END
    function numbers():Map {
        return new HashMap()
    }
)

As before, you may specify an index variable name and/or variable types:

@SOURCE(
    for index:Int, (name:String, value:Int8) in list {
        Console.writeLine("processing #\{index}")
        numbers[name] := value
    }
    --END
    function list():Array<(String, Int8)> {
        return new Array<(String, Int8)>()
    }

    function numbers():Map {
        return new HashMap()
    }
)

In addition to objects implementing the `Iteratable` interface, `Iterators`
themselves may be iterated over:

@SOURCE(
    def map := new GenericHashMap<String, String>();
    --BEGIN
    def values:Iterator<String> := map.values
    for v in values {
        Console.writeLine("iterator returned: \{v}")
    }
)

<a name="while"></a>
while
-----

<p><div class="pandacode">[&lt;label&gt;:] <span class="control WHILE">while</span> &lt;condition&gt; {
    &lt;statements&gt;
}</div></p>

The `while` statement repeatedly executes a block of statements so long as its
`Bit`-valued condition is `true`. As with other Panda control statements, the
curly braces (`{ }`) are optional if the loop body is a single statement.

The optional `<label>` on a loop allows `break` and `continue` statements to
refer to loops by name. It is otherwise ignored.

<a name="do"></a>
do
--

<p><div class="pandacode">[&lt;label&gt;:] <span class="control DO">do</span> {
    &lt;statements&gt;
}
<span class="control WHILE">while</span> &lt;condition&gt;</div></p>

The `do` loop is very similar the `while` loop, but it checks its condition at
the end of the loop rather than the beginning. The loop body will therefore 
always execute at least once.

The optional `<label>` on a loop allows `break` and `continue` statements to
refer to loops by name. It is otherwise ignored.

<a name="loop"></a>
loop
----

<p><div class="pandacode">[&lt;label&gt;:] <span class="control LOOP">loop</span> {
    &lt;statements&gt;
}</div></p>

The `loop` statement runs its body over and over indefinitely. It is an infinite
loop unless a `break`, `return`, or `throw` statement escapes from it.

The optional `<label>` on a loop allows `break` and `continue` statements to
refer to loops by name. It is otherwise ignored.

<a name="break"></a>
break
-----

<p><div class="pandacode"><span class="control BREAK">break</span> [&lt;label&gt;]</div></p>

The `break` statement immediately terminates a loop, causing execution to 
continue from the statement immediately after the end of the loop. By default, 
`break` terminates the innermost loop it is contained within, as in:

@SOURCE(
    loop {
        var value := getValue()
        if value = null
            break
        sendValue(value)
    }
    --END
    function getValue():String? {
        return "unused"
    }

    method sendValue(s:String) {
    }
)

`break` with a label can be used to break out of multiple nested loops:

@SOURCE(
    outer: for x in 0 .. width {
        for y in 0 .. height {
            processCell(x, y)
            if !isValid()
                break outer
        }
    }
    --END
    method processCell(x:Int, y:Int) {
    }

    function isValid():Bit {
        return true
    }

    function width():Int {
        return 0
    }

    function height():Int {
        return 0
    }
)

Note that `break` is one of three constructs in Panda which is sensitive to 
whitespace. An identifier following `break` *on the same line* is taken to be a 
loop label, while if the identifier is on the next line it is taken to be the
start of another statement.

<a name="continue"></a>
continue
--------

<p><div class="pandacode"><span class="control CONTINUE">continue</span> [&lt;label&gt;]</div></p>

The `continue` statement immediately skips ahead to the next iteration of a 
loop, as if the end of the loop body has just been reached. Just as with 
`break`, it normally operates on the innermost containing loop but can be used
with an optional label to continue loops other than the innermost one:

@SOURCE(
    outer: for x in 0 .. width {
        for y in 0 .. height {
            processCell(x, y)
            if skipRestOfColumn()
                continue outer
        }
    }
    --END
    method processCell(x:Int, y:Int) {
    }

    function skipRestOfColumn():Bit {
        return true
    }

    function width():Int {
        return 0
    }

    function height():Int {
        return 0
    }
)

Note that `continue` is one of three constructs in Panda which is sensitive to 
whitespace. An identifier following `continue` *on the same line* is taken to be
a loop label, while if the identifier is on the next line it is taken to be the
start of another statement.

<a name="return"></a>
return
------

<p><div class="pandacode"><span class="control RETURN">return</span> [&lt;value&gt;]</div></p>

The `return` statement immediately exits the containing method and causes it to 
return the specified value. Return statements in methods which return values 
must always provide a value, and return statements in methods which do not 
return values may never provide a value.

Note that `return` is one of three constructs in Panda which is sensitive to 
whitespace. An expression following `return` *on the same line* is taken to be 
the value to return, while if the expression is on the next line it is taken to 
be the start of another statement.

<a name="throw"></a>
throw
-----

<p><div class="pandacode"><span class="control THROW">throw</span> &lt;error&gt;</div></p>

Raises an exception. The exception unwinds the call stack until it reaches a
`try` with a `catch` block capable of handling the error. Control then transfers 
to the beginning of the catch block in question. `<error>` must be an expression
evaluating to a subclass of `Error`.

<a name="try"></a>
try
---

<p><div class="pandacode"><span class="control TRY">try</span> {
    &lt;statement&gt;
}
[<span class="control CATCH">catch</span> &lt;name&gt;:&lt;type&gt; {
    &lt;statements&gt;
}]
[<span class="control CATCH">catch</span> &lt;name&gt;:&lt;type&gt; {
    &lt;statements&gt;
}]]
[<span class="control FINALLY">finally</span> {
    &lt;statements&gt;
}]
</div></p>

Executes a block of statements with exception handling. If the code within the 
`try` block throws an exception and one of the `catch` blocks can handle that
type of exception, control will resume at the `catch` block.

Whenever execution leaves the `try` block, for any reason (such as a thrown
exception or a `return`), the code within the `finally` block will be executed.

**IMPLEMENTATION NOTE**: `finally` isn't actually working yet, and there's a
chance I may change my mind and try a different approach than `finally`. There
is currently a bug where if you nest `try` blocks, the outer `catch` will not 
catch exceptions originating from the inner `try` block (this applies only to
nested `try / catch` structures within *the same method*; exceptions propagate
between methods just fine).

<a name="assert"></a>
assert
------

<div class="pandacode"><span class="assert ASSERT">assert</span> &lt;condition&gt;[: &lt;error&gt;]</div>

An `assert` statement tells the compiler that `<condition>` should always be
`true` at this point. With safety checks on, the `<condition>` is double-checked
at run time and, if it is found to be `false`, a `SafetyError` is thrown to 
indicate the failure.

With safety checks off, the assertion is *assumed* to be true and is not 
double-checked at runtime. This allows the compiler to optimize the code under
the assumption that the condition is in fact `true`. Any code that would throw a 
`SafetyError`, including a failed assertion, becomes undefined behavior when
safety checks are disabled.

If you do not specify an `<error>`, an empty `AssertionError` is thrown for
failed assertions when safety checks are enabled. To provide more information,
`<error>` may be specified as a string (in which case the thrown 
`AssertionError` has this string as a message) or a side-effect-free expression 
of type `SafetyError`, in which case this is the exception thrown in response to
failures.

Assertions which always evaluate to false are a compile-time error. In other
languages, you may be used to using something equivalent to `assert false` to
signify "it should not be possible for this line of code to be reached", but in
Panda `assert false` will not compile. You need to use `unreachable`, described
below, to express this.

**IMPLEMENTATION NOTE:** "assert false" isn't actually a compiler error yet, but
it will be soon.

<a name="unreachable"></a>
unreachable
-----------

<div class="pandacode"><span class="control UNREACHABLE">unreachable</span></div>

The `unreachable` statement tells the compiler that this line of code will never
actually be reached. For instance, in the code:

@SOURCE(
    var widget:Widget
    if widgetReady()
        widget := nextWidget()
    else if canManufactureWidget()
        widget := makeWidget()
    processWidget(widget)
    --END
    class Widget {
    }

    function widgetReady():Bit {
        return true
    }

    function nextWidget():Widget {
        return new Widget()
    }

    function makeWidget():Widget {
        return new Widget()
    }

    function canManufactureWidget():Bit {
        return true
    }

    method processWidget(widget:Widget) {
    }
)

we will receive a compilation error because `widget` is not definitely assigned.
What if there is no ready widget and we cannot manufacture a new one? But 
suppose we know for sure that one of those conditions will always be true. We 
can then modify the code to read:

@SOURCE(
    var widget:Widget
    if widgetReady()
        widget := nextWidget()
    else if canManufactureWidget()
        widget := makeWidget()
    else {
        -- can't happen!
        unreachable
    }
    processWidget(widget)
    --END
    class Widget {
    }

    function widgetReady():Bit {
        return true
    }

    function nextWidget():Widget {
        return new Widget()
    }

    function makeWidget():Widget {
        return new Widget()
    }

    function canManufactureWidget():Bit {
        return true
    }

    method processWidget(widget:Widget) {
    }
)

and the code will then compile. We are asserting to the compiler that there is 
always either a widget ready or we will be able to manufacture one, and that the 
final `else` clause cannot actually be reached. The `widget` variable is 
therefore definitely assigned, because the only possible path by which `widget`
would remain unassigned is known to be `unreachable`.

Actually reaching an `unreachable` statement is, of course, bad. By default, 
this will result in a `SafetyError`. If you disable safety checks, the compiler
is free to optimize under the assumption that no `unreachable` code is actually
reached, and reaching `unreachable` therefore causes undefined behavior.

<a name="switch"></a>
switch
------

<p><div class="pandacode"><span class="control SWITCH">switch</span> &lt;expression&gt; {
    [<span class="control CASE">case</span> &lt;value1&gt;[, &lt;value2&gt;...]: {
        &lt;statements&gt;
    }]
    ...
    [<span class="control DEFAULT">default</span>: {
        &lt;statements&gt;
    }]
}
</div></p>

The `switch` statement runs one of a number of blocks based on the value of its
`<expression>`. `switch` is a generalization of `if`: `if` runs one of two 
blocks based on the value of its `Bit` expression, whereas `switch` runs one of
any number of blocks based on the value of its expression. Each `case` may have
any number of values, and the `case` will be run if the `<expression>` matches 
any of the `case` values. If none of the `case` values match, the `default`
block (if any) is run. If none of the `case` values match and there is no
`default` block, execution simply continues after the end of the `switch`.

Unlike many other languages, Panda's switch statement does not have 
"fall-through": when the statement or block associated with a `case` finishes,
execution continues after the end of the switch statement (rather than at the 
beginning of the next `case`), and `break` is not necessary (or, in fact, even 
legal) within a `case`. 

Example:

@SOURCE(
    switch token {
        case Token.PLUS, Token.MINUS: additiveExpression()
        case Token.TIMES, Token.DIVIDE: multiplicativeExpression()
        default: throw new ParseException()
    }
    --END
    enum Token {
        PLUS, MINUS, TIMES, DIVIDE
    }

    function token():Token {
        return Token.PLUS
    }

    method additiveExpression() {
    }

    method multiplicativeExpression() {
    }
)

`case` values must be compile-time constants.

**IMPLEMENTATION NOTE:** `switch` is currently lowered to a sequence of `if`
statements, negating the performance advantage one would expect from using
`switch`. Obviously this is just a temporary situation while Panda is in 
development.