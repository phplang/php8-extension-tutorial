dnl config.m4
PHP_ARG_WITH(mygmp, for GNU MP support,
[  --with-mygmp[=DIR]          Include GNU MP support])

if test "$PHP_MYGMP" != "no"; then
  dnl Update library list and include paths for libgmp
  PKG_CHECK_MODULES([GMP], [gmp >= 5.0.0])
  PHP_EVAL_INCLINE([$GMP_CFLAGS])
  PHP_EVAL_LIBLINE([$GMP_LIBS], [MYGMP_SHARED_LIBADD])
  PHP_SUBST(MYGMP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mygmp, mygmp.c, $ext_shared)
fi
