Annotations
===========

Annotations are special tokens attached to [classes](classes.html), 
[fields](fields.html), or [methods](methods.html). These special tokens describe
additional information about the entities they are attached to. Annotations
come directly before the entity they describe, as in:

@SOURCE(
    @protected
    @pre(!closed)
    method sayHello() {
        -*REPLACE:...*---dummy comment
    }
    --END
    function closed():Bit {
        return true
    }
)

The only exception to this is are `@post(...)` and `@postAnd(...)` annotations,
which appear immediately *after* the method they describe, and 
`@invariant(...)`, which appears within its containing class at the same level
as methods and fields.

<a name="protected"></a>
@protected
----------

The `@protected` annotation is legal only on fields. Protected fields may only
be accessed by the class that contains them, or subclasses of that class. For
instance, in:

@SOURCE(
    class A {
        @protected
        var a:Int
    }

    class B : A {
        -*REPLACE:...*---dummy comment
    }

    class C {
        -*REPLACE:...*---dummy comment
    }
)

Code present in class `B` would be permitted to access field `a`, because the
field is marked `@protected` and class `B` is a subclass of class `A`. The
unrelated class `C` would not be permitted to access field `a` of any instances
of class `A`.

<a name="private"></a>
@private
--------

`@private` may be applied to fields and methods. Fields and methods with this
annotation may only be accessed from within the same compilation unit.

<a name="class"></a>
@class
------

`@class` methods belong to the class as a whole, rather than any single instance 
of the class. In the code:

@SOURCE(
    class ClassExample {
        var x:Int

        @class
        method classMethod() {
            -*REPLACE:...*---dummy comment
        }
    }
)

the method `classMethod()` belongs to the class. Within the class, the simple
method name (`classMethod()` in the example above) can be used, but outside of 
the class the method must be qualified with the class name 
(`ClassExample.classMethod()`). From the context of the above class method, the 
simple name `x` is meaningless: `x` is a field of individual `ClassExample`
instances, not the class as a whole.

<a name="thread"></a>
@thread
-------

`@thread` fields are shared on a per-[thread](threads.html) basis. Each thread
"sees" a different copy of the field. If the field has an initial value, this
initialization expression is evaluated the first time that a given thread
references the field.

<a name="abstract"></a>
@abstract
---------

`@abstract` may be applied to classes or to fields.

An *abstract class* may not be instantiated. Abstract classes are often 
incomplete, and rely on subclasses to fill in their missing functionality.

*Abstract methods* are methods which do not have an implementation. They just 
have a method signature, with no method body, meaning that they are declared 
like:

@SOURCE(
    @abstract
    method abstractExample(s:String):Int
)
    
Abstract methods may only appear within abstract classes. If you subclass an
abstract class, you must either override all of its abstract methods (with 
non-abstract methods) or mark the subclass abstract as well.

<a name="override"></a>
@override
---------

A subclass can *override* its superclass' methods by defining methods with the
same name and parameters; instances of the subclass will then call the 
overriding method whenever the superclass method would have been called.

Overriding methods must have the `@override` annotation.

<a name="final"></a>
@final
-------

The `@final` annotation generally means "unchanging", but has slightly different
meanings depending on what is being annotated.

A *final field* is one that never changes. It must be assigned by the time the 
object is fully constructed, and cannot be modified after it is assigned. The 
object the field points to might still be modifiable, but the field cannot be 
changed to point to a different object. In other words, if you assign a 
`Monster` to a final field, the `Monster` itself remains modifiable - its 
health may go up or down, it might be poisoned or killed - but the field cannot 
be made to point to a different `Monster`.

A *final method* is one that cannot be overridden in subclasses. This may make
calls to the method faster, by avoiding virtual method lookup and by enabling
additional optimizations, and it gives you a greater measure of control over how
your classes are extended.

A *final class* is one that cannot be subclassed. `String` and a number of 
other important classes in the Panda core libraries are marked final, which 
both guarantees consistent behavior and improves performance for very 
commonly-used classes.

<a name="readonly"></a>
@readonly
---------

`@readonly` is only valid on fields. A readonly field may not modified outside 
of its containing class. The class which contains the field may still modify it 
at will. The object pointed to by the field (assuming it is mutable) may be
freely modified; only the field itself cannot be assigned to. In other words,
given:

@SOURCE(
    class dummy { --SKIP---
    @readonly
    var values := [1, 6, 14]
    } --SKIP---
)

The statement `object.values.append(76)` is legal, but the statement 
`object.values := [182]` is not legal from outside of the class containing this
field.

<a name="override"></a>
@override
---------

`@override` marks a method as overriding the equivalent method in a superclass. 
The `@override` annotation is required as safety feature, to prevent accidental
overrides and catch situations where you have failed to properly override a
parent method.

<a name="overflow"></a>
@math(overflow)
---------------

If a method is marked `@math(overflow)`, arithmetic operations within the method
overflow silently instead of generating errors or undefined behavior. This 
annotation is particularly common on implementations of the `hash` method, which
often rely on arithmetic overflow.

<a name="pre"></a>
@pre(&lt;expression>)
---------------------

Establishes a precondition on a method (an expression that must evaluate to true
for the method invocation to be valid). For example, a method that calculates a
square root might use `@pre(x >= 0)` to indicate that it cannot handle square
roots of negative numbers.

A method may have multiple `@pre(...)` annotations attached to it; the 
conditions of all `@pre(...)` annotations must be met.

Violating a precondition (when safety checks are enabled) causes a `SafetyError`
to be thrown. Violating a precondition when safety checks are disabled is
undefined behavior.

<a name="preOr"></a>
@preOr(&lt;expression>)
-----------------------

Weakens (expands) a precondition of an overridden method. A call to the method
is valid if *any* of the `@pre` or `@preOr` expressions evaluate to true. The 
only difference is that `@pre` is used for non-`@override` methods, and `@preOr`
is used for `@override` methods.

If multiple `@pre(...)` or `@preOr(...)` annotations are attached to the same
method, all of those conditions must hold. If a method is overridden, *either*
all of its `@pre(...)` annotations must hold, *or* all of the overriding 
method's `@preOr(...)` annotations must hold.

<a name="post"></a>
@post(&lt;expression>)
----------------------

Establishes a postcondition on a method (an expression that must evaluate to 
true when exiting the method). Unlike all other annotations, `@post(...)` (and
the corresponding `@postAnd(...)` appear *after* the method definition.

Postconditions are used to ensure that the method has done its job properly by 
double-checking the results. Within an `@post()` expression, two special kinds 
of expressions are supported:

`@return` - whatever value the method returned
`@pre(<expression>)` - what the expression was equal to before the method was 
entered

For instance, suppose we have this simple method:

@SOURCE(
    function list():Array<Object> { unreachable } --SKIP
    method add(value:Object) {
        list.append(value)
    }
    @post(list.length = @pre(list.length + 1))
)

The postcondition on this method ensures that the list is in fact one element
longer when the method finishes. Of course, it probably isn't worth using a 
postcondition like this where it is patently obvious that the method is behaving
correctly, but for more complex situations postconditions can turn 
difficult-to-find problems into obvious failures. It is legal to attach multiple
`@post(...)` annotations to a method; the method must fulfill all of its
`@post(...)` obligations.

Violating a postcondition causes a `SafetyError` to be thrown when safety checks
are enabled, and causes undefined behavior when they are not.

<a name="postAnd"></a>
@postAnd(&lt;expression>)
-------------------------

Strengthens a postcondition found in an overridden method. A method must fulfill
all of its `@post` and `@postAnd` conditions.

<a name="invariant"></a>
@invariant(&lt;expression>)
---------------------------

Used within a class body to establish an invariant, an expression which must 
always be true. In practice, this is equivalent to adding a postcondition to 
every method in the class.

<a name="limited"></a>
@limited
--------

Used on a method to indicate that the method only modifies the containing
object, objects it *wholly owns* (objects are objects which are never visible 
outside of the containing object), or its parameters.

Because of these restrictions, methods marked `@limited` may safely be used from 
[functions](functions.html), as long as the object the method is being called on
was created within the function and is not visible from outside the function,
and any mutable parameters are similarly only visible from within the function.

IMPLEMENTATION NOTE: currently, the compiler "takes your word for it" with 
@limited: it trusts that you are adhering to the restrictions and does not 
detect violations of this policy. This will change in the future.

<a name="self"></a>
@self
-----

Similar to `@limited`, but indicates that the method only modifies its 
containing object (not any of its parameters).

IMPLEMENTATION NOTE: currently, the compiler "takes your word for it" with 
@self: it trusts that you are adhering to the restrictions and does not 
detect violations of this policy. This will change in the future. Also, 
constructors are currently *assumed* to be @self (the vast majority of them are,
in practice) - in the future, they will be safety-checked and automatically 
marked @self / @limited if appropriate (unlike normal methods, they cannot be
inherited, so auto-marking is safe).

<a name="safeReturn"></a>
@safeReturn
-----------

Indicates that there are no references to the return value of a method when the
method exits; in other words, the method's return value was either created
within the method, is the result of another `@safeReturn` method, or is a 
private field which has never at any point been visible, and no persistent 
references to the value have been created within the method call. 

This is important to allow functions to operate on values returned from other 
methods: without a `@safeReturn` annotation, the compiler must assume that any 
mutable value returned from any method is potentially visible and therefore 
cannot be modified.

IMPLEMENTATION NOTE: currently, the compiler "takes your word for it" with 
@safeReturn: it trusts that you are adhering to the restrictions and does not 
detect violations of this policy. This will change in the future.

<a name="unsafeFunction"></a>a>
@unsafeFunction
---------------

Indicates that a [function](functions.html) performs prohibited operations.
Unsafe functions are allowed to call methods, modify variables, and otherwise 
modify state, and the `@unsafeFunction` indicates that they should still be
treated as functions by the compiler.

Because of how the compiler treats functions, it may eliminate redundant calls,
assume that fields of an object have not been modified by calls to functions,
and otherwise do things that could potentially break in the face of a dangerous
unsafe function. It is your job to ensure that a function tagged 
`@unsafeFunction` does not violate any of the compiler's assumptions by not 
modifying anything that could be potentially visible to the calling code, and
be ok with the fact that repeated calls to the function could be folded together
into a single call.

<a name="external"></a>
@external
---------

The `@external` annotation marks a method which is implemented by external 
(non-Panda) code. Like abstract methods, eternal methods do not have a method
body. See [external methods](externalMethods.html) for more details.