#include <iostream>

enum Status { SUCCESS, ERROR, WARNING };

struct Time {
    int hours;
    int minutes;
    int seconds;
};

Status input(Time* time) {
    Status state = SUCCESS;
    char colon;
    std::cin >> time->hours >> colon
        >> time->minutes >> colon
        >> time->seconds;

    return state;
}

Status set_values(Time* time, int hours, int minutes, int seconds) {
    Status state = SUCCESS;
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
    return state;
}

Status check(const Time* time) {
    if (time->hours < 0 || time->hours >= 24 ||
        time->minutes < 0 || time->minutes >= 60 ||
        time->seconds < 0 || time->seconds >= 60) {
        return ERROR;
    }
    return SUCCESS;
}

Status convert(Time* time) {
    while (time->seconds >= 60) {
        time->seconds -= 60;
        time->minutes++;
    }
    while (time->minutes >= 60) {
        time->minutes -= 60;
        time->hours++;
        if (time->hours >= 24) {
            time->hours %= 24; // перекидывание после 24 часов
        }
    }
    return SUCCESS;
}

Status add_hours(Time* time, int hours) {
    time->hours += hours;
    return convert(time);
}

Status add_minutes(Time* time, int minutes) {
    time->minutes += minutes;
    return convert(time);
}

Status add_seconds(Time* time, int seconds) {
    time->seconds += seconds;
    return convert(time);
}

int compare(const Time* time1, const Time* time2) {
    if (time1->hours > time2->hours) return 1;
    if (time1->hours < time2->hours) return -1;

    if (time1->minutes > time2->minutes) return 1;
    if (time1->minutes < time2->minutes) return -1;

    if (time1->seconds > time2->seconds) return 1;
    if (time1->seconds < time2->seconds) return -1;

    return 0; // времена равны
}

Status assign(Time* time1, const Time* time2) {
    Status state = SUCCESS;
    if (time2 == nullptr) {
        state = ERROR;
    }
    else {
        time1->hours = time2->hours;
        time1->minutes = time2->minutes;
        time1->seconds = time2->seconds;
    }
    return state;
}

Status output(const Time* time) {
    Status state = SUCCESS;
    if (time == nullptr) {
        state = ERROR;
    }
    else {
        std::cout << time->hours << ":"
            << time->minutes << ":"
            << time->seconds << std::endl;
    }

    return state;
}

int main() {
    Time time1 = { 11, 12, 57 }, time2;
    output(&time1);
    assign(&time2, &time1);
    output(&time2);

    input(&time1);

    output(&time1);

    set_values(&time2, 6, 12, 32);
    output(&time2);

    add_hours(&time2, 4);
    output(&time2);

    return 0;
}
