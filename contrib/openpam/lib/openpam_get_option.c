/*-
 * Copyright (c) 2002 Networks Associates Technologies, Inc.
 * All rights reserved.
 *
 * This software was developed for the FreeBSD Project by ThinkSec AS and
 * NAI Labs, the Security Research Division of Network Associates, Inc.
 * under DARPA/SPAWAR contract N66001-01-C-8035 ("CBOSS"), as part of the
 * DARPA CHATS research program.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $P4: //depot/projects/openpam/lib/openpam_get_option.c#2 $
 */

#include <sys/param.h>

#include <string.h>

#include <security/pam_appl.h>
#include <security/openpam.h>

#include "openpam_impl.h"

/*
 * OpenPAM extension
 *
 * Returns the value of a module option
 */

const char *
openpam_get_option(pam_handle_t *pamh,
	const char *option)
{
	pam_chain_t *cur;
	size_t len;
	int i;

	if (pamh == NULL || pamh->current == NULL || option == NULL)
		return (NULL);
	cur = pamh->current;
	len = strlen(option);
	for (i = 0; i < cur->optc; ++i) {
		if (strncmp(cur->optv[i], option, len) == 0) {
			if (cur->optv[i][len] == '\0')
				return (&cur->optv[i][len]);
			else if (cur->optv[i][len] == '=')
				return (&cur->optv[i][len + 1]);
		}
	}
	return (NULL);
}

/*
 * NOLIST
 */

/**
 * The =openpam_get_option function returns the value of the specified
 * option in the context of the currently executing service module, or
 * =NULL if the option is not set or no module is currently executing.
 */
