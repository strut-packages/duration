include <duration>;

function main() -> int {
    int_64 elapsed := duration_hours(1) + duration_minutes(2) + duration_seconds(3) + 4;
    print(duration_format(elapsed));
    print(duration_format_clock(elapsed));
    return 0;
}
