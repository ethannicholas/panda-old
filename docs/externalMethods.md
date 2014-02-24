External Methods
================

An *external* method is one which is implemented by non-Panda code. Methods 
(including functions) tagged with the `@external` annotation do not have a
method body in Panda; the compiler assumes that the method definition will be
found during the linking process. 

When compiling to native code, external methods are implemented by static or 
dynamic libraries containing C calling convention functions. When compiling to 
the JVM, external methods are implemented using ordinary Java methods. To be
properly resolved, the external implementation of a Panda method has to follow
certain naming conventions described below.

External Methods in C
---------------------

When using C (or another language capable of producing C calling convention
functions), the implementation of the external function must be named properly
and provided to the compiler in a library so that it can be linked against
(FIXME: describe how).

To determine the correct names for your external methods, compile the program
using the `-f h` (format: C header) command line arguments. Because C header
output produces multiple files, you must also specify `-o` with a directory 
name. The header files produced by this process will include a great deal of
useful information: in addition to function declarations for all of the classes'
external methods there will be a `struct` defined for each class, giving you its 
layout in memory, along with information about each of its methods enabling them
to be called directly from C (or equivalent) code.

The name chosen for a method will take one of three forms:

1. The "short form" of a method name is the fully-qualified class name (dots 
   ('.') replaced with dollar signs ('$')), a dollar sign, and then the name of
   the method (e.g. com$example$ClassName$methodName)
2. The "medium form" of a method name is the same as the short form, followed by
   an underscore-separated list of the simple names of its parameter types 
   (e.g. com$example$ClassName$methodName_Int32_String).
3. The "long form" of a method name is the same as the medium form, but using
   the fully-qualified names of its parameter types (e.g. 
   com$example$ClassName$methodName_panda$core$Int32_panda$core$String).   

For each method, the shortest form which unambiguously identifies it is chosen. 
In practice, the long form is unlikely to ever show up in actual code, but it
exists for safety's sake. The three different method name forms are described
here purely for your edification; the name chosen by the Panda compiler will
show up in the header files produced by a `-f h` compilation and you may simply
implement the named method as a C function.

External Methods in Java
------------------------

The basic idea of an external method in Java is similar to the C case, but the
external methods will be provided by implementing a Java interface.

Compiling a program with `-f javah` will produce the Java equivalent of C's 
header files: a set of interfaces which describe the methods to be implemented,
alongside default implementations of those interfaces which simply throw
`UnsupportedOperationException` for every method. Use the default 
implementations as a starting point; your own implementations of the interfaces
*must* have the same name as these default implementations.

(FIXME: describe how to provide these implementations at compile time)