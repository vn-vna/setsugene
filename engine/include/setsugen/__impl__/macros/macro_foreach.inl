#pragma once

#define FOR_EACH(macro, ...) __VA_OPT__(FOR_EACH_HELPER(macro, __VA_ARGS__))
#define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN MACRO_PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER