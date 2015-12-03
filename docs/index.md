Overview
========

Panda is a high-level, general-purpose object oriented programming language with
support for:

* First-class immutable objects and value types
* First-class functions and closures
* Type inference
* Non-nullable references, static proofs of null safety
* Contracts (preconditions, postconditions, and invariants)
* Tuples
* "Sane" operator overloading
* Output to native code, JVM, or JavaScript

This is what a simple Panda program looks like:

@SOURCE(
    ================================================================================
    Given a descriptor of the form `"2d6 + 2", simulates a (possibly modified) roll 
    of one or more dice. The number of dice defaults to 1 if not specified, and
    the modifier defaults to 0 if not specified.

    @param descriptor a string describing the number and kind of dice to roll,
            possibly with a modifier
    @returns the total roll
    ================================================================================
    method rollDice(descriptor:String):Int {
        -- use a regular expression to split the string into its component parts
        def parsed := descriptor.parse(/(\d+)?d(\d+)(?:\s*([+\-])\s*(\d+))?/)
        if parsed = null
            throw ParseException(descriptor)
        def count:Int
        if parsed[0] != ""
            count := parsed[0].convert()
        else
            count := 1
        def sides := parsed[1].convert()->Int
        var total:Int
        if parsed[3] != ""
            total := parsed[3].convert()->Int
        else
            total := 0
        if parsed[2] = "-"
            total := -total
        
        for i in 0 .. count
            total += Random.int(sides) + 1
        return total
    }

    for dice in ["2d6", "4d4 + 3", "d20", "d12 - 1"] {
        -- the <7 and >2 below respectively left-justify and right-justify the 
        -- values, so that everything lines up nicely
        Console.writeLine("\{dice,<7} = \{rollDice(dice),>2}")
    }
)

Example output:

    2d6     =  5
    4d4 + 3 = 14
    d20     =  6
    d12 - 1 =  7