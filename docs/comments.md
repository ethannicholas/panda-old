Comments
========

Panda supports three different styles of comments:

Line comments
-------------

Two hyphens in a row (`--`) begin a *line comment*, causing the rest of the line
to be ignored:

    var x:Int -- initialized in the constructor

Block comments
--------------

A hyphen followed by an asterisk (`-*`) begins a *block comment*, and the 
opposite sequence (`*-`) ends the block comment:

    -* Output the sorted results
     * Need to do some better formatting in the future
     *-
    list.sort()
    Console.writeLine(list)

Documentation comments
----------------------

Three or more equals signs (`===`) begin and end a *documentation comment*.
Documentation comments are special comments that must appear immediately prior
to a class, method, or field, and provide a formal description of the class,
method, or field they precede.

    ============================================================================
    Appends a character to the end of the string.

    @param c the character to append
    ============================================================================
    method append(c:Char) {
        ...
    }
    @post(length = @pre(length) + 1)

Documentation comments are described in more detail on the 
[documentation comments](documentationComments.html) page. Documentation 
comments in Panda, unlike in many other languages, are actually part of the
language's grammar and thus may not appear anywhere but immediately before a
class, method, or field.