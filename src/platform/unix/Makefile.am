# SmallBASIC command line version
# Copyright(C) 2001-2012 Chris Warren-Smith.
#
# This program is distributed under the terms of the GPL v2.0 or later
# Download the GNU Public License (GPL) from www.gnu.org
# 

AM_CPPFLAGS = -I$(top_builddir)/src -I. @PACKAGE_CFLAGS@

bin_PROGRAMS = sbasic

sbasic_SOURCES =          \
  ../unix/console_main.c	\
  ../unix/dev_null.c

sbasic_LDADD = -L$(top_srcdir)/src/common -lsb_common @PACKAGE_LIBS@

if !WITH_WIN32
sbasic_LDADD += -ldl
endif

sbasic_DEPENDENCIES = $(top_srcdir)/src/common/libsb_common.a

TEST_DIR=../../../samples/distro-examples/tests
UNIT_TESTS=array break byref eval-test iifs matrices metaa ongoto \
	         uds hash pass1 call_tau short-circuit strings stack-test \
           replace-test read-data proc optchk letbug ref ptr \
           trycatch chain

test: ${bin_PROGRAMS}
	@for utest in $(UNIT_TESTS); do                             \
    ./${bin_PROGRAMS} ${TEST_DIR}/$${utest}.bas > test.out;   \
    if cmp -s test.out ${TEST_DIR}/output/$${utest}.out; then \
      echo $${utest} ✓;                                      \
    else                                                      \
      echo $${utest} ✘;                                      \
      cat test.out;                                           \
    fi ;                                                      \
  done;
