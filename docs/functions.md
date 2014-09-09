Functions
=========

A `function` is a method which has two special restrictions:

1. Functions may not depend upon unpredictable state
2. Functions may not have side effects

Functions are declared exactly like other methods, but with the `function` 
keyword replacing the `method` keyword:

@SOURCE(
    function square(x:Real):Real {
        return x * x
    }
)

Note that functions are still considered methods, just with these two additional 
restrictions. The "may not depend upon unpredictable state" restriction is the
simplest, because it does not generally affect pure Panda code. "Unpredictable"
state is state which could change without Panda's knowledge; for instance, 
whether or not a file exists on the filesystem is "unpredictable" in that a
program could check for the file's existence multiple times and receive a
different answer each time, without having done anything to the filesystem 
itself. The `File.exists()` method is therefore a method, rather than a 
function. If your program is written in 100% Panda and you do not use any APIs 
that include the word "unsafe" in their names, you should never need to worry 
about this restriction.

"Side effects" are defined in Panda as "making changes to state which are 
visible outside of the function itself". Functions may freely modify state that 
only they can see; for instance, the following function is legal:

@SOURCE(
    class Example {
    var firstName:String? := "Example"
    var lastName := "Example"
    var middleName:String? := "Example"
    --BEGIN
    function getName():String {
        var result := new MutableString()
        result.append(lastName)
        if firstName != null {
            result.append(", ")
            result.append(firstName)
            if middleName != null {
                result.append(" ")
                result.append(middleName)
            }
        }
        return result->>(String)
    }
    --END
    }
)

This function creates a mutable object and manipulates it -- clearly it is
modifying state! However, the `MutableString` is not visible outside of the
function itself, and the `append` method does not modify anything but the 
`MutableString` in question. Therefore, this code does not result in any data
visible outside of the function itself changing, and is legal.

In order to comply with the "no side effects" restriction, a function may only
call non-function methods when:

1. The method is marked [`@self`](annotations.html#self) and the object that 
   owns the method is not visible outside the function
2. The method is marked [`@limited`](annotations.html#limited) and neither the 
   object that owns the method nor any of the method's mutable parameters are 
   visible outside the function

For an object to be "not visible outside the function", it must have been 
created inside the function itself by an `@self` constructor. Note that
constructors are *automatically* flagged `@self` when they comply with the
`@self` restrictions; you do not need to manually add this annotation to your 
constructors, and in practice the vast majority of constructors will be 
considered `@self`.

You should be in the habit of using functions where possible. They provide
strong data integrity guarantees and make it easier to write high-quality code.
Furthermore, functions enable optimizations that would otherwise not be 
possible: for instance, if you make multiple calls to the `getName()` function
above, the compiler may be able to prove that the object has not changed in
between the calls and therefore it is safe to simply re-use the resulting string
rather than recalculate it (this optimization is only possible for `Immutable`
data types, such as `String`, since you cannot tell if you receive one shared 
`String` instead of two separate but identical `String`s).

**IMPLEMENTATION NOTE**: The optimization described above isn't actually 
happening yet; we're a fair way off from the compiler being that smart. But a 
lot of the groundwork is laid, plans are made, and there's absolutely no reason
we can't get that working exactly as I describe here.

Functions are still very early: in particular, some of the analysis and 
annotations necessary to make them 100% reliable are being handwaved over. While
the compiler will catch a lot of shenanigans, it is currently possible to write 
functions which do in fact manipulate data they shouldn't. This will be 
tightening up in the near future. Taking advantage of functionality for
optimization purposes is quite a bit further off.

Property Getters
----------------

When calling a no-argument function (only functions, not other methods), you may 
omit the parentheses from the call. This feature is used to implement 
[properties](properties.html).

Inline Functions
----------------

See [inline functions](inlineMethods.html) for more information.

Function Optimizations
----------------------

Unlike other methods, functions are not guaranteed to actually be called. 
Because they are not supposed to have side effects, the optimizer is permitted 
to remove calls to functions when the return values of the calls are unused. In
other words, given:

@SOURCE(
    function someFunction():Bit { return true }
    --BEGIN
    method foo() {
        var unused := someFunction()
    }
)

The variable `unused` is a *dead variable*; it is written to, but never read 
from, and so its value is irrelevant. Since `someFunction()` cannot have side
effects, the call to `someFunction()` does not affect anything and can be safely
removed. This means that the optimizer is permitted to rewrite the method as:

@SOURCE(
    method foo() {
    }
)

Normally, this optimization will not affect anything: `someFunction()` wasn't
doing anything useful anyway and has no side effects, so removing it should not 
affect the program's semantics. Likewise, the optimizer is permitted to "fold" 
two redundant function calls together. Assuming that `someFunction()` returns a
`Value` type:

@SOURCE(
    function someFunction():Int { return 1 }
    --BEGIN
    method foo() {
        def a := someFunction()
        def b := someFunction()
        Console.writeLine(a + b)
    }
)

Since `someFunction()` cannot have modified anything, and there is no 
intervening code between the two calls which could have modified data upon which
`someFunction()` depends, the two calls are guaranteed to have the same result.
Since we are assuming that `someFunction()` returns a `Value`, we also do not
care whether we receive two identical copies or two references to the same copy. 
Thus, the optimizer is permitted to rewrite this method as:

@SOURCE(
    function someFunction():Int { return 1 }
    --BEGIN
    method foo() {
        def a := someFunction()
        Console.writeLine(a + a)
    }
)

However, there are two things you should be aware of when it comes to these
optimizations.

    1. Functions which contain infinite loops could be skipped over.
    2. Functions which throw exceptions could be skipped over.

Because functions calls can sometimes be eliminated, it follows that the 
infinite loops or exceptions they contain could also be eliminated. For the vast
majority of software, this should be a non-issue. Functions shouldn't contain
infinite loops in the first place, and generally the only kind of exception 
thrown by a function will be `SafetyError`, which isn't guaranteed to occur
anyway.

**IMPLEMENTATION NOTE:** These optimizations are not actually implemented yet, I
just wanted to be clear that the compiler is *permitted* to do so, and will at
some point in the future.