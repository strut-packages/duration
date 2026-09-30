# duration

Official integer duration construction and formatting for Strut.

Durations are represented as signed `int_64` milliseconds. The package does not model calendar months, years, dates, or time zones.

## Install

```sh
strut install duration
```

For a local checkout:

```sh
strut add /path/to/duration
```

## Usage

```strut
include <duration>;

function main() -> int {
    int_64 elapsed := duration_hours(1) + duration_minutes(2) + duration_seconds(3) + 4;
    print(duration_format(elapsed));       // 1h 2m 3s 4ms
    print(duration_format_clock(elapsed)); // 01:02:03.004
    return 0;
}
```

`duration_parts` decomposes a value into sign, days, hours, minutes, seconds, and milliseconds. `duration_format` emits non-zero units, while `duration_format_clock` emits `HH:MM:SS.mmm` with hours allowed to exceed 23.

Unit constructors use normal signed integer arithmetic. Callers are responsible for keeping multiplication within `int_64` range. The minimum `int_64` value cannot be negated and is outside the formatting contract.

## Test

```sh
python3 tests/run.py --strut /path/to/strut
```
