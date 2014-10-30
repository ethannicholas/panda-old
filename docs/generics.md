Generics
========

Sometimes you may want to have many different versions of a class or method, 
which differ only in the types on which they operate. 
[Array](api/panda/collections/Array.html) is a good example, as you may have an
Array *of Strings* or an Array *of Monsters* or an Array *of Objects*; these
three types are clearly related yet different.

This feature is called "generics", and allows classes and methods to take *type
parameters* which are placeholders for actual types. Here is a simple example of
a container which allows you to insert elements and then pull one out at random:

@SOURCE(
class Bag<T> {
    @private
    def contents:Array<T>

    function length():Int {
        return contents.length
    }

    method add(item:T) {
        contents.add(item)
    }

    @pre(length > 0)
    method pullRandom():T {
        def index := Random.int(contents.length)
        def result := contents[index]
        contents.removeIndex(index)
        return result
    }
}
)

The type parameter `T` appearing after the class' name means "some type to be
specified later". In the expression `new Bag<String>()`, we are creating a `Bag`
in which all instances of `T` are taken to mean `panda.core.String`.