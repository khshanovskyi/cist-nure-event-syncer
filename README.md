# cist-nure-event-syncer
Syncronizes events from cist.nure with calendar.google

Requires CMake 4.3+, Ninja, a C++20 compiler, and vcpkg. Set `VCPKG_ROOT` to your vcpkg checkout before configuring:

```sh
export VCPKG_ROOT="$HOME/vcpkg"
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

The Debug preset enables ASan, UBSan, and testing. Release disables them and skips the `tests` vcpkg feature:

```sh
cmake --preset release
cmake --build --preset release
```

In CLion, enable the `debug` or `release` CMake preset and ensure the CMake environment includes `VCPKG_ROOT`. Ninja must be on `PATH` or selected through CLion's toolchain. The first configure installs dependencies from `vcpkg.json`, including libpqxx for PostgreSQL.

The repository is at Step 1 of [implementation-plan.md](implementation-plan.md): `libs/common` (env and logging helpers), and `cist-syncer` and `tg-bot` executables that only load and log their configuration. Each module has tests; the service tests check that every vcpkg library compiles and links. See the plan for the remaining modules and the PostgreSQL setup.
