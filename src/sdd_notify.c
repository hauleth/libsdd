// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>

#include <sdd.h>

#include "sdd_internal.h"

int sd_notify(int unset_environment, const char *state) {
  return sd_pid_notify_with_fds(0, unset_environment, state, NULL, 0);
}

int sd_pid_notify(pid_t pid, int unset_environment, const char *state) {
  return sd_pid_notify_with_fds(pid, unset_environment, state, NULL, 0);
}

int sd_pid_notify_with_fds(
  pid_t pid,
  int unset_environment,
  const char *state,
  const int *fds,
  unsigned n_fds
) {
  const char *e = NULL;
  int result = 0;

  e = getenv(NOTIFY_SOCKET);
  // There is no socket, so this should be a no-op call
  if (!e)
    return 0;

  if (unset_environment) {
    unsetenv(NOTIFY_SOCKET);
  }

  struct SockAddr sa = sdd_parse_addr(e);

  int sock = socket(sa.family, SOCK_DGRAM, 0);
  if (sock < 0)
    return -1;

  struct iovec iov = IOVEC_MAKE_STRING(state);
  struct msghdr msg = {
    .msg_name = &sa.addr,
    .msg_namelen = sdd_addr_size(&sa),
    .msg_iov = &iov,
    .msg_iovlen = 1,
  };

  char *buf = NULL;

  if (n_fds > 0) {
    size_t size = n_fds * sizeof(*fds);
    size_t space = CMSG_SPACE(size);
    buf = malloc(space);

    if (!buf) {
      perror("Allocation failed");
      return -1;
    }

    msg.msg_control = buf;
    msg.msg_controllen = space;

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    if (cmsg == NULL) {
      result = -1;
      goto cmsg_buf_free;
    }
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(size);

    memcpy(CMSG_DATA(cmsg), fds, size);

    msg.msg_controllen = cmsg->cmsg_len;
  }

  result = sendmsg(sock, &msg, 0);

cmsg_buf_free:
  if (buf) free(buf);

  return result;
}

int pid_vnotifyf_with_fds(
  pid_t pid,
  int unset_environment,
  const int *fds,
  size_t n_fds,
  const char *format,
  va_list args
) {
  char *state;
  if (vasprintf(&state, format, args) < 0) {
    return -1;
  }

  int ret = sd_pid_notify_with_fds(pid, unset_environment, state, fds, n_fds);

  free(state);

  return ret;
}

#define passthrough(pid, unset_environment, fds, n_fds, format) \
  do { \
    va_list args; \
    va_start(args, format); \
    int ret = pid_vnotifyf_with_fds(pid, unset_environment, fds, n_fds, format, args); \
    va_end(args); \
    return ret; \
  } while (0)

int sd_notifyf(int unset_environment, const char *format, ...) {
  passthrough(0, unset_environment, NULL, 0, format);
}

int sd_pid_notifyf(pid_t pid, int unset_environment, const char *format, ...) {
  passthrough(pid, unset_environment, NULL, 0, format);
}

int sd_pid_notifyf_with_fds(
  pid_t pid,
  int unset_environment,
  const int *fds,
  size_t n_fds,
  const char *format,
  ...
) {
  passthrough(pid, unset_environment, fds, n_fds, format);
}

int sd_notify_barrier(
  int unset_environment,
  uint64_t timeout
) { return sd_pid_notify_barrier(0, unset_environment, timeout); }

int sd_pid_notify_barrier(
  pid_t pid,
  int unset_environment,
  uint64_t timeout
) {
  // Not yet implemented
  return -1;
}
