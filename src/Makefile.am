# Copyright (c) 2013-2016 The Lyokocoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

LYOKOCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

LYOKOCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
LYOKOCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LYOKOCOIN_SEEDER_INCLUDES = -I$(srcdir)/seeder
LYOKOCOIN_SEEDER_INCLUDES += $(LYOKOCOIN_INCLUDES)

LIBLYOKOCOIN_SERVER=liblyokocoin_server.a
LIBLYOKOCOIN_COMMON=liblyokocoin_common.a
LIBLYOKOCOIN_CONSENSUS=liblyokocoin_consensus.a
LIBLYOKOCOIN_CLI=liblyokocoin_cli.a
LIBLYOKOCOIN_UTIL=liblyokocoin_util.a
LIBLYOKOCOIN_CRYPTO=crypto/liblyokocoin_crypto.a
LIBLYOKOCOINQT=qt/liblyokocoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBLYOKOCOIN_ZMQ=liblyokocoin_zmq.a
endif
if BUILD_LYOKOCOIN_LIBS
LIBLYOKOCOINCONSENSUS=liblyokocoinconsensus.la
endif
if BUILD_LYOKOCOIN_SEEDER
LIBLYOKOCOIN_SEEDER=liblyokocoin_seeder.a
endif
if ENABLE_WALLET
LIBLYOKOCOIN_WALLET=liblyokocoin_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBLYOKOCOIN_CRYPTO) \
  $(LIBLYOKOCOIN_UTIL) \
  $(LIBLYOKOCOIN_COMMON) \
  $(LIBLYOKOCOIN_CONSENSUS) \
  $(LIBLYOKOCOIN_SERVER) \
  $(LIBLYOKOCOIN_CLI) \
  $(LIBLYOKOCOIN_SEEDER) \
  $(LIBLYOKOCOIN_WALLET) \
  $(LIBLYOKOCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBLYOKOCOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_LYOKOCOIND
  bin_PROGRAMS += lyokocoind
endif

if BUILD_LYOKOCOIN_SEEDER
  bin_PROGRAMS += lyokocoin-seeder
endif

if BUILD_LYOKOCOIN_UTILS
  bin_PROGRAMS += lyokocoin-cli lyokocoin-tx
endif

.PHONY: FORCE check-symbols check-security
# lyokocoin core #
LYOKOCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  cashaddr.h \
  cashaddrenc.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  config.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  dstencode.h \
  fs.h \
  globals.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/misc.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/tojson.h \
  rpc/register.h \
  scheduler.h \
  script/scriptcache.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/finaltx.h \
  wallet/rpcdump.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) "$(builddir)/obj"
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
liblyokocoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between lyokocoind and lyokocoin-qt
liblyokocoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
liblyokocoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_server_a_SOURCES = \
  addrman.cpp \
  addrdb.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  config.cpp \
  globals.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/abc.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/scriptcache.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(LYOKOCOIN_CORE_H)

if ENABLE_ZMQ
liblyokocoin_zmq_a_CPPFLAGS = $(LYOKOCOIN_INCLUDES) $(ZMQ_CFLAGS)
liblyokocoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between lyokocoind and lyokocoin-qt, but only linked
# when wallet enabled
liblyokocoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
liblyokocoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/finaltx.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  $(LYOKOCOIN_CORE_H)

# crypto primitives library
crypto_liblyokocoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_liblyokocoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_liblyokocoin_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

if USE_ASM
crypto_liblyokocoin_crypto_a_SOURCES += crypto/sha256_sse4.cpp
endif

# consensus: shared between all executables that validate any consensus rules.
liblyokocoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
liblyokocoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/lyokocoinconsensus.cpp \
  script/sighashtype.h \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between lyokocoind, and lyokocoin-qt and non-server tools
liblyokocoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
liblyokocoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  cashaddr.cpp \
  cashaddrenc.cpp \
  chainparams.cpp \
  config.cpp \
  coins.cpp \
  compressor.cpp \
  dstencode.cpp \
  globals.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(LYOKOCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
liblyokocoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
liblyokocoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  logging.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  uint256.cpp \
  uint256.h \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(LYOKOCOIN_CORE_H)

if GLIBC_BACK_COMPAT
liblyokocoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between lyokocoin-cli and lyokocoin-qt
liblyokocoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
liblyokocoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(LYOKOCOIN_CORE_H)

# seeder library
liblyokocoin_seeder_a_CPPFLAGS = $(AM_CPPFLAGS) $(PIE_FLAGS) $(LYOKOCOIN_SEEDER_INCLUDES)
liblyokocoin_seeder_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liblyokocoin_seeder_a_SOURCES = \
  seeder/lyokocoin.cpp \
  seeder/lyokocoin.h \
  seeder/compat.h \
  seeder/db.cpp \
  seeder/db.h \
  seeder/dns.cpp \
  seeder/dns.h \
  seeder/strlcpy.h \
  seeder/util.h

nodist_liblyokocoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# lyokocoind binary #
lyokocoind_SOURCES = lyokocoind.cpp
lyokocoind_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
lyokocoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
lyokocoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
lyokocoind_SOURCES += lyokocoind-res.rc
endif

lyokocoind_LDADD = \
  $(LIBLYOKOCOIN_SERVER) \
  $(LIBLYOKOCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBLYOKOCOIN_UTIL) \
  $(LIBLYOKOCOIN_WALLET) \
  $(LIBLYOKOCOIN_ZMQ) \
  $(LIBLYOKOCOIN_CONSENSUS) \
  $(LIBLYOKOCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

lyokocoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# lyokocoin-cli binary #
lyokocoin_cli_SOURCES = lyokocoin-cli.cpp
lyokocoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES) $(EVENT_CFLAGS)
lyokocoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
lyokocoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
lyokocoin_cli_SOURCES += lyokocoin-cli-res.rc
endif

lyokocoin_cli_LDADD = \
  $(LIBLYOKOCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBLYOKOCOIN_UTIL) \
  $(LIBLYOKOCOIN_CRYPTO)

lyokocoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# lyokocoin-seeder binary #
lyokocoin_seeder_SOURCES = seeder/main.cpp
lyokocoin_seeder_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_SEEDER_INCLUDES)
lyokocoin_seeder_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
lyokocoin_seeder_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

lyokocoin_seeder_LDADD = \
  $(LIBLYOKOCOIN_SEEDER) \
  $(LIBLYOKOCOIN_COMMON) \
  $(LIBLYOKOCOIN_UTIL) \
  $(LIBLYOKOCOIN_CRYPTO)

lyokocoin_seeder_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# lyokocoin-tx binary #
lyokocoin_tx_SOURCES = lyokocoin-tx.cpp
lyokocoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(LYOKOCOIN_INCLUDES)
lyokocoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
lyokocoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
lyokocoin_tx_SOURCES += lyokocoin-tx-res.rc
endif

lyokocoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBLYOKOCOIN_COMMON) \
  $(LIBLYOKOCOIN_UTIL) \
  $(LIBLYOKOCOIN_CONSENSUS) \
  $(LIBLYOKOCOIN_CRYPTO) \
  $(LIBSECP256K1)

lyokocoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# lyokocoinconsensus library #
if BUILD_LYOKOCOIN_LIBS
include_HEADERS = script/lyokocoinconsensus.h
liblyokocoinconsensus_la_SOURCES = $(crypto_liblyokocoin_crypto_a_SOURCES) $(liblyokocoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  liblyokocoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

liblyokocoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
liblyokocoinconsensus_la_LIBADD = $(LIBSECP256K1)
liblyokocoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_LYOKOCOIN_INTERNAL
liblyokocoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
