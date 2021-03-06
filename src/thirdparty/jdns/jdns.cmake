if (WIN32)
	if (MSVC)
		set(LIBS ${LIBS} Ws2_32.lib Advapi32.lib)
	elseif (MINGW)
		set(LIBS ${LIBS} -lWs2_32 -lAdvapi32)
	endif (MSVC)
endif (WIN32)

set(QT_USE_QTNETWORK YES)

set(HEADERS ${HEADERS}
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/qjdns.h"
	)

set(SOURCES ${SOURCES}
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/jdns_util.c"
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/jdns_packet.c"
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/jdns_mdnsd.c"
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/jdns_sys.c"
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/jdns.c"
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/qjdns_sock.cpp"
	"${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/qjdns.cpp"
	)

qt4_generate_moc("${CMAKE_SOURCE_DIR}/src/thirdparty/jdns/qjdns.cpp"
	"${CMAKE_CURRENT_BINARY_DIR}/qjdns.moc")
