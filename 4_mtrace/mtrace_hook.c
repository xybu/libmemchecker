#include <mcheck.h>

__attribute__((constructor ())) void mtrace_hook(){
	mtrace();
}

__attribute__((destructor ())) void mtrace_unhook(){
	muntrace();
}
