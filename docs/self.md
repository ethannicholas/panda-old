self
====

`self` is a special [keyword](keywords.html) which represents the object 
instance against which an instance method is running. 

Example:

    class Example {
        var name := "class Example"

        method sayHello() {
            Console.writeLine("Hello from " + self + "!")
        }

        @override
        function ->>():String {
            return name
        }

        @class
        method main() {
            new Example().sayHello()
        }
    }

Result: `Hello from class Example!`

`self` is defined only within instance methods.