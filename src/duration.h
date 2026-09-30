struct DurationParts {
    bool negative;
    int_64 days;
    int_64 hours;
    int_64 minutes;
    int_64 seconds;
    int_64 milliseconds;
}

function duration_internal_decimal(int_64 value) -> string {
    string[] digits := ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
    if (value == 0) {
        return "0";
    }
    result := "";
    while (value > 0) {
        int_64 digit := value % 10;
        result = digits[digit] + result;
        value = value / 10;
    }
    return result;
}

function duration_internal_pad2(int_64 value) -> string {
    if (value < 10) {
        return "0" + duration_internal_decimal(value);
    }
    return duration_internal_decimal(value);
}

function duration_internal_pad3(int_64 value) -> string {
    if (value < 10) {
        return "00" + duration_internal_decimal(value);
    }
    if (value < 100) {
        return "0" + duration_internal_decimal(value);
    }
    return duration_internal_decimal(value);
}

function duration_internal_parts(int_64 milliseconds) -> DurationParts {
    bool negative := milliseconds < 0;
    int_64 remaining := milliseconds;
    if (negative) {
        remaining = -remaining;
    }

    int_64 days := remaining / 86400000;
    remaining = remaining % 86400000;
    int_64 hours := remaining / 3600000;
    remaining = remaining % 3600000;
    int_64 minutes := remaining / 60000;
    remaining = remaining % 60000;
    int_64 seconds := remaining / 1000;
    remaining = remaining % 1000;

    return DurationParts {
        negative: negative,
        days: days,
        hours: hours,
        minutes: minutes,
        seconds: seconds,
        milliseconds: remaining
    };
}

function duration_internal_format(int_64 milliseconds) -> string {
    DurationParts parts := duration_internal_parts(milliseconds);
    result := "";
    if (parts.negative) {
        result = "-";
    }

    bool has_component := false;
    if (parts.days > 0) {
        result = result + duration_internal_decimal(parts.days) + "d";
        has_component = true;
    }
    if (parts.hours > 0) {
        if (has_component) { result = result + " "; }
        result = result + duration_internal_decimal(parts.hours) + "h";
        has_component = true;
    }
    if (parts.minutes > 0) {
        if (has_component) { result = result + " "; }
        result = result + duration_internal_decimal(parts.minutes) + "m";
        has_component = true;
    }
    if (parts.seconds > 0) {
        if (has_component) { result = result + " "; }
        result = result + duration_internal_decimal(parts.seconds) + "s";
        has_component = true;
    }
    if (parts.milliseconds > 0 || !has_component) {
        if (has_component) { result = result + " "; }
        result = result + duration_internal_decimal(parts.milliseconds) + "ms";
    }
    return result;
}

function duration_internal_format_clock(int_64 milliseconds) -> string {
    DurationParts parts := duration_internal_parts(milliseconds);
    int_64 hours := parts.days * 24 + parts.hours;
    result := "";
    if (parts.negative) {
        result = "-";
    }
    return result
    + duration_internal_pad2(hours) + ":"
    + duration_internal_pad2(parts.minutes) + ":"
    + duration_internal_pad2(parts.seconds) + "."
    + duration_internal_pad3(parts.milliseconds);
}

function duration_internal_seconds(int_64 value) -> int_64 {
    return value * 1000;
}

function duration_internal_minutes(int_64 value) -> int_64 {
    return value * 60000;
}

function duration_internal_hours(int_64 value) -> int_64 {
    return value * 3600000;
}

function duration_internal_days(int_64 value) -> int_64 {
    return value * 86400000;
}

struct DurationFacade {
    function parts(int_64 milliseconds) -> DurationParts;
    function format(int_64 milliseconds) -> string;
    function format_clock(int_64 milliseconds) -> string;
    function seconds(int_64 value) -> int_64;
    function minutes(int_64 value) -> int_64;
    function hours(int_64 value) -> int_64;
    function days(int_64 value) -> int_64;
}

function DurationFacade::parts(int_64 milliseconds) -> DurationParts { return duration_internal_parts(milliseconds); }
function DurationFacade::format(int_64 milliseconds) -> string { return duration_internal_format(milliseconds); }
function DurationFacade::format_clock(int_64 milliseconds) -> string { return duration_internal_format_clock(milliseconds); }
function DurationFacade::seconds(int_64 value) -> int_64 { return duration_internal_seconds(value); }
function DurationFacade::minutes(int_64 value) -> int_64 { return duration_internal_minutes(value); }
function DurationFacade::hours(int_64 value) -> int_64 { return duration_internal_hours(value); }
function DurationFacade::days(int_64 value) -> int_64 { return duration_internal_days(value); }

function duration_internal_facade() -> DurationFacade { return DurationFacade {}; }

DurationFacade duration := duration_internal_facade();
