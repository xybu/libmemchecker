mtrace hook
===============

The third method uses mtrace component in Linux to generate and parse logs.

## Known Issues

1. Older versions of mtrace will treat realloc(ptr, 0) as __UNfreed__ memory (mtrace bug #14981 as recorded at https://sourceware.org/bugzilla/show_bug.cgi?id=14981).
