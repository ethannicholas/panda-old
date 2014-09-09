Interfaces
==========

An interface is a special kind of class which only has [methods](methods.html)
and [constants](constants.html), but no [variables](variables.html) or
[defines](defines.html). A [class](classes.html) may only have one superclass, 
but it may have any number of superinterfaces. Interfaces are defined much like 
classes, but with the `interface` keyword and abstract-by-default methods:

@SOURCE(
    interface Example {
        method exampleMethod(s:String):Bit
    }
)

Classes list all the interfaces they implement in a comma-separated, 
parenthesized list after their supertype declaration:

@SOURCE(
    class FooSuper { }
    interface Example { method exampleMethod(s:String):Bit { return true } }
    --BEGIN
    class Foo : FooSuper (Example) {
        @override
        method exampleMethod(s:String):Bit {
            -*REPLACE:...*---dummy comment
            return true --SKIP
        }
    }
)

In addition to all the types `Foo` could normally be used as (itself, 
`FooSuper`, `Object`, etc.), `Foo` is also an instance of `Example` and may be
used wherever an `Example` is required.

Interfaces may themselves have superinterfaces:

@SOURCE(
    interface Example {
        method exampleMethod(s:String):Bit
    }

    interface BetterExample : Example {
        method betterExampleMethod(s:String, o:Object)
    }
)

Interfaces may even inherit from more than one parent interface:

@SOURCE(
    interface BetterExample { }
    interface AnotherInterface { }
    interface AndAThird { }
    --BEGIN
    interface MultipleParents : BetterExample, AnotherInterface, AndAThird {
        -*REPLACE:...*---dummy comment
    }
)

Default Methods
---------------

All methods in an interface are abstract by default. You may provide an 
implementation of an interface method in order to create a *default method*:

@SOURCE(
    interface Example {
        method exampleMethod(s:String):Bit

        method defaultMethod() {
            Console.writeLine("this method has an implementation!")
        }
    }
)

A default method will be inherited by a class implementing this interface, but
if two or more interfaces provide a method with the same signature, the 
interface listed first "wins" and its implementation will be used in preference
to interfaces listed later. For example, given the code:

@SOURCE(
    interface Example1 {
        method exampleMethod(s:String):Bit

        method defaultMethod() {
            Console.writeLine("this method has an implementation!")
        }
    }

    interface Example2 {
        function someOtherMethod(r:Real64):Real64

        method defaultMethod() {
            Console.writeLine("this method also has an implementation!")
        }
    }    

    class Foo (Example2, Example1) {
        @override
        method exampleMethod(s:String):Bit {
            -*REPLACE:...*---dummy comment
            return true --SKIP
        }

        @override
        function someOtherMethod(r:Real64):Real64 {
            -*REPLACE:...*---dummy comment
            return 0 --SKIP
        }
    }
)

The statement `new Foo().defaultMethod()` will result in the output
`"this method also has an implementation!"`. `defaultMethod()` is present in
both `Example1` and `Example1`, but as class Foo lists `Example2` first, that
interface's implementation of `defaultMethod()` will be inherited.

It is possible for two interfaces to conflict, for instance to both define
methods with the same signature but different return types. In this case it is
impossible to implement both interfaces in the same class and attempting to do
so will result in a compile-time error.