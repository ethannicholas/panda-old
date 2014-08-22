Status and Roadmap
==================

Panda is currently in *pre-beta*. It is working well enough to have implemented
a 50,000 line compiler and a number of sample applications, and for me to use
day-to-day as my primary programming language, but it is still incomplete and a
lot of hard work remains before it is a bulletproof, complete, production-ready
language.

There are a *lot* of little things that need work, but this document is only
intended to cover some of the very high-level plans.

A Note On Backwards Compatibility
=================================

Obviously, backwards compatibility is an important goal in any programming 
language -- nobody wants to find out that their existing software has
suddenly stopped working. However, while Panda is this early in development,
backwards compatibility is not yet 100% guaranteed.

Breaking changes will not be made lightly. The entire compiler is written in
Panda, after all, which means any changes are going to hit me much harder than
they will hit anyone else. But if I discover a problem area, I'd rather fix it 
now and deal with some brief pain than be stuck with a poor decision for the 
rest of Panda's lifespan.

Once Panda hits actual beta, every piece of Panda will be marked with its
expected stability (one of STABLE, UNSTABLE, EXPERIMENTAL, or DEPRECATED), which
you will see clearly noted in the documentation. Changes to STABLE components 
are not expected to happen, though that is not a hard guarantee yet. UNSTABLE 
components *probably* won't change, and all bets are off on EXPERIMENTAL 
components. I reserve the right to introduce new keywords during this process.

Once Panda hits 1.0, anything marked STABLE will not be changing and you will be
able to trust Panda's backwards compatibilty as much as any other language.

Definite Upcoming Changes
=========================

Performance
-----------

Performance is an important long-term goal for Panda, but early on it is more
important to worry about getting the language completely working than it is to
worry about squeezing every last ounce of speed out of it. Currently, Panda is 
probably going to be at least three or four times slower than Java for 
general-purpose code even when safety checks are disabled; certain
microbenchmarks are likely at leat two orders of magnitude slower.

While that's obviously not great, consider that Java has a twenty-year head 
start and started off *far* slower than Panda is now. Panda is going to get 
considerably faster after it is feature-complete and focus turns towards
optimization.

It's worth noting that Panda's current approach to optimization is "don't". Code
generation is about as stupid as it can possibly get, and I'm using the fact 
that the languages I'm outputting to (LLVM IR and Java) have their own 
optimizing compilers as a crutch. 

Therefore, we end up with pretty tolerable (though not awesome) code despite 
zero work on optimization. Obviously this will change, but it's not completely 
clear to me where the best optimization payoffs are, since duplicating 
optimization work which is also going to be performed by LLVM or javac will suck
up a lot of time while providing little or no payoff (possibly even negative
payoff, as our optimized code might prevent even better optimizations that LLVM
would have been doing on the naive unoptimized code). Also worth noting that 
while we're not actually optimizing yet, a lot of the basic groundwork is there:
we are building a CFG, performing (very basic) dataflow analysis, and so forth 
(though given the currently-limited applications of this data, there are 
probably some serious bugs in the existing code).

Compiler Performance
--------------------

Right this second, the compiler is much slower than it should be. There are some
general performance trouble spots which are certainly affecting this, but the
major issue is blocked on generics: Array types are all instantiated separately,
and each of them has a bunch of methods getting compiled for it. Since simply
parsing the core libraries involves creation of a bunch of array types, this 
adds up to hundreds of unnecessary method compilations and thousands of lines of
code just to compile "Hello, World!".

Obviously, this isn't going to remain this way! Once generics are in and I can
reign in the craziness by reusing existing array implementations internally, the
time to compile "Hello, World!" should immediately drop back down to a fraction
of a second.

APIs
----

Panda's core libraries cover only the most basic of basics. There's no date or
time API, no networking, no arbitrary-precision math, only the most incredibly
simple of a graphics API, no sound API, and there are a million other things 
missing. This isn't because those things aren't important; it's simply because I
am currently the only person working on Panda and it's a very, very big project.

Generics
--------

Generics are the only major missing language feature (as opposed to API) 
remaining for 1.0, but it's a big one. A lot of the groundwork has been laid, 
but finishing it up will not be a quick process. Panda's generics are going to 
be powerful enough to define things like the map and fold function on arrays in 
a completely generic fashion, so you can call e.g.

    (1 ... 5).map(x => x * 2.5)

and it will sort out that the lambda's type is `(Int)=>(Real)` and that 
therefore the result of the `map` call must be `Array<Real>`. The proposed
syntax for the `map` function on `ListView<T>` is:

    function <T2> map(fn:(T)=>(T2)):List<T2> {
        def result := new Array<T2>()
        for v in self
            result.append(fn(v))
        return result
    }

Of course, you don't actually need to know this; this is just what the 
`ListView<T>` interface will provide as the default implementation of the 
function. But hopefully it is instructive to see the syntax.

This is even more complex than it looks, because there are effectively thirteen
types supported internally by Panda: Int8, Int16, Int32, Int64, UInt8, UInt16,
UInt32, UInt64, Real32, Real64, Bit, Char, and Object. Naturally, the compiler
jumps through a lot of hoops to make it look like everything is an Object, but
internally that isn't the case. This means that this particular `map()` function
must be instantiated differently for different combinations of types, though
since all non-primitive Objects will be treated the same, the number of 
different implementations which actually get instantiated should be small
compared to the madness that happens with C++ templates.

Threading
---------

I *think* I'm happy with the overall thread model (communication via messages,
no shared mutable state). It definitely imposes some additional costs relative
to the good old fashioned "everything can access everything, deadlocks and 
unexpectedly broken data for everyone!" model, but I'm hoping once the APIs 
are fully fleshed out the safety and comprehensibility benefits will outweigh
the costs. Frankly, I'm still not quite 100% sure this will be the case; it's
possible I'll end up saying "screw it" and reintroduce class variables and all
that (Panda had them, once upon a time; some of the machinery is still present
in the compiler).

Assuming I stick with the current approach, there are still a lot of things that 
need work:

1. The current implementation of the threading system sucks. It was a very
    quick-and-dirty implementation to begin with, and then I found out that some
    of the things I was doing didn't play right with this particular garbage 
    collector, and then I found some other problems, and... well, you know how 
    it goes. It's a mess right now.
2. The API needs work. Creating new threads feels "heavier" than I would like it
    to; might be worth introducing a keyword or at least some kind of simpler
    syntax to spawn a new thread. There's also no way to select among multiple 
    MessageQueues, and that is *desperately* needed.
3. Threads are currently just operating system threads, which are very 
    heavyweight. I'd like to have a very low cost for threading, so we can 
    easily have tens of thousands of threads running. Might be worth considering
    multiplexing Panda threads onto the same OS thread, though of course that
    carries its own tradeoffs.
4. `Thread.context` has a lot of potential, but the current implementation isn't
    quite right. Basically, what I really want is a means of locking "global"
    variables, configuration settings, and so forth to a particular thread or
    group of threads. Obviously that isn't what we actually have at the moment,
    and even to the extent that we do have it, it's harder than it should be to
    work with. Unfortunately I feel like I'm orbiting around the right approach,
    occasionally catching glimpses of it, without ever quite solving the 
    fundamental problems.

Unicode
-------

Panda has some of the groundwork for Unicode support -- `Char` is 16 bits long, 
streams have both `Int8` and `Char` methods, etc., but no "real" Unicode support 
is actually present. Panda is currently just zero-extending bytes to make 
characters, and truncating characters to make bytes, which means it really only
works for ASCII characters. Of course I know this is not the right way to handle
things :-). It's just a temporary hack until I have time to implement proper
Unicode support, but that's a big job and we can still do a lot of interesting
things even with an ASCII-only Panda.

*Ethan's thoughts:* I still have some open questions about the best way to 
handle things. For instance, I am well aware that a 16-bit Char is not big 
enough to hold all Unicode characters; but extending it to get rid of surrogates 
doubles the storage costs and slows things down for relatively little gain. 
Furthermore, even if we get rid of surrogates by using a 32-bit char, we can't 
get rid of decomposed character sequences like LATIN SMALL LETTER A + 
COMBINING ACUTE ACCENT. If we already have to deal with the fact that character
sequences like this exist, are surrogates really that much worse? Doubling
storage costs is a *huge* deal, and it wouldn't actually fix things. How do we
handle the API issues caused by the fact that a "Char" isn't actually a "Char",
it's really just a UTF-16 code point? Is "Char" even the right name for the
type?

Of course, we could also internally store a String as something other than an
Array<Char>, but that comes with a whole host of its own problems. I really need
to perform a survey of how other languages are solving these issues. I suspect
there's really not a great solution to a lot of these issues, but I'm open to 
suggestions.

Nullable Numbers
----------------

Every non-`null` value in Panda is an object, even numbers like `12`. But for 
the sake of efficiency, Panda doesn't actually create a full-blown object 
instance unless it needs to. If you consider a statement like

    x += y

where `x` and `y` are `Int`s, this will compile to the same basic CPU math
instructions as it would under any other language; no actual objects need to
exist anywhere. Of course, when you do something like add a number to an
`Array<Object>` or call `processObject(o:Object)` with a number, Panda will end
up transparently creating an actual `Object` instance for the number, and that's
probably the best we can do there.

But there's an intermediate case, too: nullable numbers. If a function returns
`Int?`, we don't really need to create a full-blown `Object` instance for this:
we really only need one more bit of storage somewhere, so that we can 
distinguish between `null` and non-`null` numbers. Unfortunately the current
approach is simply to fall all the way back to creating actual `Object` 
instances. Even more unfortunately, there are a couple of spots where this 
actually creates major performance concerns: several common `String` operations, 
and byte-by-byte/char-by-char `InputStream` reading both use nullable numbers to
signal exceptional results, and I'm sure the sheer number of objects we are
creating is murder.

So by fixing nullable numbers to just be bigger (probably a struct consisting of
the number itself and an extra bit) and using that additional bit to distinguish 
`null` from non-`null`, we should be able to massively improve performance on
some common operations. On the Java side of things, we could similarly extend
the range of numbers smaller than `Int64` (using, say, a `short` to represent 
`Int8?`) to give us the extra bit we need; this would at least fix the problem
for integers 32 bits and smaller, which is the 99% use case.

Value Improvements
------------------

The `Value` class exists as a hint to the compiler that this object can be
passed by value, and it is ok to fold similar instances together into a single
object. The compiler is not currently performing either of these optimizations,
but when it does it should lead to a significant speed bost.

Memory Management
-----------------

Panda currently uses the Boehm-Demers-Weiser garbage collector to manage its
memory, and its approach to memory is... simplistic. "Just allocate everything
on the heap and let the collector sort it out" is refreshingly straightforward, 
but it's definitely not the smartest approach. Escape analysis, particularly
given Panda's approach towards functions, should allow a significant number of
allocations to end up on the stack instead of the heap. A concept of "wholly 
owned" objects (objects which are completely encapsulated inside of other 
objects and never visible to outside code) will allow objects to be merged 
together and allocated as a single unit, reducing load on the garbage collector. 

Furthermore, I have learned that despite all of the documentation claiming that 
the Boehm-Demers-Weiser garbage collector is purely a conservative collector, it 
actually *can* be used as an accurate GC! We need to switch to using
GC_gcj_malloc, which shouldn't be very difficult.

Finally, I'm not even 100% convinced that garbage collection is the right
overall approach. An early version of Panda used automatic reference counting as
its garbage collection algorithm; I've variously been tempted to go back to 
that or something else more predictable. Unfortunately, everything has its
downsides...

Better Debugging
----------------

Panda does not currently embed debug information in its executables, meaning you
can't get line numbers from its exceptions. It also does not catch stack 
overflows, meaning that they simply crash with a segfault. Obviously this needs
to get fixed, but it has been a surprisingly minor annoyance for me in practice: 
for the time being, one can simply recompile the offending program to run on the 
JVM, which does catch such errors and includes line numbers (though you have to
check the .java source to figure out where in the .panda file the error
corresponds to. That's something else that needs to get fixed!)

Reflection
----------

Reflection probably won't make it until post-1.0, but it's an obvious missing
feature.

Native use of Java objects
--------------------------

Currently, accessing Java objects from Panda requires jumping through a lot of
hoops. I'd like to simplify this, although the resulting program will obviously
then be JVM-only. Accessing Panda objects from Java, however, will likely
continue to be fairly difficult.

JavaScript Output
-----------------

The JavaScript output engine is already almost completely functional. With just
a bit more work, you'll be able to write a game in Panda and run it in a web
browser.

Resources
---------

The compiler will be able to embed files into the executable, sort of like
embedding resource files into a Java .jar file. (Well, exactly like that, when 
you're compiling to a .jar file...)

Proper Collection API
---------------------

Obviously Panda is eventually going to feature a full-fledged collection API, 
with `List`, `Set`, `Map`, and all the rest. This feature is blocked on 
A) generics, and B) making sure I'm completely happy with the design before I go
crazy and write something I don't like.

Better Regular Expression Syntax
--------------------------------

Panda sets aside the hash (`#`) character as a special kind of "quote" for what
are internally known as `plugin` values. The only such plugin currently is
regular expressions: if the "quoted" value starts ands ends with a slash (`/`),
the value is treated as a regular expression.

Plugins create a nice way to "gently" introduce experimental new syntax such as
regular expressions, but I'd like to make regular expressions first-class 
citizens in Panda source code. This means that you will be able to write:

    def pattern := /\d+/

instead of the current:
    
    def pattern := #/\d+/#

The only real difficulty here is that regular expressions have their own 
grammar, with their own tokens, which basically requires me to be able to 
"switch modes" during lexical analysis in order to process a different grammar. 
The good news is that it shouldn't be all that hard to do, and then we've got 
the general ability to embed other languages within Panda without too much fuss.

Potential Features Which Might Happen Eventually
================================================

Default Interface Implementations
---------------------------------

Enterprise software has shown us the importance of interfaces and pluggable
implementations, but I'm not convinced that it has shown us the best way to
implement these things. Something I'm considering for the future of Panda is
*default interface implementations*: basically, interfaces can define 
constructors, just as they do methods, and would be guaranteed that every class
implementing that interface would provide an implementation of that constructor.
Then you would be able to define in a context what the default implementation of
a given interface is, and simply create that interface as if it were a class:

    def m := new Map<String, Object>()

and actually end up with an instance of the default implementation of that
interface. In other words, no Factory classes -- just instantiate the interfaces
directly, and you can seamlessly switch out implementations at will.

Extensions
----------

I am considering a syntax to extend existing classes, similar to Objective C's 
categories. This would be a huge win in terms of keeping the core libraries
modular; much as I like the regular expression features in `String`, for 
example, I'd prefer to see them split out into a separate module (much as 
`panda.gl` is currently broken out) so we don't absolutely have to have a 
regular expression library in every Panda installation, and the same basic deal
for every "big" and not-strictly-necessary module currently included. The big
hesitation here is I'm not sure how well that can be accomplished on the JVM.

I'm not saying there isn't a great (possibly even an obvious) solution, but I
haven't spent much time thinking about it and my gut feel is that it's going to
be difficult to do right. Maybe I'm wrong.

Inner Classes
-------------

At some point I'll probably add inner classes, similar syntactically to Java's.
It's not as high of a priority as it was for Java, however, because Panda has 
first class functions and therefore does not have nearly the need for anonymous
inner classes. Even if it gains support for named inner classes, Panda will 
probably not offer anonymous inner classes at all: with tuples, first-class 
functions, lambdas, MessageQueues, and other powerful language features, there 
just isn't nearly as much need for them as there was in Java.

Multiple-Dimension Indexing
---------------------------

I am strongly considering extending the index and indexed-assignment operators
to accept multiple values, allowing you to write things like:

    dest[x, y] := src[x, y]

Syntactically, this is quite straightforward, and I could probably do the
implementation in an afternoon. The hesitation mainly comes from open questions
about interaction with other language features, such as the slice syntax.
Keeping slicing single-valued as it is now, forcing you to use tuples to specify
multi-dimensional slices, is a potential answer.

Potential Breaking Changes
==========================

It is not my intent to break the language in any major way... but I'd rather do
the right thing now than be stuck with the wrong approach forever due to
backwards compatibility concerns. So I'm going to make a note of a few things
which I'm not necessarily completely happy with as things stand and which may
change in the future; these will in general require only minor updates to 
existing programs.

Threading
---------

As discussed above, threading is a major candidate for breaking changes.

Interfaces
----------

I am considering requiring a `@default` annotation on default methods in
interfaces. There's no technical reason to require it, of course, but I view it
as similar to the `@override` annotation (which there is also no technical
reason to require): it might improve the quality and clarity of the code to
require it. Or it might not. For the time being, I chose not to require it.

Annotations
-----------

Eventually, I could see adding a general-purpose annotation system. This may
involve updating several of the current annotations which don't "follow the
rules", namely `@math(overflow)` (the token in parentheses is not an 
expression), `@post()` (comes after, rather than before, the thing it 
describes), and `@invariant()` (can appear anywhere in a class body).
`@math(overflow)` will almost certainly change, but I'm less certain about
`@post()` and `@invariant()` -- while they follow their own rules, I kind of
like not having to put them before the method / class they describe. 

Finalization
------------

I do not like Object.finalize. *At all*. It pretends to solve the problem of
cleaning up resources associated with objects, but does not actually do so;
allocating many finalizable objects in a loop will generally break things, 
because they are being allocated faster than they are being finalized and 
whatever native code cares about the object is likely to get upset about that.
Furthermore, such failures are far more likely to happen in the real world,
under heavy load, than they are during carefully-controlled QA testing. This is
bad.

So, I am trying to figure out an alternate approach. Java's try-with-resources /
C#'s using statement are potentially reasonable ways to handle things, probably
with objects that require closing generating a warning if they were destroyed
without being closed (I like that better than silently closing them at 
finalization time, because that tends to hide problems more than it does fix
them. We can have a debug compiler setting which embeds stack traces at 
creation time, to debug where the allocation is happening). Furthermore, the
compiler could easily catch most cases of failure-to-close things, because most
of the time such values will not have escaped and there will be no question that
the close didn't happen.

The only major issue with this is that whether or not an object needs
finalization could be an implementation detail: Matcher, for example, currently
requires closing (because it is backed by a native ICU regex) but will not in
the future (because I'm eventually going to have a Panda-native regex engine).
Some streams don't really require closing, either, such as MemoryOutputStream. 
So, finalization it is for right now, but I'm not happy about it and make no 
guarantees it will remain.

Error Handling
--------------

Panda's exception handling support in general is extremely minimal. I ended up
using Java's basic exception handling approach not because I'm convinced it's
unbelievably awesome, but rather because I haven't seen a compellingly better
way to do it. I haven't spent a tremendous amount of time on exception handling
because I'm not convinced it's the right way to go long-term. In particular,
Panda's `try` / `catch` mostly works (hopefully you didn't notice that it's only 
"mostly"!), but it doesn't support `finally` at all. 

Here are my major concerns:

1. Exception handling is unbelievably slow, particularly when you consider the
   time it takes to assemble stack traces. It's not a big deal when you only
   have exceptions for truly exceptional situations, but when it crops up during
   ordinary day-to-day usage of a program (say, hypothetically, during
   speculative compilation of a structure) it is a significant performance 
   drain.
2. finally is, in general, a terrible way to handle object cleanup. With a 
   better cleanup system as discussed above, the use cases for finally drop
   dramatically... I'm tempted to just leave it out and see how much people
   complain.