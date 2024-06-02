// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <assert.h>

#include <sdd.h>

int main() {
  int result = sd_notify(0, "READY=1");

  if (result < 0) {
    printf("Error: %d\n", result);
    return 1;
  }

  return 0;
}
