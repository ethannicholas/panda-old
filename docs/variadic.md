Variadic Methods
================

*Variable arity* or *variadic* [methods](methods.html) are methods which can 
accept a variable number of parameters. Variadic methods are created by using an 
ellipsis (`...`) after the type of the final method parameter:

@SOURCE(
    method variadic(message:String, parameters:Object...) {
        -*REPLACE:...*---dummy comment
    }
)

The `parameters` parameter may be repeated any number of times, including zero.
The following calls to the `variadic` method are all valid:

@SOURCE(
    method variadic(message:String, parameters:Object...) { }
    --BEGIN
    variadic("Hello")
    variadic("Goodbye", "Cruel", "World")
    variadic("I'm Back!", 12, new File("/tmp"))
)

Within the body of the variadic method, the `parameters` parameter is 
represented as a `ListView` of the relevant type (`Object`, in this case).

@SOURCE(
    method variadic(message:String, parameters:Object...) {
        Console.writeLine("\{message}:")
        for p in parameters
            Console.writeLine("    \{p}")
    }
)

Unwrapping a List
-----------------

You may encounter a situation in which you have the parameters you wish to pass
in to a variadic method already in a `ListView`:

@SOURCE(
    def parameters:Array<Object> := ["Some", "parameters", "determined", "somehow"]
)

If you wish to pass these parameters to `variadic`, this approach won't work:

@SOURCE(
    method variadic(message:String, parameters:Object...) { }
    def parameters:Array<Object> := []
    --BEGIN
    variadic("Won't work!", parameters) -- only passes one parameter!
)

This call passes a single parameter, namely the `parameters` list. That probably 
isn't what you meant. You can *unwrap* the list, passing the four objects it
contains as separate parameters, using an ellipsis (`...`):

@SOURCE(
    method variadic(message:String, parameters:Object...) { }
    def parameters:Array<Object> := []
    --BEGIN
    variadic("This works!", parameters...) -- passes four parameters
)