#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include <gmp.h>

#include "mygmp_arginfo.h"

static gmp_randstate_t randstate;

PHP_FUNCTION(mygmp_get_version) {
    RETURN_STRING(gmp_version);
}

PHP_FUNCTION(mygmp_version) {
    php_printf("%s\n", gmp_version);
}

static void do_mygmp_add(zval *return_value, zend_string *arg1, zend_string *arg2) {
    zend_string *retstr;
    mpz_t ret, num1, num2;

    /* Parse text strings into GMP ints */
    mpz_inits(ret, num1, num2, NULL);
    if (mpz_set_str(num1, ZSTR_VAL(arg1), 0) || mpz_set_str(num2, ZSTR_VAL(arg2), 0)) {
        mpz_clears(ret, num1, num2, NULL);
        RETURN_FALSE;
    }

    /* Perform the operation */
    mpz_add(ret, num1, num2);

    /* Marshal the sum to a string for output */
    retstr = zend_string_alloc(mpz_sizeinbase(ret, 10), 0);
    mpz_get_str(ZSTR_VAL(retstr), 10, ret);
    ZSTR_LEN(retstr) = strlen(ZSTR_VAL(retstr));

    /* Free memory and return */
    mpz_clears(ret, num1, num2, NULL);
    RETURN_STR(retstr);
}

PHP_FUNCTION(mygmp_add) {
    zend_string *arg1, *arg2;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "PP", &arg1, &arg2) == FAILURE) {
        RETURN_THROWS();
    }
    do_mygmp_add(return_value, arg1, arg2);
}

PHP_FUNCTION(mygmp_add_array) {
    zend_array *arr;
    zval *a, *b;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "h", &arr) == FAILURE) {
        RETURN_THROWS();
    }

    a = zend_symtable_str_find(arr, "a", strlen("a"));
    b = zend_symtable_str_find(arr, "b", strlen("b"));
    if (!a || (Z_TYPE_P(a) != IS_STRING) || !b || (Z_TYPE_P(b) != IS_STRING)) {
        php_error(E_WARNING, "Invalid or missing elements");
        RETURN_FALSE;
    }

    do_mygmp_add(return_value, Z_STR_P(a), Z_STR_P(b));
}

PHP_FUNCTION(mygmp_sum) {
    zend_array *arr;
    zend_string *retstr;
    mpz_t ret;
    zval *val;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "h", &arr) == FAILURE) {
        RETURN_THROWS();
    }

    mpz_init(ret);
    /* foreach ($arr as $val) */
    ZEND_HASH_FOREACH_VAL(arr, val) {
        mpz_t v;
        zend_string *str = zval_get_string(val); // Provides auto-coersion

        mpz_init(v);
        if (mpz_set_str(v, ZSTR_VAL(str), 0)) {
            php_error(E_WARNING, "Invalid value: %s", ZSTR_VAL(str));
            mpz_clear(v);
            zend_string_release(str);
            continue;
        }

        mpz_add(ret, ret, v); // $ret += $v;
        mpz_clear(v);
        zend_string_release(str);
    } ZEND_HASH_FOREACH_END();

    retstr = zend_string_alloc(mpz_sizeinbase(ret, 10), 0);
    mpz_get_str(ZSTR_VAL(retstr), 10, ret);
    ZSTR_LEN(retstr) = strlen(ZSTR_VAL(retstr));

    mpz_clear(ret);
    RETURN_STR(retstr);
}

PHP_FUNCTION(mygmp_random_ints) {
    zend_long count;
    zend_long bits = sizeof(zend_long) << 3;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l|l", &count, &bits) == FAILURE) {
        RETURN_THROWS();
    }

    if (count < 0) {
        php_error(E_WARNING, "Invalid number of random ints requested");
        RETURN_FALSE;
    }

    if ((bits < 1) || (bits > (sizeof(zend_long) << 3))) {
        php_error(E_WARNING, "Invalid bitsize requested, using %ld instead",
                  sizeof(zend_long) << 3);
        bits = sizeof(zend_long) << 3;
    }

    array_init(return_value);
    while (count--) {
        zend_long val = (zend_long)gmp_urandomb_ui(randstate, bits);
        add_next_index_long(return_value, val);
    }
}

static zend_class_entry *mygmp_ce;
static zend_object_handlers mygmp_handlers;

typedef struct _mygmp_object {
    mpz_t value;
    zend_object std;
} mygmp_object;

static zend_object* mygmp_to_zend_object(mygmp_object* objval)
    { return ((zend_object*)(objval + 1)) - 1; }

static mygmp_object* mygmp_from_zend_object(zend_object* zobj)
    { return ((mygmp_object*)(zobj + 1)) - 1; }

PHP_METHOD(MyGMP, __construct) {
    // TODO...
}

static zend_object* mygmp_ctor(zend_class_entry *ce) {
    mygmp_object *objval = ecalloc(1, sizeof(mygmp_object) + zend_object_properties_size(ce));
    mpz_init(objval->value);

    zend_object* ret = mygmp_to_zend_object(objval);
    zend_object_std_init(ret, ce);
    object_properties_init(ret, ce);
    ret->handlers = &mygmp_handlers;

    return ret;
}

static zend_object* mygmp_clone(zend_object *zsrc) {
    zend_object *zdst = mygmp_ctor(zsrc->ce);
    zend_objects_clone_members(zdst, zsrc);

    mygmp_object *src = mygmp_from_zend_object(zsrc);
    mygmp_object *dst = mygmp_from_zend_object(zdst);
    mpz_set(dst->value, src->value);
    return zdst;
}

static void mygmp_free(zend_object *zobj) {
    mygmp_object *obj = mygmp_from_zend_object(zobj);
    mpz_clear(obj->value);
    zend_object_std_dtor(zobj);
}

static PHP_MINIT_FUNCTION(mygmp) {
    gmp_randinit_mt(randstate);
    mygmp_ce = register_class_MyGMP();
    mygmp_ce->create_object = mygmp_ctor;

    memcpy(&mygmp_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mygmp_handlers.offset = XtOffsetOf(mygmp_object, std);
    mygmp_handlers.clone_obj = mygmp_clone;
    mygmp_handlers.free_obj = mygmp_free;

    return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(mygmp) {
    gmp_randclear(randstate);
    return SUCCESS;
}

static PHP_MINFO_FUNCTION(mygmp) {
    php_info_print_table_start();
    php_info_print_table_row(2, "MyGMP support", "enabled");
    php_info_print_table_row(2, "libgmp version", gmp_version);
    php_info_print_table_end();
}

zend_module_entry mygmp_module_entry = { 
    STANDARD_MODULE_HEADER,
    "mygmp",
    ext_functions,
    PHP_MINIT(mygmp),
    PHP_MSHUTDOWN(mygmp),
    NULL, /* RINIT */
    NULL, /* MINFO */
    PHP_MINFO(mygmp),
    NO_VERSION_YET,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYGMP
ZEND_GET_MODULE(mygmp)
#endif

