// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#include <assert.h>

#include "sdd_internal.h"

struct SockAddr sdd_parse_addr(const char *input) {
  assert(input);

  struct SockAddr sa;

  size_t len = strlen(input);

  if (len == 0 || len > 100) return sa;

  sa.family = PF_UNIX;

  sa.addr.unix = (struct sockaddr_un){};

  strncpy(sa.addr.unix.sun_path, input, len);

  // If it is using Linux abstract namespace then we need to set first byte to 0
  if (sa.addr.unix.sun_path[0] == '@') sa.addr.unix.sun_path[0] = 0;

  return sa;
}

size_t sdd_addr_size(struct SockAddr const * const sa) {
  switch (sa->family) {
    case PF_UNIX: return sizeof(sa->addr.unix);
    default: assert(0);
  }
}
