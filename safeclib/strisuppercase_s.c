/*  SPDX-License-Identifier: MIT */
/*
 *  Copyright (c) 2008 Bo Berry
 *  Copyright (c) 2008-2011, 2013 Cisco Systems
 */

#include "safeclib_private.h"
#include "safe_str_constraint.h"
#include "safe_str_lib.h"


/**
 * NAME
 *    strisuppercase_s
 *
 * SYNOPSIS
 *    #include "safe_str_lib.h"
 *    bool
 *    strisuppercase_s(const char *dest, rsize_t dmax)
 *
 * DESCRIPTION
 *    This function checks if entire string is uppercase
 *    The scanning stops at the first null or after dmax
 *    characters.
 *
 * EXTENSION TO
 *    ISO/IEC TR 24731, Programming languages, environments
 *    and system software interfaces, Extensions to the C Library,
 *    Part I: Bounds-checking interfaces
 *
 * INPUT PARAMETERS
 *    dest      pointer to string
 *
 *    dmax      maximum length of string
 *
 * OUTPUT PARAMETERS
 *    none
 *
 * RUNTIME CONSTRAINTS
 *    dest shall not be a null pointer.
 *    dmax shall not equal zero.
 *    dmax shall not be greater than RSIZE_MAX_STR.
 *
 * RETURN VALUE
 *    true      string is uppercase
 *    false     string is not uppercase or an error occurred
 *
 * ALSO SEE
 *    strisalphanumeric_s(), strisascii_s(), strisdigit_s(),
 *    strishex_s(), strislowercase_s(), strismixedcase_s(),
 *
 */
bool
strisuppercase_s (const char *dest, rsize_t dmax)
{

    if (!dest) {
        invoke_safe_str_constraint_handler("strisuppercase_s: "
                   "dest is null",
                   NULL, ESNULLP);
        return (false);
    }

    if (dmax == 0) {
        invoke_safe_str_constraint_handler("strisuppercase_s: "
                   "dmax is 0",
                   NULL, ESZEROL);
        return (false);
    }

    if (dmax > RSIZE_MAX_STR) {
        invoke_safe_str_constraint_handler("strisuppercase_s: "
                   "dmax exceeds max",
                   NULL, ESLEMAX);
        return (false);
    }

    if (*dest == '\0') {
        return (false);
    }

    while (*dest) {

        if ((*dest < 'A') || (*dest > 'Z')) {
            return (false);
        }
        dest++;
        dmax--;
    }

    return (true);
}
EXPORT_SYMBOL(strisuppercase_s)
