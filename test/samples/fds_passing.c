// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include <sdd.h>

#define FD 0

int main() {
  int fds[] = { FD };
  int result = sd_pid_notify_with_fds(0, 0, "FDSTORE=1", fds, 1);

  if (result < 0) {
    printf("Error: %d\n", result);
    return 1;
  }

  return 0;
}

