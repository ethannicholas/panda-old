Documentation Comments
======================

A *documentation comment* is a special comment that must appear immediately 
prior to a [class](classes.html), [method](methods.html), or 
[field](fields.html), and provides a formal description of the class, method, or
field it precedes.

Documentation comments begin and end with three or more equals signs (`===`), as
in:


@SOURCE(
    ============================================================================
    Appends a character to the end of the string.

    @param c the character to append
    ============================================================================
    method append(c:Char) {
        -*REPLACE:...*---dummy comment
    }
)

While only three equals signs are necessary, by convention the row of equals 
signs extend to the width of the source code.

Documentation comments are processed by [`pandac`](pandac.html) when the output
format (`-f`) is set to `doc`, causing a set of HTML documentation files to be
produced.

**IMPLEMENTATION NOTE:** Currently, the doc output is actually XML suitable for
postprocessing using the `pandadoc.xsl` stylesheet. When Panda has a built-in
XSLT processor, the XSLT processing will happen as part of the doc output.

Documentation comments consist of three parts. The *summary* is the first 
"sentence" of the content, extending from the beginning of the comment to the
first period (`.`). The *description* is the entire documentation text, 
including the summary, up until the *tags* begin. The *tags* are a set of
directives beginning with `@` at the end of the documentation comment.

The summary and description permit a very limited subset of Markdown notation
for text formatting. In particular, they support `*italic text*` and 
`**bold text**`, `\`code spans\``, code blocks (blocks indented by four spaces), 
and `[links](target.html)`.

In addition to normal URL links, links within documentation comments may point
to particular classes, fields, and methods. If the link target starts with 
`"http:"` or `"/"`, it will be treated as a URL. Otherwise, the compiler will
attempt to resolve it as a reference to a class, field, or method. Classes may 
be named using their fully-qualified names, or simple name / alias if they are
imported. Fields may be referenced by their simple name, if within the same 
class, or by a "member" expression of the form `ClassName::fieldName`. Methods
may be referenced in the same fashion as fields, but may also have a list of
parameter types to disambiguate similarly-named methods (e.g. `Int::max(Int)`).

Panda extends the Markdown link syntax to allow for "simple" links. Normally, 
you would specify the link target using a parenthesized URL after the link text,
as in `[Object](Object)`. In Panda documentation it often happens that the link
text and link target are the same, so Panda allows you to omit the link target.
This means you can create a link to the `Object` class simply by writing 
`[Object]`.

Zero or more tags follow the description. Tags provide additional documentation
such as parameters and return types. Supported tags include:

* `@param <name> <description>` - provides a description for the named parameter
* `@returns <description>` - describes the method's return value
* `@see <link>` - provides a See Also link