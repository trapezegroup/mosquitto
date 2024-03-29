add_subdirectory(cpp)

option(WITH_THREADING "Include client library threading support?" ON)
if (${WITH_THREADING} STREQUAL ON)
	add_definitions("-DWITH_THREADING")
else (${WITH_THREADING} STREQUAL ON)
	set (PTHREAD_LIBRARIES "")
	set (PTHREAD_INCLUDE_DIR "")
endif (${WITH_THREADING} STREQUAL ON)

include_directories(${mosquitto_SOURCE_DIR} ${mosquitto_SOURCE_DIR}/lib
			${STDBOOL_H_PATH} ${STDINT_H_PATH}
			${OPENSSL_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})
link_directories(${mosquitto_SOURCE_DIR}/lib)

set ( SOURCE_FILES
    logging_mosq.c logging_mosq.h
    memory_mosq.c memory_mosq.h
    messages_mosq.c messages_mosq.h
    mosquitto.c mosquitto.h
    mosquitto_internal.h
    mqtt3_protocol.h
    net_mosq.c net_mosq.h
    read_handle.c read_handle.h
    read_handle_client.c
    read_handle_shared.c
    send_client_mosq.c
    send_mosq.c send_mosq.h
    socks_mosq.c
    srv_mosq.c
    thread_mosq.c
    time_mosq.c
    tls_mosq.c
    util_mosq.c util_mosq.h
    will_mosq.c will_mosq.h
    )

if (WIN32)
  set (SOURCE_FILES ${SOURCE_FILES} pthread_win32.cpp pthread_win32.h)
endif (WIN32)

add_library(libmosquitto STATIC ${SOURCE_FILES})

set (LIBRARIES ${OPENSSL_LIBRARIES} ${PTHREAD_LIBRARIES})

if (UNIX AND NOT APPLE)
	find_library(LIBRT rt)
	if (LIBRT)
		set (LIBRARIES ${LIBRARIES} rt)
	endif (LIBRT)
endif (UNIX AND NOT APPLE)

if (WIN32)
	set (LIBRARIES ${LIBRARIES} ws2_32)
endif (WIN32)

if (${WITH_SRV} STREQUAL ON)
	# Simple detect c-ares
	find_path(ARES_HEADER ares.h)
	if (ARES_HEADER)
		add_definitions("-DWITH_SRV")
		set (LIBRARIES ${LIBRARIES} cares)
	else (ARES_HEADER)
		message(WARNING "c-ares library not found.")
	endif (ARES_HEADER)
endif (${WITH_SRV} STREQUAL ON)

target_link_libraries(libmosquitto ${LIBRARIES})

set_target_properties(libmosquitto PROPERTIES
	OUTPUT_NAME mosquitto
	VERSION ${VERSION}
	SOVERSION 1
)

install(TARGETS libmosquitto RUNTIME DESTINATION "${BINDIR}" LIBRARY DESTINATION "${LIBDIR}" ARCHIVE DESTINATION "${LIBDIR}")
install(FILES mosquitto.h DESTINATION "${INCLUDEDIR}")

if (UNIX)
	install(CODE "EXEC_PROGRAM(/sbin/ldconfig)")
endif (UNIX)
