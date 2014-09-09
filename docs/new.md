New
===

The `new` [keyword](keywords.html) is used to create new instances of a 
[class](classes.html). The syntax for `new` is:

@SOURCE(
    class ClassName { }
    --BEGIN
    new ClassName()
)

Any parameters to the [constructor](constructors.html) go inside the 
parentheses, such as in the expression `new File("calling a constructor")`.

Panda features automatic memory management. Objects will be automatically
destroyed when there are no remaining references to them.