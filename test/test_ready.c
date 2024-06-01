// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#include <stdio.h>

#include <sdd.h>

int main() {
  sd_notify(0, "READY=1");
  return 0;
}
