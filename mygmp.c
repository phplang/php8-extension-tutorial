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

static PHP_MINIT_FUNCTION(mygmp) {
    gmp_randinit_mt(randstate);
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

