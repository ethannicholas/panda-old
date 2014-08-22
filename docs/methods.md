Methods
=======

    method <name>(<parameters>)[:<return>] {
        <statements>
    }

A method is a [named](identifiers.html) block of code which can be invoked by 
*calling* the method. Methods take zero or more *parameters*, which are values 
passed in to the method that it can reference as if they were local variables. 
Each parameter is a name, a colon (`:`), and a [type](types.html), and multiple 
parameters are separated by a comma (`,`). Methods may *return* a value, which 
becomes the value of the method call expression.

Example:

    method sayHello(firstName:String, lastName:String) {
        Console.writeLine("Hello, {0} {1}!", firstName, lastName)
    }

This defines a method named `sayHello`, which takes a single parameter `name` of
type `String`. When called (such as by `sayHello("Panda")`), the statements
within the method will be executed, in this case invoking the 
`Console.writeLine` method to display the text `Hello, Panda!`.

To return a value from a method, first give the method a return type and then
use `return <value>` from within the method:

    method square(x:Real):Real {
        return x * x
    }

This defines a method which returns a `Real` equal to its parameter squared.

<a name="annotations"></a>
Annotations
-----------

The following [annotations](annotations.html) are legal on methods:

* [`@private`](annotations.html#private)
* [`@protected`](annotations.html#protected)
* [`@class`](annotations.html#class)
* [`@abstract`](annotations.html#abstract)
* [`@static`](annotations.html#static)
* [`@override`](annotations.html#override)
* [`@math(overflow)`](annotations.html#overflow)
* [`@pre(...)`](annotations.html#pre)
* [`@preOr(...)`](annotations.html#preOr)
* [`@post(...)`](annotations.html#post) (after the method body)
* [`@postAnd(...)`](annotations.html#post) (after the method body)

<a name="variableParameters"></a>
Variable Parameters
-------------------

By default, method parameters behave as [defines](defines.html); that is, the
object the method parameter refers to may be modified, but the parameter may not
be reassigned to point to a different object.

    method example(param:MutableString) {
        param.append("this works!") -- legal!
        param := new MutableString("this doesn't!") -- illegal, won't compile
    }

The `var` keyword turns a method parameter into an ordinary variable, which may
then be freely modified:

    method countDown(var i:Int) {
        while i > 0 {
            Console.writeLine(i)
            i -= 1
        }
    }

Variable method parameters are treated as ordinary local variables, and 
reassigning the variable does not affect anything outside of the method itself.

<a name="convertParameters"></a>
Convert Parameters
------------------

Method parameters are normally a name, a colon (`:`), and a type, such as 
`s:String`. If you use the [convert operator (`->>`)](operators.html#convert)
instead of the colon, as in:

    method append(s->>String) {
        ...
    }

`s` becomes a "convert parameter", which will perform an automatic conversion of
the method parameter to `String`. For instance, `append(123)` is equivalent to
`append(123->>String)`. Convert parameters are particularly useful where 
`String`s are required, because every [non-nullable](nonNullability.html) type 
can be converted to `String`: `Console.writeLine()` and `MutableString.append()` 
are good examples of methods in the core library using convert parameters. This 
allows you to call these methods with *any* non-nullable type and have the 
parameter automatically be converted as required.

<a name="varargs"></a>
Variadic Methods
----------------

Methods may accept a variable number of parameters (*variable arity* or 
*variadic* methods). See [variadic methods](variadic.html) for details.

self
----

Within an instance method (including [functions](functions.html) and 
[constructors](constructors.html)), you may refer to the object on which the
method is running using the `self` [keyword](keywords.html).

Overriding Methods
------------------

Methods present in a superclass may be overridden by similarly-named and -typed
methods present in a subclass. For instance, given:

    class Super {
        method performFoo() {
            Console.writeLine("superclass method!")
        }
    }

You may provide a different implementation of the method in a subclass:

    class Sub : Super {
        @override
        method performFoo() {
            Console.writeLine("subclass method!")
        }
    }

The fact that the subclass method has the same name and parameters means it will 
be called instead of its superclass equivalent when the object is of type `Sub`.
The required `@override` annotation prevents you from accidentally overriding
superclass methods without realizing it.

Whenever the `performFoo` method is called, the right implementation of the
method will be selected at runtime based on the class of the object:

    var object := new Super()
    object.performFoo() -- displays "superclass method!"
    object := new Sub()
    object.performFoo() -- displays "subclass method!"

All parameter types of an override method must match exactly (including 
[nullability](nonNullability.html)), but the return type of an override method
may be different so long as it is [implicitly castable](implicitCasting.html) to
the superclass method's return type.

Calling superclass methods
--------------------------

When you have overridden a method, you may find yourself needing to call the
superclass' version of the method. For instance,

    class Text {
        method paint() {
            ...
        }
    }

    class UnderlinedText : Text {
        method paint() {
            ...
        }
    }

We would like to have `UnderlinedText` do whatever drawing `Text` does, and then
draw a line under the text. We can do this with the syntax `super.paint()`:

    class UnderlinedText : Text {
        method paint() {
            super.paint()
            drawUnderline()
        }
    }

The syntax `super.paint()` means "call the version of the method present in my
superclass", in this case Text.paint().

Method Values
-------------

Methods and functions are *first-class* values in Panda, meaning that they can
be stored in variables, passed into and returned from methods, and otherwise be
used as any other value would be. There are three ways to use a method as a
value:

[Inline methods](inlineMethods.html), such as:

    process(method() {
        Console.writeLine("in the process method!")
    })

[Lambdas](inlineMethods.html#lambdas), such as:
    
    list.fold((x, y) => x + y)

[Method References](methodReferences.html), such as:

    call(Widget::process(Sprocket))