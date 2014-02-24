Getting Started
===============

See the `INSTALL` file in the Panda distribution for build instructions. After
you build the compiler, add `target/pandac/bin` to your `path`.

Create a file named `hello.panda` containing the following code:
    Console.writeLine("Hello, World!")

Run the command `pandac hello.panda`. This will produce an executable file
named `hello`. Running `hello` will produce the output:
    Hello, World!

For more interesting examples, check the `examples` directory. The `run.sh`
scripts in each individual example will execute the example code.
