/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 65f15bc42e4bbde48854c2489057ffed3396e723 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_version, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_get_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_mygmp_add, 0, 2, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(mygmp_version);
ZEND_FUNCTION(mygmp_get_version);
ZEND_FUNCTION(mygmp_add);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(mygmp_version, arginfo_mygmp_version)
	ZEND_FE(mygmp_get_version, arginfo_mygmp_get_version)
	ZEND_FE(mygmp_add, arginfo_mygmp_add)
	ZEND_FE_END
};
