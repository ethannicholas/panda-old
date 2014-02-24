Constructors
============

A *constructor* is a special kind of [method](methods.html) which is used during 
[object creation](new.html). The syntax for constructors is:

    constructor(<parameters>) {
        <statements>
    }

Constructor parameters are defined just like method parameters, but unlike
normal methods, constructors do not have a name or return type. Constructors are
implicitly invoked when creating new objects. For instance, if we define a
`Point` class as follows:

    class Point {
        var x:Int
        var y:Int

        constructor(x:Int, y:Int) {
            self.x := x
            self.y := y
        }
    }

we can create a new `Point` as follows:

    new Point(5, 7)

This will create a new `Point` object and invoke its constructor with parameters
`5` and `7`.

Default Constructors
--------------------

If a class does not have any constructors defined, the compiler automatically
provides it with a *default constructor*. The default constructor looks like:

    constructor() {
    }

In other words, it is public, takes no parameters and does nothing. Defining any
other constructors will suppress the default constructor. You may wish to create
non-instantiable objects by defining:

    @private
    constructor() {
    }

Assuming this is the only constructor, no one other than the class itself can 
create an instance of it because its only constructor is private.

Calling Superclass Constructors
-------------------------------

Panda requires superclass constructors to be run before any code in a subclass'
constructor does. You may explicitly invoke a superclass constructor as the
first line of code in a constructor, using the syntax `super.constructor(...)`:

    class Point3D : Point {
        var z:Int

        constructor(x:Int, y:Int, z:Int) {
            super.constructor(x, y)
            self.z := z
        }
    }

If you do not explicitly invoke another constructor, Panda inserts an *implicit* 
call to the no-argument superclass constructor, exactly as if your constructor 
began with the line `super.constructor()`. If there is no no-argument superclass 
constructor, you must manually invoke one of its constructors or a compile-time 
error will occur.

Invoking Other Constructors
---------------------------

The syntax `constructor(...)` allows you to invoke other constructors from
within a constructor. Just as with invoking superclass constructors, calls to
other constructors must be the very first line of code in a constructor. For
example:

    class Point {
        var x:Int
        var y:Int

        constructor() {
            constructor(0, 0)
        }

        constructor(x:Int, y:Int) {
            self.x := x
            self.y := y
        }
    }

`Point` now has a no-argument constructor which invokes the `(Int, Int)`
constructor and passes it `(0, 0)`. As described above, the `(Int, Int)` 
constructor will make an implicit call to its superclass' (`Object`) no-argument 
constructor as its first action, but the no-argument `Point` constructor will 
not, because it is explicitly calling another constructor.

Constructors and Non-Nullability
--------------------------------

By the time a constructor is finished running, it must ensure that all 
[fields](fields.html) which do not have [default values](defaultValues.html)
have been initialized. It is an error to leave a field without a default value
uninitialized.

Safety Concerns
---------------

Calling instance methods from within a constructor is potentially dangerous;
these instance methods can then "see" the object in a partially-constructed 
state, which can include non-nullable fields not having been initialized yet.
Referring to uninitialized fields during construction causes undefined behavior.

Future versions of Panda may tighten up this behavior.