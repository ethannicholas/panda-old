Classes
=======

A *class* in Panda represents a kind of *object*. An object is a value 
containing [fields](fields.html) (data values) and [methods](methods.html) 
(actions). Every Panda value other than [`null`](null.html) is an object, and 
therefore an instance of a class. Classes are defined using the syntax:

@SOURCE(
    class -*REPLACE:<name>*-name -*REPLACE:[*- : -*REPLACE:<superclass>]*-Object {
        -*REPLACE:<bodyEntries>*-var -*REPLACE:*-x-*REPLACE:*-:-*REPLACE:*-Int
    }
)

A `<bodyEntry>` is a [method](methods.html), [field](fields.html), 
[constant](constants.html), or [`@invariant`](annotations.html#invariant).

For instance, a simple class containing two fields:

@SOURCE(
    class Point : Immutable {
        def x:Int
        def y:Int

        init(x:Int, y:Int) {
            self.x := x
            self.y := y
        }
    }
)

Because `Point` does not specify a supertype, it descends from 
`panda.core.Object`. Its two fields, `x` and `y`, are public by default (that
is, any other class is free to read and modify them).

You would create a new `Point` by referencing the name of the class followed by
the parameters to its `init` method, as follows:

@SOURCE(
    class Point {
        def x:Int
        def y:Int

        init(x:Int, y:Int) {
            self.x := x
            self.y := y
        }
    }
    --BEGIN
    def p := new Point(5, 7)
    Console.writeLine("The point is: \{p.x}, \{p.y}")
)

Result: 
    
    The point is: 5, 7

Inheritance
-----------

Classes may *inherit* from another class to extend or modify the parent class'
behavior. In the real world, we might say that the Human class extends the
Primate class, which in turn extends the Mammal class, and so forth. At each 
step, we add new traits which specialize the class further. We could express 
this concept in Panda as follows:

@SOURCE(
    class Mammal : -*REPLACE:Vertebrate*-Object {
        -*REPLACE:...*---dummy comment
    }

    class Primate : Mammal {
        -*REPLACE:...*---dummy comment
    }

    class Human : Primate {
        -*REPLACE:...*---dummy comment
    }
)

Each child class (subclass) inherits all of the fields and methods from its
parent class (superclass), and may be used anywhere the parent class is 
expected (that is, all `Human` objects are also `Mammal` objects). Subclasses
may add additional fields and methods, as well as override (replace) methods
inherited from their parent classes.

All classes ultimately inherit from 
[`panda.core.Object`](api/panda/core/Object.html). If you do not specify a 
superclass, the superclass defaults to `Object`.

Class Literals
--------------

Each Panda class is represented at runtime by an instance of the 
[Class](api/panda/core/Class.html) class. You may obtain a reference to this
`Class` instance using the class' name in an expression, e.g.:

@SOURCE(
    Console.writeLine(String)
)

Result: 
    
    class panda.core.String

Implementing Interfaces
-----------------------

In addition to inheriting from one superclass, classes may also inherit from any
number of superinterfaces. The syntax for this is:

@SOURCE(
    interface Interface1 { }
    interface Interface2 { }
    interface Interface3 { }
    --BEGIN
    class LotsOfInterfaces (Interface1, Interface2, Interface3) {
        -*REPLACE:...*---dummy comment
    }
)

If both a superclass and superinterfaces are being provided, the interface
declaration comes after the superclass declaration:

@SOURCE(
    class Superclass { }
    interface Superinterface { }
    --BEGIN
    class SuperclassAndSuperinterfaces : Superclass (Superinterface) {
        -*REPLACE:...*---dummy comment
    }
)

Each interface provides (generally abstract) methods, but no fields. See the
page on [interfaces](interfaces.html) for more information.

Generic Classes
---------------

See the page on [generics](generics.html) for information on generic classes.

Nested Classes
--------------

Panda allows you to nest class or [choice](choices.html) definitions inside of
other classes, e.g.:

@SOURCE(
    class Monster {
        choice Element {
            FIRE,
            WATER,
            EARTH,
            AIR,
            UNALIGNED
        }

        def element:Element

        init(element:Element) {
            self.element := element
        }
    }

    def redDragon := Monster(Monster.Element.FIRE)
)

Other than their scope, nested classes are exactly the same as top-level 
classes. This means that a nested class can be created without an instance of
its containing class and is in all other ways "independent" of its containing
class.