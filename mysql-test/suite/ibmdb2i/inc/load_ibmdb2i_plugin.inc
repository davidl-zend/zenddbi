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
# Change Date:                                                                 #
# Change:                                                                      #
################################################################################

--disable_warnings
--disable_query_log
install plugin ibmdb2i soname "ha_ibmdb2i.so";
--enable_query_log
--enable_warnings
