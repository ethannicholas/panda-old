Default Values
==============

Several Panda [types](types.html) have a *default value*:

    * All `Int`s, `Real`s, and `Char`: `0`
    * `Bit`: `false`
    * Nullable types: `null`

[Fields](fields.html) in a newly-created object are initialized to their default 
value prior to the [constructor's](constructors.html) execution. 
[Non-nullable](nonNullability.html) types other than those listed above do not 
have a default value; you may not read such fields before they are assigned.

[Arrays](arrays.html) created with a specified size will be filled with the
default value for their type. Arrays for types without default values do not
possess a constructor which allows you to specify a size.