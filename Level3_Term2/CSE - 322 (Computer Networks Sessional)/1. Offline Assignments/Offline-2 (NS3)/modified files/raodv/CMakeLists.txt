build_lib(
  LIBNAME raodv  # Change the library name to avoid conflicts
  SOURCE_FILES
    helper/raodv-helper.cc
    model/aodv-dpd.cc
    model/aodv-id-cache.cc
    model/aodv-neighbor.cc
    model/raodv-packet.cc
    model/raodv-routing-protocol.cc  # Reference RAODV-specific files
    model/aodv-rqueue.cc
    model/raodv-rtable.cc
  HEADER_FILES
    helper/raodv-helper.h  # Update to match renamed headers
    model/aodv-dpd.h
    model/aodv-id-cache.h
    model/aodv-neighbor.h
    model/raodv-packet.h
    model/raodv-routing-protocol.h  # Match renamed protocol header
    model/aodv-rqueue.h
    model/raodv-rtable.h
  LIBRARIES_TO_LINK
    ${libapplications}
    ${libinternet-apps}
    ${libwifi}
  TEST_SOURCES
    test/aodv-id-cache-test-suite.cc
    test/aodv-regression.cc
    test/aodv-test-suite.cc
    test/loopback.cc
    test/bug-772.cc
)
