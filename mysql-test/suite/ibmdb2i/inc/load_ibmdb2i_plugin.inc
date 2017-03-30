################################################################################
# inc/load_ibmdb2i_plugin.inc                                                  #
#                                                                              #
# Purpose:                                                                     #
#   Load ibmdb2i plugin				                  	       #
#                                                                              #
#------------------------------------------------------------------------------#
# Original Author: David Lowes                                                 #
# Original Date: 2017-03-07                                                    #
# Change Author:                                                               #
# Change Date: 2017-03-30                                                      #
# Change:                                                                      #
################################################################################

--disable_warnings
--disable_query_log
--disable_result_log
--disable_abort_on_error
eval INSTALL PLUGIN ibmdb2i SONAME "ha_ibmdb2i.so";
--enable_abort_on_error
--enable_result_log
--enable_query_log
--enable_warnings

