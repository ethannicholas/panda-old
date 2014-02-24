Properties
==========

A `property` is a value of an object which can be accessed just like a 
[field](fields.html), but which uses a [function](functions.html) for getting 
its value and a [method](methods.html) for setting its value. There are many 
advantages of properties, such as:

1. The ability to perform additional actions when a property is set
2. The ability to compute property values at runtime, without having to store
   them in the object
3. The ability to override property behaviors by subclassing.

Of course, invoking functions and methods is slower than simply reading or
writing a field, so you do pay a (very small) price for this additional power
and flexibility.

Manual Properties
-----------------

To manually create a property in an object, you need a *getter* and/or a 
*setter* for the property. The getter is a no-argument function which returns
the property's value, such as:

    function height():Int {
        return layout.heights[self]
    }

Because a no-argument function can be invoked without parentheses, you can 
access this property as if it were a field:

    Console.writeLine(object.height)

The setter is a special kind of [operator overload](operatorOverloading.html)
which overloads assignment to the property:

    method height:=(height:Int) {
        layout.heights[self] := height
    }

And again, this setter can be invoked exactly like it were a field:

    object.height := 100

Compound assignment works as well, first calling the getter to get the current
value and then the setter to apply the new value:

    object.height += delta

It is also possible to combine a setter and a field, such that the field is used 
for reading and the setter is used for writing. In this case you must mark the
field as [`@readonly`](annotations.html#readonly) so that assignment is
unambiguous:

    @readonly
    var height:Int

    method height:=(height:Int) {
        self.height := height
        Console.writeLine("{}.height is now: {}", self, height)
    }

Automatic Properties
--------------------

An *automatic property* is just like the manual properties described above,
except you let the compiler write the code for you. In the simplest case, define
a property using the same syntax as a field, but using the `property` keyword
instead of `var`:

    property height:Int

This does three things:

1. Creates an instance field to hold the property's value. The instance field is
   named the same as the property, but with a leading underscore (in this case
   `_height`).
2. Creates a getter function which returns the value of the instance field,
   assuming that no manually-defined getter exists elsewhere in the class.
3. Creates a setter function which returns the value of the instance field,
   assuming that the property is writable and no manually-defined setter exists 
   elsewhere in the class.

For the simple case of `property height:Int`, this is equivalent to the 
following declarations:

    var _height:Int

    function height():Int {
        return _height
    }

    method height:=(height:Int) {
        self._height := height
    }

If you want to provide your own getters and setters instead of the defaults, 
simply define them:

    property height:Int

    method height:=(height:Int) {
        self._height := height
        Console.writeLine("{}.height is now: {}", self, height)
    }

This will still create the field and the getter, but the property will notice
the existing setter and use that instead of an automatically-created one. If the
property declaration doesn't end up creating either a getter or a setter, you
will receive a warning like this:

    class Test : Immutable {
        property p:Int

        function p():Int {
            return 5
        }
    }

    > pandac Test.panda
    warning: Test.panda:2:9: property 'p' had neither a getter or a setter created for it:
        getter not created because an explicit getter was defined at Test.panda:4:9
        setter not created because 'Test' is immutable
    This declaration is therefore equivalent to 'var _p:panda.core.Int32'
    1 warning

This is explaining that the property declaration didn't actually do anything
beyond what a basic `var` declaration would have. You created a manual getter, 
so you were probably expecting the synthetic getter to not get created. But
perhaps you didn't think about the fact that `Test` is declared immutable, and
therefore the property `p` must be read-only.

The getters and setters created by a property are allowed to implement abstract
methods (such as interface methods), but may not override concrete methods. For
instance, this is legal:

    interface Shape {
        function centerX():Real

        function centerY():Real
    }

    class Circle (Shape) {
        property centerX:Real

        property centerY:Real

        ...
    }

The getters created by the two properties in `Circle` match the signatures of
the abstract functions inherited from `Shape`, and so they are automatically 
marked `@override` and treated as the implementations of these functions. 
However, this is not legal:

    class Super {
        property x:String
    }

    class Sub : Super {
        property x:String -- compile error!
    }

The property created in the subclass will attempt to create a getter and a 
setter, but a getter and setter with that name already exist due to the 
duplicate property declaration in the superclass, and the compiler will reject 
this as invalid.