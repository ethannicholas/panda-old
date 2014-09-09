Non-Nullable References
=======================

Panda's [types](types.html) are *non-nullable* by default. This means simply 
that [`null`](null.html) is not a legal value for the type: a 
[`method`](methods.html) declared to return `String` may not return `null` 
instead, `Array<Widget>` may not contain any `null` values, and so forth.

Why eliminate `null`?
---------------------

Dereferencing a `null` reference is the single most common cause of crashes and
exceptions in most programming languages. Tony Hoare, the Turing Award-winning
creator of the QuickSort algorithm and the first person to use `null` in 
object-oriented programming, called his invention of the `null` reference his 
"billion-dollar mistake" because `null` has "led to innumerable errors, 
vulnerabilities, and system crashes, which have probably caused a billion 
dollars of pain and damage in the last forty years". By making it impossible to
give `null` to code which is not expecting it, an entire class of program 
crashes and errors simply disappears.

What if I need a `null`?
------------------------

The `null` reference means "no value exists". There are times that this is
entirely appropriate: perhaps you don't know the user's email address, and so a 
`null` return from `function emailAddress()` would be the expected result. While 
Panda types are non-nullable by default, you may also declare types nullable by 
adding a trailing "?". `String` may not be `null`, but `String?` (pronounced 
"String or `null`") may be. Use non-nullable types where possible, but it is 
generally better to use a `null` where required than contort your program with 
placeholder values and other tricks to avoid using `null`.

Mixing nullable and non-nullable references
-------------------------------------------

You will often find yourself in a situation where you have a nullable reference,
and need to use it where a non-nullable reference is required. Suppose you have
a function

@SOURCE(
    class Widget { }
    --BEGIN
    function getNextWidget():Widget?
    --END
    { return new Widget() }
)

Because there might not be a `Widget` ready for processing, this function can
return `null`. You also have


@SOURCE(
    class Widget { }
    --BEGIN
    method processWidget(w:Widget)
    --END
    { }
)

You'd like to get the next widget and process it. So you write:

@SOURCE(
    function getNextWidget():Int { return 5 }
    method processWidget(i:Int) { }
    --BEGIN
    processWidget(getNextWidget())
)

Result: `cannot use possibly-null value as non-nullable type Widget`

This doesn't compile! `getNextWidget()` might have returned a `null`, and
`processWidget()` doesn't allow `null`. We can solve this by proving to the 
compiler that the value cannot actually be `null`: Panda allows us to use a
nullable type as if it were non-nullable if it can *prove* via static analysis
that the value cannot in fact be `null`. So we can instead write:

@SOURCE(
    function getNextWidget():Int? { return 5 }
    method processWidget(i:Int) { }
    --BEGIN
    def widget := getNextWidget() -- widget has type 'Widget?'
    if widget != null
        processWidget(widget)
)

This version compiles fine. Even though `widget` has type `Widget?`, and
`processWidget()` requires type `Widget`, the compiler knows that if we made it
past the `widget != null` check, then `widget` isn't actually `null`. Since it
has been proven to be non-`null`, the compiler does not complain when you pass
it to a method requiring a non-`null` value. Likewise, the following code 
compiles fine:

    -- FIXME the new compiler isn't actually doing constant folding yet, and
    -- therefore can't work this one out anymore
    class Widget { }
    --BEGIN
    var contrived:Widget
    if 5 * 6 > 8 + 9
        contrived := ne Widget()
    else
        contrived := null
    loop {
        if true
            break
        contrived := null
    }
    processWidget(contrived)

The static analyzer can see that we cannot reach the `processWidget(contrived)`
call with a `null` value, and so it allows the call.

Static analyzers are smart, but it is not possible for any static analyzer, no 
matter how smart, to perfectly predict how a program may behave. There will be 
times where you, being smarter than a computer, know that a particular situation 
is impossible, but the static analyzer cannot prove that. Perhaps this code is 
only called when a `Widget` is already known to be available, so the complaints 
about `getNextWidget()` possibly returning `null` are spurious. The best way to 
handle this is to `assert` that the value is non-`null`:

SOURCE(
    function getNextWidget():Int? { return 5 }
    method processWidget(i:Int) { }
    --BEGIN
    def widget := getNextWidget()
    assert widget != null
    processWidget(widget)
)

It probably is not surprising that this code compiles fine when assertions are 
enabled. We clearly can't reach the `processWidget(widget)` statement with a 
`null` widget. It may be a bit more surprising that this code still compiles 
when assertions are disabled. As any code that would fail an assertion or 
otherwise generate a safety error is allowed to invoke undefined behavior when
safety checks are disabled, the compiler can simply assume that all assertions
pass when safety checks are off.

In addition to proving that the value is non-`null`, or asserting that the value
is non-`null`, you may simply [cast](operators.html#cast) the nullable type to 
its non-nullable equivalent. The code:

@SOURCE(
    class Widget { }
    function getNextWidget():Widget { return new Widget() }
    method processWidget(w:Widget) { }
    --BEGIN
    processWidget(getNextWidget()->(Widget))
)

compiles without error, and will verify the cast at runtime (assuming safety
checks are left enabled). This is more-or-less equivalent to the assertion
version above, and reflects your confidence that `getNextWidget()` is not
actually going to return `null`. While using casts in this fashion is legal,
you should strongly consider using assertions instead. Assertions make your 
intent more clear, by forcing you to state explicitly "this value will never, 
ever be `null`" as a separate statement, rather than bury the assumption in the
middle of another statement.

**IMPLEMENTATION NOTE:** Panda's static analyzer is still very much a work in
progress. One major annoyance occurs in code like this:

    function example():Object? {
        return ...
    }

    if example != null
        Console.writeLine(example)

This *should* compile just fine. Unfortunately, it is flagged as an unsafe use
of `null`, because there are two calls to `example()` and the analyzer isn't
yet smart enough to realize that they are (in this case, at least) guaranteed to 
return the same thing. Fortunately, working around this issue is easy:

    function example():Object? {
        return ...
    }

    var e := example()
    if e != null
        Console.writeLine(e)

Expect the static analyzer to continually improve as Panda is developed; this
particular situation will certainly be fixed before Panda is officially
released.
