Uses
====

The *uses* directive allows you to refer to classes using simpler names. 
Normally, if you have classes in two different [packages](packages.html), they
must use fully-qualified names to refer to each other:

@SOURCE(
    package example.package1
    
    class Example1 {
        var example2:example.package2.Example2
    }

    package example.package2
    
    class Example2 {
        var example1:example.package1.Example1
    }
)

By *using* these classes, we can refer to them using just their simple names:

@SOURCE(
    package example.package1
    
    uses example.package2.Example2

    class Example1 {
        var example2:Example2
    }

    package example.package2
    
    uses example.package1.Example1

    class Example2 {
        var example1:Example1
    }
)

Note that *using* a class does not actually bring in or load any additional 
code. It merely allows you to refer to classes without requiring their 
fully-qualified names. There are two different kinds of `uses`:

Using a Package
---------------

@SOURCE(
    package packageName
    class Dummy { }
    --BEGIN
    uses packageName.*
    Console.writeLine("dummy code")--SKIP
)

By *using* a package name followed by the token `".*"`, you *use* all classes
in the package.

Using a Class
-------------

@SOURCE(
    package fully.qualified
    class ClassName { }
    --BEGIN
    uses fully.qualified.ClassName-*REPLACE: [*- as Alias-*REPLACE:]*- 
)

This variant *uses* a single class, with an optional alias. Aliasing a class is
useful if two classes in different packages have the same simple name: you can
rename one or both of them within the context of the current compilation unit so
that you may unambiguously refer to them without needing to use their 
fully-qualified names.