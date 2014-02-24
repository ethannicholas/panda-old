Inline Methods
==============

In addition to defining [methods](methods.html) as members of a 
[class](classes.html), you may use *inline methods* in 
[expressions](expressions.html):

    table.setFormatter(function(node:Node):String {
        return node.id + " (" + node.children.count + ")"
    })

Inline methods are defined very similarly to normal class member functions. They
may be either methods or [functions](functions.html), but they do not have names 
or annotations. Methods are a first-class [type](types.html) in Panda, meaning 
that you may store methods in variables, return them from methods, create arrays 
of methods, and otherwise treat them as you would any other Panda value.

Methods defined inside of another method may access any visible local variables,
but those variables must be *effectively static*. In other words, it must not be
possible for those variables to change after the point at which they become
visible to the inline method.

**IMPLEMENTATION NOTE**: Methods can't actually capture values yet; closures
aren't implemented. Coming soon!

See [method types](types.html#methodTypes) for how to describe the 
[type](type.html) of a method.

<a name="lambdas"></a>
Lambdas
-------

In addition to the full form shown above, a shorthand syntax exists to create
functions which simply return an expression:

    x:Real => x * x

This is equivalent to the inline function:

    function(x:Real):Real {
        return x * x
    }

This form of expression is known as a lambda, after the 
[lambda calculus](http://en.wikipedia.org/wiki/Lambda_calculus), but "short
form of a function" is really all you need to understand. If a lambda expression
has more than one parameter, the parameters must be surrounded by parentheses:

    (x:Real, y:Real) => (x ^ 2 + y ^ 2).sqrt

If the lambda is being used in a context where its type can be inferred (such as
a call to a method which expects a particular type of method or an assignment to
a variable or field with a method type), you may omit the parameter types:

    var distance:(Point, Point)=>(Real) := 
            (p1, p2) => ((p1.x - p2.x) ^ 2 + (p1.y - p2.y) ^ 2).sqrt

Lambdas are always functions; they may not have side effects and there is no
equivalent "method form" of a lambda. If you must define an inline method, use
the full syntax described above.