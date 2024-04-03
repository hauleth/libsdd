// SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
//
// SPDX-License-Identifier: MIT

#ifndef SDD_H
#define SDD_H 1

#define SD_EMERG   "<0>"  /* system is unusable */
#define SD_ALERT   "<1>"  /* action must be taken immediately */
#define SD_CRIT    "<2>"  /* critical conditions */
#define SD_ERR     "<3>"  /* error conditions */
#define SD_WARNING "<4>"  /* warning conditions */
#define SD_NOTICE  "<5>"  /* normal but significant condition */
#define SD_INFO    "<6>"  /* informational */
#define SD_DEBUG   "<7>"  /* debug-level messages */

int sd_notify(
  int unset_environment,
  const char *state
);

int sd_notifyf(
  int unset_environment,
  const char *format,
  ...
);

int sd_pid_notify(
  pid_t pid,
  int unset_environment,
  const char *state
);

int sd_pid_notifyf(
  pid_t pid,
  int unset_environment,
  const char *format,
  ...
);

int sd_pid_notify_with_fds(
  pid_t pid,
  int unset_environment,
  const char *state,
  const int *fds,
  unsigned n_fds
);

int sd_pid_notifyf_with_fds(
  pid_t pid,
  int unset_environment,
  const int *fds,
  size_t n_fds,
  const char *format,
  ...
);

int sd_notify_barrier(
  int unset_environment,
  uint64_t timeout
);

int sd_pid_notify_barrier(
  pid_t pid,
  int unset_environment,
  uint64_t timeout
);

#endif /* SDD_H */
