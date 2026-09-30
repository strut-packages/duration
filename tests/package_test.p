include <duration>;

function main() -> int {
    DurationParts parts := duration.parts(-93784005);
    print(parts.negative);
    print(parts.days);
    print(parts.hours);
    print(parts.minutes);
    print(parts.seconds);
    print(parts.milliseconds);
    print(duration.format(-93784005));
    print(duration.format(120000));
    print(duration.format(0));
    print(duration.format_clock(-3723004));
    print(duration.days(2));
    return 0;
}
