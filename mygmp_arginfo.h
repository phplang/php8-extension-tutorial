/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a8239839f63af1d19ce92de53d3ae50396f0a970 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_version, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_mygmp_get_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(mygmp_version);
ZEND_FUNCTION(mygmp_get_version);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(mygmp_version, arginfo_mygmp_version)
	ZEND_FE(mygmp_get_version, arginfo_mygmp_get_version)
	ZEND_FE_END
};
