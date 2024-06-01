<!--
SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>

SPDX-License-Identifier: MIT
-->

# systemd-daemons helper library

In response of [CSV-2024-3094][] there was [rejected proposal][pr-32028] to
`libsystemd` to reduce amount of dependencies, as most of systemd daemons do not
require features provided by these dependencies. Goal of this project is to
provide basic features of `libsystemd` without any dependencies.

## Supported API

- [x] syslog macros
- [x] `sd_notify*`
- [ ] `sd_watchdog_enabled`
- [ ] `sd_journal_print*`, `sd_journal_perror*`
- [ ] `sd_booted`

## License

MIT - I have chosen this license over the "original" LGPL because I want to make
it easier to embedded in any software, including commercial one, for sake of
better integration with systemd (or systemd-compatible tools).

[CSV-2024-3094]: https://security-tracker.debian.org/tracker/CVE-2024-3094
[pr-32028]: https://github.com/systemd/systemd/issues/32028
