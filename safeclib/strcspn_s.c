/*  SPDX-License-Identifier: MIT */
/*
 *  Copyright (c) 2008 Bo Berry
 *  Copyright (c) 2008-2011 Cisco Systems
 */

#include "safeclib_private.h"
#include "safe_str_constraint.h"
#include "safe_str_lib.h"


/**
 * NAME
 *    strcspn_s
 *
 * SYNOPSIS
 *    #include "safe_str_lib.h"
 *    errno_t
 *    strcspn_s(const char *dest, rsize_t dmax,
 *              const char *src,  rsize_t slen, rsize_t *count)
 *
 * DESCRIPTION
 *    This function computes the prefix length of the string pointed
 *    to by dest which consists entirely of characters that are
 *    excluded from the string pointed to by src. The scanning stops
 *    at the first null in dest or after dmax characters. The
 *    exclusion string is checked to the null or after slen
 *    characters.
 *
 * EXTENSION TO
 *    ISO/IEC TR 24731, Programming languages, environments
 *    and system software interfaces, Extensions to the C Library,
 *    Part I: Bounds-checking interfaces
 *
 * INPUT PARAMETERS
 *    dest     pointer to string to determine the prefix
 *
 *    dmax     restricted maximum length of string dest
 *
 *    src      pointer to exclusion string
 *
 *    slen     restricted maximum length of string src
 *
 *    count    pointer to a count variable that will be updated
 *              with the dest substring length
 *
 * OUTPUT PARAMETERS
 *    count    updated count variable
 *
 * RUNTIME CONSTRAINTS
 *    Neither dest nor src shall be a null pointer.
 *    count shall not be a null pointer.
 *    dmax shall not be 0
 *    dmax shall not be greater than RSIZE_MAX_STR
 *
 * RETURN VALUE
 *    EOK         count
 *    ESNULLP     NULL pointer
 *    ESZEROL     zero length
 *    ESLEMAX     length exceeds max limit
 *
 * ALSO SEE
 *    strspn_s(), strpbrk_s(), strstr_s()
 *
 */
errno_t
strcspn_s (const char *dest, rsize_t dmax,
           const char *src,  rsize_t slen, rsize_t *count)
{
    const char *scan2;
    rsize_t smax;

    if (count== NULL) {
        invoke_safe_str_constraint_handler("strcspn_s: count is null",
                   NULL, ESNULLP);
        return RCNEGATE(ESNULLP);
    }
    *count = 0;

    if (dest == NULL) {
        invoke_safe_str_constraint_handler("strcspn_s: dest is null",
                   NULL, ESNULLP);
        return RCNEGATE(ESNULLP);
    }

    if (src == NULL) {
        invoke_safe_str_constraint_handler("strcspn_s: src is null",
                   NULL, ESNULLP);
        return RCNEGATE(ESNULLP);
    }

    if (dmax == 0 ) {
        invoke_safe_str_constraint_handler("strcspn_s: dmax is 0",
                   NULL, ESZEROL);
        return RCNEGATE(ESZEROL);
    }

    if (dmax > RSIZE_MAX_STR) {
        invoke_safe_str_constraint_handler("strcspn_s: dmax exceeds max",
                   NULL, ESLEMAX);
        return RCNEGATE(ESLEMAX);
    }

    if (slen == 0 ) {
        invoke_safe_str_constraint_handler("strcspn_s: slen is 0",
                   NULL, ESZEROL);
        return RCNEGATE(ESZEROL);
    }

    if (slen > RSIZE_MAX_STR) {
        invoke_safe_str_constraint_handler("strcspn_s: slen exceeds max",
                   NULL, ESLEMAX);
        return RCNEGATE(ESLEMAX);
    }

    while (*dest && dmax) {

        /*
         * Scanning for exclusions, so if there is a match,
         * we're done!
         */
        smax = slen;
        scan2 = src;
        while (*scan2 && smax) {

             if (*dest == *scan2) {
                 return RCNEGATE(EOK);
             }
             scan2++;
             smax--;
        }

        (*count)++;
        dest++;
        dmax--;
    }

    return RCNEGATE(EOK);
}
EXPORT_SYMBOL(strcspn_s)
