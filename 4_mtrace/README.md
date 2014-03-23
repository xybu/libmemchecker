mtrace hook
***

# Known Issues

1. mtrace will treat realloc(ptr, 0) as UNfreed memory.
