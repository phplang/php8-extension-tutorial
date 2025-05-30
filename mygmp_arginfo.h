/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 60d9514c956adab803ee5cb66930fcf47e92150b */

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MyGMP___construct, 0, 0, 0)
	ZEND_ARG_TYPE_MASK(0, num, MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_STRING, "0")
ZEND_END_ARG_INFO()

#define arginfo_class_MyGMP___toString arginfo_mygmp_get_version

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MyGMP___debugInfo, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MyGMP_add, 0, 1, MyGMP, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, other, MyGMP, MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

#define arginfo_class_MyGMP_sub arginfo_class_MyGMP_add

#define arginfo_class_MyGMP_mul arginfo_class_MyGMP_add

#define arginfo_class_MyGMP_divq arginfo_class_MyGMP_add

ZEND_FUNCTION(mygmp_version);
ZEND_FUNCTION(mygmp_get_version);
ZEND_FUNCTION(mygmp_add);
ZEND_FUNCTION(mygmp_add_array);
ZEND_FUNCTION(mygmp_sum);
ZEND_FUNCTION(mygmp_random_ints);
ZEND_METHOD(MyGMP, __construct);
ZEND_METHOD(MyGMP, __toString);
ZEND_METHOD(MyGMP, __debugInfo);
ZEND_METHOD(MyGMP, add);
ZEND_METHOD(MyGMP, sub);
ZEND_METHOD(MyGMP, mul);
ZEND_METHOD(MyGMP, divq);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(mygmp_version, arginfo_mygmp_version)
	ZEND_FE(mygmp_get_version, arginfo_mygmp_get_version)
	ZEND_FE(mygmp_add, arginfo_mygmp_add)
	ZEND_FE(mygmp_add_array, arginfo_mygmp_add_array)
	ZEND_FE(mygmp_sum, arginfo_mygmp_sum)
	ZEND_FE(mygmp_random_ints, arginfo_mygmp_random_ints)
	ZEND_FE_END
};

static const zend_function_entry class_MyGMP_methods[] = {
	ZEND_ME(MyGMP, __construct, arginfo_class_MyGMP___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(MyGMP, __toString, arginfo_class_MyGMP___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(MyGMP, __debugInfo, arginfo_class_MyGMP___debugInfo, ZEND_ACC_PUBLIC)
	ZEND_ME(MyGMP, add, arginfo_class_MyGMP_add, ZEND_ACC_PUBLIC)
	ZEND_ME(MyGMP, sub, arginfo_class_MyGMP_sub, ZEND_ACC_PUBLIC)
	ZEND_ME(MyGMP, mul, arginfo_class_MyGMP_mul, ZEND_ACC_PUBLIC)
	ZEND_ME(MyGMP, divq, arginfo_class_MyGMP_divq, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_MyGMP(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MyGMP", class_MyGMP_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, 0);

	return class_entry;
}
