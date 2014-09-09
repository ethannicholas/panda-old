pandac
======

The Panda compiler is named `pandac`. `pandac` takes one or more `.panda` files
as input and produces an executable program as output.

Simple usage:

    > pandac Hello.panda
    > ./Hello
    Hello, world!
    > 

Command-line arguments:

<table>
  <tr>
    <th>-o &lt;path&gt;</th>
    <td>Output path</td>
  </tr>
  <tr>
    <th>-f &lt;format&gt;</th>
    <td>Output format. Options include:
      <ul>
        <li><code>exec</code>: executable file (the default)</li>
        <li><code>lib</code>: library file</li>
        <li><code>doc</code>: documentation</li>
        <li><code>html</code>: syntax-highlighted HTML</li>
        <li><code>h</code>: C header files</li>
        <li><code>java</code>: Java source code</li>
        <li><code>javah</code>: Java "header" files (interfaces for external methods)</li>
        <li><code>jar</code>: Executable `.jar` file</li>
        <li><code>js</code>: JavaScript files</li>
      </ul>
    </td>
  </tr>
  <tr>
    <th>-L &lt;path&gt;</th>
    <td>Library search path</td>
  </tr>
  <tr>
    <th>-l &lt;name&gt;</th>
    <td>Library to link against</td>
  </tr>
  <tr>
    <th>-S0</th>
    <td>Disable safety checks</td>
  </tr>
</table>

**IMPLEMENTATION NOTE:** More complete `pandac` documentation is pending. The
compiler is also *very slow* for small programs at the moment. This is very
unfortunate, but not a permanent situation (performance improvements are blocked
on generics, for reasons I won't get into at the moment). It *should* be taking
a fraction of a second to compile a small program, but is currently taking
several seconds. **This will get fixed**, don't despair.