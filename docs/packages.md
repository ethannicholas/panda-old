Packages
========

A *package* is a namespace which [classes](classes.html) may belong to. Packages
are introduced with the `package` [keyword](keywords.html):

@SOURCE(
    package org.pandalanguage.examples
    --END
    class A { }
)

After a `package` statement, all classes appearing in the same file are
considered to belong to that package.

@SOURCE(
    package org.pandalanguage.package1

    class A { }

    class B { }

    package org.pandalanguage.package2

    class C { }
)

In this example, classes `A` and `B` belong to package 
`org.pandalanguage.package1`, and class `C` belongs to package 
`org.pandalanguage.package2`.

Class `A` has the *simple* name `A`, and the *fully-qualified* name
`org.pandalanguage.package1.A`. It is always legal to refer to a class using its
fully-qualified name, but you may use its simple name when:

* You are referring to a class in the same package
* You have used a [uses](uses.html) directive for the class or its containing 
  package
* The class is in the package `panda.core`, `panda.collections`, `panda.io`, 
  `panda.math`, or `panda.threads`