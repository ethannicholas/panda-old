String Interpolation
====================

*String interpolation* is the ability to embed expressions directly into string
literals:

@SOURCE(
    def count := 9
    Console.writeLine("I did it \{count} times!")
)

String interpolations are introduced with a backslash followed by a left curly
brace (`\{`) and ended by a right curly brace (`}`). The full range of 
formatting options described at `OutputStream.write()` are available:

@SOURCE(
    def total := 42.5988
    Console.writeLine("Total: \{total,$>10:.2}")
)

Result: `Total: $$$$$42.60`
