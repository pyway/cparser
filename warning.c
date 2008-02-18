/*
 * This file is part of cparser.
 * Copyright (C) 2007-2008 Matthias Braun <matze@braunis.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
#include <stdio.h>
#include <string.h>
#include "warning.h"

warning_t warning = {
	.char_subscripts               = true,
	.check_format                  = true,
	.empty_statement               = false,
	.fatal_errors                  = false,
	.float_equal                   = false,
	.implicit_function_declaration = true,
	.implicit_int                  = true,
	.main                          = true,
	.missing_declarations          = false,
	.missing_prototypes            = false,
	.multichar                     = true,
	.redundant_decls               = true,
	.s_are_errors                  = false,
	.shadow                        = false,
	.sign_compare                  = false,
	.strict_prototypes             = true,
	.switch_default                = false,
	.unknown_pragmas               = true,
	.unused_function               = false,
	.unused_label                  = false,
	.unused_parameter              = false,
	.unused_value                  = true,
	.unused_variable               = false
};

void set_warning_opt(const char *const opt)
{
	const char* s = opt;

	bool state = true;

	/* "no-" prefix */
	if (s[0] == 'n' && s[1] == 'o' && s[2] == '-') {
		s += 3;
		state = false;
	}

	if (0) {}
#define OPTX(x)   else if (strcmp(s, x) == 0)
#define SET(y)    warning.y = state;
#define OPT(x, y) OPTX(x) SET(y)
	OPTX("all") {
		/* Note: this switched on a lot of more warnings than gcc's -Wall */
		SET(char_subscripts)
		SET(check_format)
		SET(empty_statement)
		SET(implicit_function_declaration)
		SET(implicit_int)
		SET(main)
		SET(redundant_decls)
		SET(shadow)
		SET(sign_compare)
		SET(strict_prototypes)
		SET(unknown_pragmas)
		SET(unused_function)
		SET(unused_label)
		SET(unused_parameter)
		SET(unused_value)
		SET(unused_variable)
	}
	OPT("char-subscripts",               char_subscripts)
	OPT("empty-statement",               empty_statement)
	OPT("error",                         s_are_errors)
	OPTX("extra") {
		/* TODO */
		// TODO SET(function_end_without_return)
		SET(empty_statement)
		// TODO SET(incomplete_aggregate_init)
		// TODO SET(pointless_comparison)
		// TODO SET(sign_compare)
		SET(unused_parameter)
		SET(unused_value)
	}
	OPT("fatal-errors",                  fatal_errors)
	OPT("float-equal",                   float_equal)
	OPT("format",                        check_format)
	OPTX("implicit") {
		SET(implicit_function_declaration)
		SET(implicit_int)
	}
	OPT("implicit-function-declaration", implicit_function_declaration)
	OPT("implicit-int",                  implicit_int)
	OPT("main",                          main)
	OPT("missing-declarations",          missing_declarations)
	OPT("missing-prototypes",            missing_prototypes)
	OPT("multichar",                     multichar)
	OPT("redundant-decls",               redundant_decls)
	OPT("shadow",                        shadow)
	OPT("sign-compare",                  sign_compare)
	OPT("strict-prototypes",             strict_prototypes)
	OPT("switch-default",                switch_default)
	OPT("unknown-pragmas",               unknown_pragmas)
	OPTX("unused") {
		SET(unused_function)
		SET(unused_label)
		SET(unused_parameter)
		SET(unused_value)
		SET(unused_variable)
	}
	OPT("unused-function",               unused_function)
	OPT("unused-label",                  unused_label)
	OPT("unused-parameter",              unused_parameter)
	OPT("unused-value",                  unused_value)
	OPT("unused-variable",               unused_variable)
#undef OPT
#undef SET
#undef OPT_X
	else {
		fprintf(stderr, "warning: ignoring unknown option -W%s\n", opt);
	}
}
