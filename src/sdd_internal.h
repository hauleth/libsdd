// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#ifndef SDD_INTERNAL_H
#define SDD_INTERNAL_H

#include <string.h>
#include <limits.h>

#include <unistd.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/socket.h>

#define NOTIFY_SOCKET "NOTIFY_SOCKET"

#define IOVEC_MAKE_STRING(str) { .iov_base = (void*)str, .iov_len = strlen(str) }

struct SockAddr {
  int family;
  union {
    struct sockaddr_un unix;
  } addr;
};

struct SockAddr sdd_parse_addr(char const *input);

size_t sdd_addr_size(struct SockAddr const * const sa);

enum SDD_ERRORS {
  UNIMPLEMENTED = INT_MIN,
  CMSG_FAILED,
  ALLOC_FAILED,
  SOCKET_NOT_AVAILABLE,
  IGNORE = 0,
};

#endif /* SDD_INTERNAL_H */
