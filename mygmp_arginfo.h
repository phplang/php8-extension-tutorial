/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: bc8fe8c8f96da45bac2bd57a7b3a57fbdebc30e6 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_version, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_get_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_mygmp_add, 0, 2, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_add_array, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, arr, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_mygmp_sum, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, nums, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_mygmp_random_ints, 0, 1, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, bits, IS_LONG, 0, "64")
ZEND_END_ARG_INFO()

ZEND_FUNCTION(mygmp_version);
ZEND_FUNCTION(mygmp_get_version);
ZEND_FUNCTION(mygmp_add);
ZEND_FUNCTION(mygmp_add_array);
ZEND_FUNCTION(mygmp_sum);
ZEND_FUNCTION(mygmp_random_ints);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(mygmp_version, arginfo_mygmp_version)
	ZEND_FE(mygmp_get_version, arginfo_mygmp_get_version)
	ZEND_FE(mygmp_add, arginfo_mygmp_add)
	ZEND_FE(mygmp_add_array, arginfo_mygmp_add_array)
	ZEND_FE(mygmp_sum, arginfo_mygmp_sum)
	ZEND_FE(mygmp_random_ints, arginfo_mygmp_random_ints)
	ZEND_FE_END
};
