include <duration>;

function main() -> int {
    DurationParts parts := duration_parts(-93784005);
    print(parts.negative);
    print(parts.days);
    print(parts.hours);
    print(parts.minutes);
    print(parts.seconds);
    print(parts.milliseconds);
    print(duration_format(-93784005));
    print(duration_format(120000));
    print(duration_format(0));
    print(duration_format_clock(-3723004));
    print(duration_days(2));
    return 0;
}
