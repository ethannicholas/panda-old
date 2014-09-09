main
====

The `main` [method](methods.html) is the entry point to your program, the code
that actually runs when it starts up. `main` can be defined on any class, must
be a [`@class`](annotations.html#class) method, and may be defined to take 
either zero parameters or an `Array<String>`. 

If `main` is defined to take an `Array<String>`, it will receive the 
command-line arguments passed into the program. If it is defined to take zero
parameters, the command-line arguments are ignored.

@SOURCE(
    class Example {
        @class
        method main(args:Array<String>) {
            Console.writeLine("main invoked with parameters: \{args}")
        }
    }
)

    > pandac Example.panda
    > ./Example a couple of parameters
    main invoked with parameters: [a, couple, of, parameters]
    >

**IMPLEMENTATION NOTE:** Eventually, you will be able to have a `main` on
multiple classes and select which one to actually use via a command-line flag to 
`pandac`. Currently, it is an error to have more than one `main` method among 
the set of classes being compiled.