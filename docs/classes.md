Classes
=======

Every Panda value is an object, and therefore an instance of a class. Classes 
are defined using the syntax:

    class <name> [: <supertype>] {
        <bodyEntries>
    }

A `<bodyEntry>` is a [method](methods.html), [field](fields.html), 
[constant](constants.html), or [`@invariant`](annotations.html#invariant).

For instance, a simple class containing two fields:

    class Point {
        var x:Int
        var y:Int
    }

Because `Point` does not specify a supertype, it descends from 
`panda.core.Object`. Its two fields, `x` and `y`, are public by default (that
is, any other class is free to read and modify them).

You would create a new `Point` using [new](new.html) keyword, as in the 
expression `new Point()`. To create and configure a `Point`:

    var p := new Point()
    p.x := 5
    p.y := 7
    Console.writeLine("The point is: " + p.x + ", " + p.y)

Result: `The point is: 5, 7`

It would be more convenient to be able to create and initialize a `Point` in a
single step. We can define a special kind of method, a 
[`constructor`](constructors.html), to simplify the initialization:

    class Point {
        var x:Int
        var y:Int

        constructor(x:Int, y:Int) {
            self.x := x
            self.y := y
        }
    }

    var p := new Point(5, 7)

As shown above, the current object instance may be referred to by using the 
`self` [keyword](keywords.html).

Class Literals
--------------

Each Panda class is represented at runtime by an instance of the 
[Class](api/panda.core.Class.html) class. You may obtain a reference to this
`Class` instance at runtime using the syntax `class(<name>)`, e.g.:

    Console.writeLine(class(String).name)

Result: `panda.core.String`

Interfaces
----------

In addition to inheriting from one superclass, classes may also inherit from any
number of superinterfaces. The syntax for this is:

    class LotsOfInterfaces (Interface1, Interface2, Interface3) {
        ...
    }

If both a superclass and superinterfaces are being provided, the interface
declaration comes after the superclass declaration:

    class SuperclassAndSuperinterfaces : Superclass (Superinterface) {
        ...
    }

Each interface provides (generally abstract) methods, but no fields. See the
page on [interfaces](interfaces.html) for more information.