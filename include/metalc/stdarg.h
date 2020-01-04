#ifndef INCLUDE_METALC_STDARG_H_
#define INCLUDE_METALC_STDARG_H_

#include <metalc/metalc.h>

#if METALC_HAVE_STDARG_H
    #include <stdarg.h>
#else
    /* We may eventually implement this ourselves but it's highly unlikely */
    #error "Compiler must provide stdarg.h but it doesn't."
#endif  /* METALC_HAVE_STDARG_H */

#endif  /* INCLUDE_METALC_STDARG_H_ */
