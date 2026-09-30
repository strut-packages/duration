include <duration>;

function main() -> int {
    int_64 elapsed := duration.hours(1) + duration.minutes(2) + duration.seconds(3) + 4;
    print(duration.format(elapsed));
    print(duration.format_clock(elapsed));
    return 0;
}
