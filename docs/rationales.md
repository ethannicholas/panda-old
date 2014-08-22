Rationales
==========

It often isn't obvious from looking at a language *why* a particular design was
chosen for a feature. The language's designer may have tried several different
approaches, discarding each of them in turn, before finally settling on what he
deems the best (or sometimes least awful) approach. Without having gone through 
the same process as the designer, without seeing the problems with other 
approaches firsthand, it may not be at all obvious why certain things are the 
way they are. In this document I will attempt to describe my rationale for
structuring various features of Panda the way I did. 

You of course may not agree with my decisions; the simple fact that there are so 
many different programming languages out there shows that there are many ways to
solve the same problem. But perhaps some insight into the design process may at 
least make it easier to see where I am coming from. Note that I make absolutely 
no claims to be a language design expert or anything of the sort. Panda is my 
first "real" programming language, and my thoughts during the design process can 
best be summed up as "oh god I have no idea what I'm doing and I hope no one 
notices".

*Why are `Array.length` and `String.length` signed integers? They can't ever be
negative!*

Two reasons. First, there is no safe conversion between `Int32` and `UInt32`, 
which would force any code which cares about string or array length (which 
covers pretty much all code) to deal with unsigned numbers and their attendant 
complications. Second, `Int32` doesn't overflow until you get roughly two 
billion away from zero, which is a limit most programs will never approach. 
`UInt32` can overflow one away from zero, and is therefore much easier to 
encounter overflows with (consider `array.length - 1` when `array.length` is 
`0`). For these reasons, the core Panda APIs allow you to work with unsigned 
numbers, but never require you to do so.

*Why does Panda math promote to 32 bits?*

Consider the following code:

    var x := 20
    x *= 20

Which answer would you expect?

A) 400
B) -112
C) panda.core.OverflowError

20 is an `Int8`, but 20 * 20 is too big to fit into an `Int8`. We really only 
have three choices: promote to a type which is "big enough" for day-to-day math,
silently overflow an `Int8` (resulting in `-112`), or complain about the 
overflow. Panda chooses to promote all types to at least `Int32`, because it's
much less surprising to run into an overflow when working with numbers on the
order of several billion than when working with numbers on the order of twenty.

*Why doesn't Panda support the ternary operator?*

C's ternary operator uses up two symbols ('`?`' and '`:`'), both of which 
already have important meaning in Panda, adds very little expressive power, and 
is notoriously difficult for new programmers (and even sometimes experienced 
programmers) to read properly. I considered various other ways to add this 
feature (such as allowing an `if` construct to be used as a value) but after
writing thirty thousand lines of Panda code I realized I didn't miss the ternary
operator enough to worry about it, at least not yet. 

Panda is slightly more verbose as a result, but if brevity were all that 
mattered we'd all be using something like
[APL](http://en.wikipedia.org/wiki/APL_(programming_language)) instead. There's
a lot to be said for readability.

*Why doesn't Panda support pre / post increment / decrement?*

The various increment / decrement operators also add very little to the 
language; there's very little difference between `i++` and `i += 1`. The primary
use of these operators in C-derived languages is in `for` loops, but the Panda
`for` loop doesn't use an explicit increment operation, so for that and other
reasons these operations would see much less use in Panda. The only other reason 
for them to exist is to embed side-effecting operations in the middle of 
expressions, which is something Panda expressly tries to minimize. This is the
same reason why assignment expressions (like `i += 1`) may not be used as values
in expressions.

*Why no type inference on method returns?*

There are of course languages which take type inference farther than Panda does, 
but there are a whole series of tradeoffs involved. In this case, I 
stylistically prefer having to declare method returns so one can simply look at
the header to see a method's full signature, but even if I wanted to infer the
return value it couldn't be done in Panda as it is now. The issue in this case
is, perhaps surprisingly, semicolons.

Lots of languages require a line terminator such as a semicolon or significant
carriage return to tell the parser when one statement is finished and the next 
begins. The ones which don't generally have a much simpler syntax than Panda; 
only a relative handful of languages have syntactic complexity comparable to
Panda and yet do not require line terminators. It turns out that it's a hard
problem to solve; there are lots of nonobvious ways for a grammar without line
terminators to end up being ambiguous. Here's one example:
    
    if foo()
        return bar()

    if foo()
        return
    bar()

These are the exact same sequences of tokens, structured using whitespace to
make two different intents clear. In one case we are returning the value 
`bar()`, and in the other case we are either returning no value or else calling 
`bar()`. But the Panda compiler doesn't care about whitespace or indentation, so
it is going to see these two examples as being exactly the same. You could in
fact structure it like
    
    if foo() return bar() -- don't do this!

and it would make no difference. So how do we handle two different intents for 
the same sequence of tokens? We have to know whether or not the method returns a 
value; if it does return a value, we compile it as `return bar()`, and if it 
doesn't, we compile it as a `return` and a separate call to `bar()`. This is one 
of a few cases where the parser needs some context about what it is parsing in 
order to handle it correctly; while I have generally tried to avoid such cases, 
I decided that freeing the language of the tyranny of semicolons was worth a 
tiny bit of uncleanliness.

So, we need to know whether a method returns a value. While we could potentially
have gone hard core and only allow functions to return values (as in 
[call-query separation](http://en.wikipedia.org/wiki/Command–query_separation)),
have significant whitespace, or have some other signal for whether a method 
returns a value, I felt that the cleanest and most practical solution was simply
to require specification of return types.

*Why is `Char` only 16 bits? That's not enough to represent all of Unicode!*

It's true that a 16 bit `Char` can't represent every character in Unicode 
without requiring multiple `Char` values for a single character. But neither can
a 32 bit `Char`! No matter how wide your `Char` is, you would still have to deal
with things like LATIN SMALL LETTER O + COMBINING DOT BELOW + COMBINING 
CIRCUMFLEX ACCENT. That's three Unicode code points to represent a single 
logical character, and that happens even with a 32 bit `Char`.

Obviously, you could take this argument to its logical extreme and say "Well, 
why even have a 16 bit `Char`, then? If you're just going to accept multiple
`Char`s to represent a single character, why not go all the way down to bytes 
and make everybody deal with UTF-8?" And, of course, that's one possible way to 
go. I felt that the best tradeoff between utility, memory consumption, and 
performance was a 16 bit `Char`, so that's what Panda has.

*Why can't I perform math on `Char`?*

I admit that having to do `(c->(UInt16) + 1)->(Char)` to add one to a `Char` is 
considerably less graceful than a simple `c + 1`. But language design is full of
tradeoffs, and often when you make one thing easier you often make another thing
harder. Let's look at Java, a similar language which does permit math on its 
`char`, for comparison. Take a look at this Java code:

    StringBuilder s = new StringBuilder('[');
    int[] values = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < values.length; i++) {
        if (i > 0)
            s.append(',');
        s.append(values[i]);
    }
    s.append(']');
    System.out.println(s);

It certainly looks like it should output `"[1,2,3,4,5]"`, doesn't it? But if you
compile and run this code snippet, you will see that the result is in fact
`"1,2,3,4,5]"`. The bug is subtle: we created the `StringBuilder` with an 
initial `char`, but `StringBuilder` doesn't have a `char` constructor. So the
`char` gets upconverted to an `int` and is used to specify the initial size of
the `StringBuilder`. I have seen bugs like this in production code, where 
someone was obviously expecting a `char` to be used as a string-like value but 
it was instead being used as a plain `int`. During a job interview, I once 
watched a frustrated candidate spend several minutes trying to figure out why 
his
    
    System.out.print(result + '\n');

wasn't giving him the output he expected, before he finally gave up and accepted
my offer of a hint. (He was obviously stuck on the idea that his calculation was
wrong, and never considered the possibility that the `print` itself was the
culprit until I suggested he look more closely at that line.) The point is that 
in Java `x + "\n"` and `x + '\n'` usually do the exact same thing, but if `x` 
happens to be a number it will suddenly do something very different for no 
obvious reason. It's very easy to feel smugly superior to the hapless interview
candidate I describe, but that's only because you're not the one in the hot seat
staring at code that is spitting out a blatantly wrong answer for no reason you
can see. I've never met the programmer who hasn't at least occasionally spent 
hours debugging simple, stupid mistakes like this, and the fewer pitfalls like 
this that Panda has, the better.

On top of that, performing math on `Char` is rare, and most of the time it is 
being done is actually bad (for instance, adding 32 to convert uppercase to 
lowercase characters works great as long as your data is ASCII, but won't work
on any non-English letters). There is seldom a good reason for general purpose 
code to treat `Char` as a mathematical entity, but there are plenty of times you 
might pass a `Char` in to a method thinking it will be treated as, well, a 
`Char` and not an `Int`.

This is also one of those issues where it's easy to add the feature if I change
my mind later, but impossible to take out without breaking things. So I have 
tended to leave such features out, secure in the knowledge that I can always add
them in later.

*Operator overloading? Ewwwww!*

That's... not a question. But I'll do my best to answer it anyway! Operator
overloading generally has a bad reputation, caused in no small part by the
excesses of C++. While I freely admit that operator overloading is prone to
abuse, it's worth noting that the alternative is not all sunshine and roses,
either. If you've ever had to write something along the lines of:

    a = a.add(b.mul(c)).div(d);
    values.set(x, values.get(1) + a);

you may be able to appreciate the Panda equivalent:

    a := (a + b * c) / d
    values[x] += a

So while operator overloading can be abused, it can also result in much more
natural, easier-to-read code. The main complaints against operator overloading
seem to be:

1. It's not obvious when code is invoking user-defined operators.
2. Seemingly-safe expressions can have unexpected side effects.
3. You can repurpose existing operators to do something completely different 
   (such as bitwise shift becoming stream insertion / extraction in C++)
4. You can violate common mathematical expectations, such as associativity or
    commutativity

I'll address these in turn.

1. In Panda, at least, I don't really agree with this. If you're adding two 
   things together, and *at least one of them isn't a number*, you're invoking 
   an overloaded operator. That's basically all you need to know, and if you 
   don't know whether what you're operating on is a number or not, you're going 
   to have bigger issues trying to understand what the code is doing. 

   Code comprehensibility is the reason that Panda doesn't allow overloading of
   parentheses (i.e. to have `foo(12)` actually be a call to an overloaded 
   parentheses operator defined on the object `foo`), as it suddenly becomes 
   much less obvious what the code is doing; I did not feel that the marginal 
   benefit of allowing this was worth the cost.
2. This is true in general, but not in Panda. Other than the various assignment
   operators (indexed, slice, and field assignment), Panda's operators must be
   functions and therefore may not have side effects. Furthermore, the 
   assignment operators must be defined as [`@self`](annotations.html#self), so
   they are not allowed to alter anything but the object being assigned to.
3. True, but you can also define a function named `multiply()` which actually
   divides. We allow programmers to define names for their functions, trusting
   them to not do stupid things like naming them counter to what they actually
   do, but for some reason expect that all of this common sense immediately goes
   out the window when it comes to operators. 

   Unfortunately, history has shown that there may in fact be some truth to 
   this, as some programmers do in fact repurpose operators to do something
   unexpected. Panda attempts to mitigate this, first by setting a good 
   example (the Panda core libraries are very conservative in how they use 
   operators), second by preventing side effects on operators that aren't 
   supposed to have them (the stream insertion / extraction example from C++ 
   isn't even *possible* in Panda), and third by giving each operator a standard 
   name which is used in all automatically-generated documentation, to hopefully 
   remind people that they have done something awful by repurposing an existing 
   operator to do something other than its name would indicate.
4. Mathematics already violates these assumptions itself: matrix multiplication,
   for example, is not commutative. The basic assumptions of associativity and
   commutativity hold only for numbers and not for other more complex 
   mathematical objects; I see no issue with the same basic pattern happening
   elsewhere.

*Why are the `&` / `&&` and `|` / `||` operators backwards?*

C (and, by inheritance, many other languages) use `&` and `|` for bitwise
operations, and `&&` and `||` for logical operations. Panda reverses this,
potentially leading to confusion for people familiar with C-derived languages.
Why?

There are four common boolean operations: AND, OR, XOR, and NOT (there are
others, of course, but they are not generally used by programmers). Each of 
these operators can operate either on boolean values (`Bit`, in Panda) or 
integer types. Here's how it breaks down in C and its ilk:

AND: either `&&` (logical) or `&` (bitwise)
OR: either `||` (logical) or `|` (bitwise)
XOR: `^` (either bitwise only, as in C, or both bitwise and logical, as in Java)
NOT: either `!` (logical) or `~` (bitwise)

And here's the lineup in Panda:

AND: either `&` (logical) or `&&` (bitwise)
OR: either `|` (logical) or `||` (bitwise)
XOR: either `~` (logical) or `~~` (bitwise)
NOT: either `!` (logical) or `!!` (bitwise)

Panda's greater consistency appeals to me, so the only remaining question was
which should require a single symbol and which a double symbol. As logical
operations (especially `!`) tend to be vastly more common than bitwise 
operations, this was an easy choice. The fact that it is opposite the C / Java
convention in the case of `||` / `&&` is unfortunate, but I am not going to
promulgate a mistake just because it happens to be popular. As far as I'm 
concerned, C and Java do it the wrong way around.

There was, of course, another option: there's no reason these operators need to
be different at all!` In Panda, unlike in C, the presence of an actual boolean
type means that we could use the same symbol for both logical and bitwise
operators. But logical OR and AND, in particular, have very different semantics
than bitwise OR and AND (boolean short-circuiting), and the two sets of 
operators do not "want" the same precedence (bitwise OR and AND are used
equivalently to addition and multiplication, whereas logical OR and AND need
markedly lower precedence). Other languages generally handle this by making you 
add lots of parentheses to counteract the surprisingly low precedence of the 
bitwise operators, while Panda gives the two sets of operators different 
precedences.

Like I said, often there's just no completely-right answer.