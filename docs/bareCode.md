Bare Code
=========

*Bare code* is a general term for code (including [variables](variables.html),
[defines](defines.html), [constants](constants.html), [methods](methods.html),
or [statements](statements.html)) that appears outside of a 
[class](classes.html). For example, in the very simple program:

@SOURCE(
    Console.writeLine("Hello, world!")
)

the statement is not inside of a method in a class and therefore is bare code.

When the Panda compiler encounters bare code, it "wraps" it in a synthetic class
and, for anything other than a method, in a synthetic [main](main.html) method. 
This program will be treated as if you had actually written:

@SOURCE(
    class RandomName {
        @class
        method main(args:Array<String>) {
            Console.writeLine("Hello, world!")
        } 
    }
)

Bare code just reduces the amount of boilerplate necessary in very short, simple
programs. You probably will not use bare code in larger Panda programs; for
instance the Panda compiler has no bare code anywhere.

Methods appearing outside of classes are automatically treated as 
[`@class`](annotations.html#class) methods of the synthetic class. Variables, 
defines, and constants appearing outside of a class body are treated as local 
variables in the synthetic `main` method. Thus, you cannot write:

@SOURCE(
    var count := 0

    method increment() {
        var count := 0 --SKIP
        count += 1
    }

    increment()
    increment()
    Console.writeLine("The current count is: \{count}")
)

This will be compiled as if you had written:

@SOURCE(
    class RandomName {
        @class
        method increment() {
            var count := 0 --SKIP
            count += 1
        }

        @class
        method main(args:Array<String>) {
            var count := 0
            increment()
            increment()
            Console.writeLine("The current count is: \{count}")
        }
    }
)

This causes a compilation error because `count` is a local variable of the
`main` method and thus cannot be seen by the `increment` method. Bare code is 
thus somewhat limited in its expressive power compared to "normal" Panda code.