Fields
======

A *field* is a [variable](variables.html) declared inside of a class body. In
this simple class:

@SOURCE(
    class Point {
        var x:Int
        var y:Int
    }
)

there are two fields, named `x` and `y`. Each individual `Point` object instance
has its own copies of the `x` and `y` fields.

Fields may be either *instance* or *thread* [scoped](scope.html). There are no
class or global scoped fields in Panda.