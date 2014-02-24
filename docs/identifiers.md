Identifier
==========

An *identifier* is a name used in a Panda program to refer to a 
[class](classes.html), [method](methods.html), [variable](variables.html), or
other program element.

Identifiers must begin with a letter or underscore (`_`), and continue with any 
number of letters, underscores, or digits. [Keywords](keywords.html) are 
reserved and may not be used as identifiers. An underscore by itself is not a
legal identifier, as that is used to ignore values when extracting values from a
[`tuple`](tuples.html) in a multiple assignment.

Internal Use Names
------------------

Technically, the dollar sign (`$`) is also a legal identifier character. 
However, names involving dollar signs are reserved for internal use by the
compiler and should not be used in user programs.