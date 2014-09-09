Compilation Units
=================

A "compilation unit" is a single file out of the set of files being compiled.
Generally, you will want to have each [class](classes.html) you are compiling 
live in its own file, so for instance you might have:

One.panda
---------

@SOURCE(
    package foo.bar

    class One {
        -*REPLACE:...*---dummy comment
    }
)

Two.panda
---------

@SOURCE(
    package foo.bar

    class Two {
        -*REPLACE:...*---dummy comment
    }
)

You would compile these two separate compilation units together in order to form
a program.

Each compilation unit contains zero or more classes, and optionally some 
[bare code](bareCode.html).