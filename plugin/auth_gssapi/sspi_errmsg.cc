/* Copyright (c) 2015, Shuang Qiu, Robbie Hardwood,
Vladislav Vaintroub & MariaDB Corporation

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include <windows.h>
#include <stdio.h>

#define ERRSYM(x) {x, #x}
static struct {
  int error;
  const char *sym;
} error_symbols[] =
{
  ERRSYM(SEC_E_OK),
  ERRSYM(SEC_E_INSUFFICIENT_MEMORY),
  ERRSYM(SEC_E_INVALID_HANDLE),
  ERRSYM(SEC_E_UNSUPPORTED_FUNCTION),
  ERRSYM(SEC_E_TARGET_UNKNOWN),
  ERRSYM(SEC_E_INTERNAL_ERROR),
  ERRSYM(SEC_E_SECPKG_NOT_FOUND),
  ERRSYM(SEC_E_NOT_OWNER),
  ERRSYM(SEC_E_CANNOT_INSTALL),
  ERRSYM(SEC_E_INVALID_TOKEN),
  ERRSYM(SEC_E_CANNOT_PACK),
  ERRSYM(SEC_E_QOP_NOT_SUPPORTED),
  ERRSYM(SEC_E_NO_IMPERSONATION),
  ERRSYM(SEC_E_LOGON_DENIED),
  ERRSYM(SEC_E_UNKNOWN_CREDENTIALS),
  ERRSYM(SEC_E_NO_CREDENTIALS),
  ERRSYM(SEC_E_MESSAGE_ALTERED),
  ERRSYM(SEC_E_OUT_OF_SEQUENCE),
  ERRSYM(SEC_E_NO_AUTHENTICATING_AUTHORITY),
  ERRSYM(SEC_E_BAD_PKGID),
  ERRSYM(SEC_E_CONTEXT_EXPIRED),
  ERRSYM(SEC_E_INCOMPLETE_MESSAGE),
  ERRSYM(SEC_E_INCOMPLETE_CREDENTIALS),
  ERRSYM(SEC_E_BUFFER_TOO_SMALL),
  ERRSYM(SEC_E_WRONG_PRINCIPAL),
  ERRSYM(SEC_E_TIME_SKEW),
  ERRSYM(SEC_E_UNTRUSTED_ROOT),
  ERRSYM(SEC_E_ILLEGAL_MESSAGE),
  ERRSYM(SEC_E_CERT_UNKNOWN),
  ERRSYM(SEC_E_CERT_EXPIRED),
  ERRSYM(SEC_E_ENCRYPT_FAILURE),
  ERRSYM(SEC_E_DECRYPT_FAILURE),
  ERRSYM(SEC_E_ALGORITHM_MISMATCH),
  ERRSYM(SEC_E_SECURITY_QOS_FAILED),
  ERRSYM(SEC_E_UNFINISHED_CONTEXT_DELETED),
  ERRSYM(SEC_E_NO_TGT_REPLY),
  ERRSYM(SEC_E_NO_IP_ADDRESSES),
  ERRSYM(SEC_E_WRONG_CREDENTIAL_HANDLE),
  ERRSYM(SEC_E_CRYPTO_SYSTEM_INVALID),
  ERRSYM(SEC_E_MAX_REFERRALS_EXCEEDED),
  ERRSYM(SEC_E_MUST_BE_KDC),
  ERRSYM(SEC_E_STRONG_CRYPTO_NOT_SUPPORTED),
  ERRSYM(SEC_E_TOO_MANY_PRINCIPALS),
  ERRSYM(SEC_E_NO_PA_DATA),
  ERRSYM(SEC_E_PKINIT_NAME_MISMATCH),
  ERRSYM(SEC_E_SMARTCARD_LOGON_REQUIRED),
  ERRSYM(SEC_E_SHUTDOWN_IN_PROGRESS),
  ERRSYM(SEC_E_KDC_INVALID_REQUEST),
  ERRSYM(SEC_E_KDC_UNABLE_TO_REFER),
  ERRSYM(SEC_E_KDC_UNKNOWN_ETYPE),
  ERRSYM(SEC_E_UNSUPPORTED_PREAUTH),
  ERRSYM(SEC_E_DELEGATION_REQUIRED),
  ERRSYM(SEC_E_BAD_BINDINGS),
  ERRSYM(SEC_E_MULTIPLE_ACCOUNTS),
  ERRSYM(SEC_E_NO_KERB_KEY),
  ERRSYM(SEC_E_CERT_WRONG_USAGE),
  ERRSYM(SEC_E_DOWNGRADE_DETECTED),
  ERRSYM(SEC_E_SMARTCARD_CERT_REVOKED),
  ERRSYM(SEC_E_ISSUING_CA_UNTRUSTED),
  ERRSYM(SEC_E_REVOCATION_OFFLINE_C),
  ERRSYM(SEC_E_PKINIT_CLIENT_FAILURE),
  ERRSYM(SEC_E_SMARTCARD_CERT_EXPIRED),
  ERRSYM(SEC_E_NO_S4U_PROT_SUPPORT),
  ERRSYM(SEC_E_CROSSREALM_DELEGATION_FAILURE),
  ERRSYM(SEC_E_REVOCATION_OFFLINE_KDC),
  ERRSYM(SEC_E_ISSUING_CA_UNTRUSTED_KDC),
  ERRSYM(SEC_E_KDC_CERT_EXPIRED),
  ERRSYM(SEC_E_KDC_CERT_REVOKED),
  ERRSYM(SEC_E_INVALID_PARAMETER),
  ERRSYM(SEC_E_DELEGATION_POLICY),
  ERRSYM(SEC_E_POLICY_NLTM_ONLY),
  ERRSYM(SEC_E_NO_CONTEXT),
  ERRSYM(SEC_E_PKU2U_CERT_FAILURE),
  ERRSYM(SEC_E_MUTUAL_AUTH_FAILED),
  ERRSYM(SEC_E_NO_SPM),
  ERRSYM(SEC_E_NOT_SUPPORTED),
  {0,0}
};

void sspi_errmsg(int err, char *buf, size_t size)
{
  buf[size - 1] = 0;
  size_t len;

  for (size_t i= 0; error_symbols[i].sym; i++)
  {
    if (error_symbols[i].error == err)
    {
      size_t len= strlen(error_symbols[i].sym);
      if (len + 2 < size)
      {
        memcpy(buf, error_symbols[i].sym, len);
        buf[len]= ' ';
        buf += len + 1;
        size-= len + 1;
      }
      break;
    }
  }

  len = FormatMessageA(
    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
    err, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
    buf, size, NULL);

  if(len > 0)
  {
    /* Trim trailing \n\r*/
    char *p;
    for(p= buf + len;p > buf && (*p == '\n' || *p=='\r' || *p == 0);p--)
      *p= 0;
  }
}
