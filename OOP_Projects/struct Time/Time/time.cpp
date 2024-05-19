#include <iostream>

enum Status { SUCCESS, ERROR, WARNING };

struct Time {
    int hours;
    int minutes;
    int seconds;
};

Status check(const Time* time) {
    if (time->hours < 0 || time->hours >= 24 ||
        time->minutes < 0 || time->minutes >= 60 ||
        time->seconds < 0 || time->seconds >= 60) {
        return ERROR;
    }
    return SUCCESS;
}

Status input(Time* time) {
    Status state = SUCCESS;
    char colon;
    std::cin >> time->hours >> colon
        >> time->minutes >> colon
        >> time->seconds;
    if (check(time) == ERROR) {
        std::cout << "Ошибка: введено некорректное время." << std::endl;
        exit(1);
    }
    return state;
}

Status set_values(Time* time, int hours, int minutes, int seconds) {
    Status state = SUCCESS;
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
    return state;
}

Status convert(Time* time) {
    while (time->seconds >= 60) {
        time->seconds -= 60;
        time->minutes++;
    }
    while (time->minutes >= 60) {
        time->minutes -= 60;
        time->hours++;
    }
    while (time->hours >= 24) {
        time->hours %= 24;
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

    return 0; // время равно
}

Status assign(Time* time1, const Time* time2) {
    Status state = SUCCESS;
    if (time2 == nullptr) {
        state = ERROR;
        exit(1);
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
        exit(1);
    }
    else {
        Time tempTime = *time;
        convert(&tempTime);

        std::cout << tempTime.hours << ":"
            << tempTime.minutes << ":"
            << tempTime.seconds << std::endl;
    }
    return state;
}

int main() {
    setlocale(LC_ALL, "RU");

    Time time1 = { 11, 12, 57 }, time2;
    output(&time1);
    assign(&time2, &time1);
    output(&time2);

    if (input(&time1) == ERROR) {
        return 1;
    }

    output(&time1);

    set_values(&time2, 23, 42, 32);
    output(&time2);

    add_hours(&time2, 4);
    output(&time2);

    int comparison = compare(&time1, &time2);

    if (comparison == 0) {
        std::cout << "Time1 равно Time2" << std::endl;
    }
    if (comparison == 1) {
        std::cout << "Time1 больше чем Time2" << std::endl;
    }
    if (comparison == -1) {
        std::cout << "Time1 меньше чем Time2" << std::endl;
    }

    system("pause");
    return 0;
} //end
