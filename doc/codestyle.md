#General
Always library functions if available. Be as modular as possible. *Do not* use magic numbers in code. Try to avoid constant definitions.

#Comments
Roughly describe for each function *what* it does. If you feel that a design choice of an implementation detail is not directly obvious, clarify briefly. Comments in separate lines before commented code.

#Naming
Since C is awfully untyped, in addition to always using telling variable and function names, use [Apps Hungarian] (http://en.wikipedia.org/wiki/Hungarian_notation) where [appropriate] (http://www.joelonsoftware.com/articles/Wrong.html).

#Indentation
Use [Allman style] (http://en.wikipedia.org/wiki/Indent_style#Allman_style) with tab indentation.

#Testing
Test each implemented function at least with some hard coded data. As soon as dynamic data structures are available, try to write at least one more sophisticated test.
