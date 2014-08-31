Overview
========

Panda is a high-level, general-purpose object oriented programming language with
support for:

* First-class immutable objects and value types
* First-class functions
* Type inference
* Non-nullable references
* Contracts (preconditions, postconditions, and invariants)
* Tuples
* "Sane" operator overloading
* Output to native code, JVM, or JavaScript

This is what a simple Panda program looks like:

<code>
<span class="keyword">method</span> <span class="methodName">randomArray</span>(<span class="variable">length</span>:<span class="type">Int</span>):<span class="type">Array&lt;Int&gt;</span> {
<div class="indent">
<span class="keyword">def</span> <span class="identifier">result</span> := <span class="keyword">new</span> <span class="type">Array&lt;Int&gt;</span>()
<span class="for">for</span> <span class="variable">i</span> <span class="keyword">in</span> <span class="number">0</span> .. <span class="variable">length</span>
<div class="indent">
<span class="variable">result</span>.<span class="methodName">append</span>(<span class="type">Random</span>.<span class="methodName">int</span>(<span class="number">100</span>))
</div>
<span class="keyword">return</span> <span class="variable">result</span>
</div>
}
</code>

constant COUNT := 20
def random := randomArray(COUNT)
Console.writeLine("\{COUNT} random numbers: \{random}")
def sum := random.fold(Int::+)
Console.writeLine("Total: \{sum}")
Console.writeLine("Average: \{sum / COUNT:.2}")

Example output:

    20 random numbers: [3, 37, 13, 67, 91, 74, 72, 57, 88, 28, 54, 21, 3, 88, 
    18, 81, 23, 53, 80, 30]
    Total: 981
    Average: 49.05

Getting Started
===============

After you download and unzip Panda, see the `INSTALL` file for instructions on
building it for your platform.

For a quick overview of Panda syntax, you may wish to look at 
[Panda in 15 Minutes](PandaIn15Minutes.panda) or 
[Panda For Java Programmers](pandaForJavaProgrammers.html).

Basic Topics
============

* [Compiling your first program](gettingStarted.html)
* [Statements](statements.html)
* [Types](types.html)
* [Classes](classes.html)
* [Interfaces](interfaces.html)
* [Methods](methods.html)
* [Functions](functions.html)
* [Constructors](constructors.html)
* [Operators](operators.html)
* [Operator Overloading](operatorOverloading.html)
* [Variables](variables.html)
* [Defines](defines.html)
* [Constants](constants.html)
* [Properties](properties.html)
* [Arrays](arrays.html)
* [Packages](packages.html)
* [Comments](comments.html)
* [Status and Roadmap](status.html)

Deeper Dives
============

* [API documentation](api/index.html)
* [Annotations](annotations.html)
* [Implicit Casting](implicitCasting.html)
* [`null`](null.html)
* [Non-Nullability](nonNullability.html)
* [Coding Conventions](codingConventions.html)
* [External Methods](externalMethods.html)
* [Why does Panda...?](rationales.html)

