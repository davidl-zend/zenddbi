#SET(IBMDB2I_PLUGIN_STATIC  "ibmdb2i")
SET(IBMDB2I_PLUGIN_DYNAMIC "ha_ibmdb2i")
SET(IBMDB2I_SOURCES  ha_ibmdb2i.cc db2i_ileBridge.cc db2i_conversion.cc 
                     db2i_blobCollection.cc db2i_file.cc db2i_charsetSupport.cc 
                     db2i_collationSupport.cc db2i_errors.cc db2i_constraints.cc 
                     db2i_rir.cc db2i_sqlStatementStream.cc db2i_ioBuffers.cc 
                     db2i_myconv.cc)

MYSQL_ADD_PLUGIN(ibmdb2i ${IBMDB2I_SOURCES} STORAGE_ENGINE)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include 
                    ${CMAKE_SOURCE_DIR}/sql
                    ${CMAKE_SOURCE_DIR}/regex
                    ${CMAKE_SOURCE_DIR}/extra/yassl/include
                    ${CMAKE_SOURCE_DIR}/include400
                    )
