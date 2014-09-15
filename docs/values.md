Values
======

Value types are any objects descending from the class 
[`panda.core.Value`](api/panda.core.Value.html). Because `Value` descends from
[`Immutable`](immutable.html), all `Value` types are therefore also immutable.

`Value` types, such as `Int32` and `Bit` are special in that they are not
required to have an identity. In other words, you may not use the `==` or `!==`
operators on `Value` types, because the answer would be meaningless. The 
compiler is free to coalesce similar value types into a single instance and to
pass value types by value instead of by reference. Note that these optimizations
are not required; they may not be implemented at all, or the compiler may choose
to pass some `Value` objects by value and other `Value` objects by reference.

Because they do not have an identity, `Value` types may not have finalizers
(`Value` has a `@final` do-nothing finalizer to prevent this.)