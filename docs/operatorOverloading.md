Operator Overloading
====================

Panda classes may provide their own implementations of 
[operators](operators.html), which is called *operator overloading*.

    -- this won't compile, keep reading!
    class OperatorExample {
        var value:Int

        constructor(value:Int) {
            self.value := value
        }

        @class
        method main() {
            var a := new OperatorExample(12)
            var b := new OperatorExample(16)
            Console.writeLine(a + b)
        }
    }

If you attempt to compile this class, it will fail with the message `'+' cannot 
operate on OperatorExample, OperatorExample`, because Panda does not know how to
add two `OperatorExample`s together.

We can tell Panda how to add these objects together by providing an 
implementation of the `+` operator. There are two ways to do this, either as an
instance method with one parameter:

    function +(right:OperatorExample):OperatorExample {
        return new OperatorExample(value + right.value)
    }

or a class method with two parameters:

    @class
    function +(left:OperatorExample, right:OperatorExample):OperatorExample {
        return new OperatorExample(left.value + right.value)
    }

These two [functions](functions.html) are equivalent. The instance method 
operates on [self](self.html) and its single parameter, while the 
[class method](annotations.html#class) receives two parameters. If you define 
either of these two functions and recompile the example, it will now run and 
produce output similar to:

    OperatorExample<37027776>

The overloaded `+` operator ran successfully, returning a new `OperatorExample`
object, and this is the default output from `Object`'s 
[convert-to-`String`](operators.html#convert) function, showing the name of the
class and its `hash`. With a more useful implementation of the convert operator, 
the complete example becomes:

    class OperatorExample {
        var value:Int

        constructor(value:Int) {
            self.value := value
        }

        function +(right:OperatorExample):OperatorExample {
            return new OperatorExample(value + right.value)
        }
        
        @override
        function ->>():String {
            return "Overloaded: " + value
        }

        @class
        method main() {
            var a := new OperatorExample(12)
            var b := new OperatorExample(16)
            Console.writeLine(a + b)
        }
    }

Result: `Overloaded: 28`

Any binary operator can be overloaded simply by providing a function that 
accepts the left and right operands; either explicitly as a `@class` method with
two parameters, or as a one-parameter instance method with `self` implicitly 
representing the left operand. When the left and right operands are different 
classes, both classes will be checked for appropriate functions.

Unary operators (such as logical not (`!`) or convert (`->>`)) require only a 
single parameter. Just as with binary operators, unary operators may be 
implemented as instance methods (in which case `self` is the implicit parameter)
or as class methods taking an explicit parameter.

Convert
-------

The convert operator (`->>`) is unique among all Panda methods, in that 
conversion is the only situation in which the return type of a method is 
considered during method lookup. Given two functions:

    function ->>():String {
        ...
    }

    function ->>():Int {
        ...
    }

these two methods are not considered to conflict, despite the fact that they
have the same name and the same parameters, because converters can be 
distinguished by return type. Again, this is only true of converters; any other
methods with the same name and parameters would be considered duplicates and
therefore an error.

Index
-----

The index (`[]`) and indexed assignment (`[]:=`) operators are also 
overloadable, allowing other classes to be indexed in the same fashion as 
arrays. Example:

    class Bits {
        @private
        var bits:Int64

        method [](index:Int):Bit {
            return (bits >> index && 1) != 0
        }

        method []:=(index:Int, value:Bit) {
            if value
                bits ||= 1 << index
            else
                bits &&= !!(1 << index)
        }
    }

This class presents an `Int64` value as if it were an array of 64 `Bit` values, 
allowing you to get and set them individually.

Slice
-----

The three parameters for the slice (`[..]`) operator are called *start*, *end*, 
and *step*. A fully-qualified slice operator is expressed as 
`[start .. end by step]`, but all three parts are optional. Method lookup 
follows these rules:

1. If none of the three parameters are specified, a zero-parameter slice method 
    will be checked for
2. If the *end* and *step* parameters are not specified, a single-parameter 
    method taking only *start* will be checked for. If *start* is not specified,
    it defaults to `null`.
3. If the *step* parameter is not specified, a two-parameter method taking 
    *start* and *end* will be checked for. If either is not specified, they
    default to `null`.
4. A three-parameter method taking *start*, *end*, and *step* will be checked 
    for. *step* will default to `1` if not specified, and *start* and *end* each
    default to `null`.

If none of these methods are found, an error is raised.

Note that:

* The *start*, *end*, and *step* may be of any type so long as there is a 
  matching method. There may be multiple overloaded versions of each kind (for
  instance, you could define both `[..](start:Int)` and `[..](start:Real)`).
* *step* will never be [null](null.html), so you may not define it as a nullable 
  type.
* The simplest (but not most efficient) way to implement slice is to just 
  implement the three-parameter function with the *start* and *end* parameters
  nullable, as this will handle all combinations of present/omitted parameters.
* For efficiency, you may wish to define more than one of these variants. For
  instance, `String` defines both `[..](start:Int, end:Int)` and 
  `[..](start:Int?, end:Int?)` (among other variants) because it can handle 
  `Int` more efficiently than `Int?`.
* You can require the `start` and/or `end` values to be specified by not
  defining slice functions taking nullable values
* You can disallow the step (the `by <expression>`) clause by not defining a
  three-parameter slice function.

Overloading sliced assignment (`[..]:=`) works the same, except that an
additional parameter (the value to assign) will be present, so the method will
take one to four parameters instead of zero to three.

Properties
----------

[Property](properties.html) setters are implemented using operator overloading.
If you define a single-parameter instance method whose name ends in `:=`, that
method may be invoked via an assignment statement, as follows:

    class Example {
        method property:=(msg:String) {
            Console.writeLine("You have set the property to: {0}", msg)
        }
    }

    var e := new Example()
    e.property := "Overloaded assignment!"

Result: `You have set the property to: Overloaded assignment!`

The line `e.property := "Overloaded assignment!"` is actually invoking a method,
despite looking like a standard assignment.