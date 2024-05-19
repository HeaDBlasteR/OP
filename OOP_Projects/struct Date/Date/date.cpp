#include <iostream>

enum Status { SUCCESS, ERROR, WARNING };

struct Date {
    int day;
    int month;
    int year;
};

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    if (month == 2) {
        return is_leap_year(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

Status check(const Date* date) {
    if (date->day <= 0 || date->month <= 0 || date->month > 12 || date->year <= 0) {
        return ERROR;
    }
    if (date->day > days_in_month(date->month, date->year)) {
        return ERROR;
    }
    return SUCCESS;
}

Status input(Date* date) {
    Status state = SUCCESS;
    char slash;
    std::cin >> date->day >> slash
        >> date->month >> slash
        >> date->year;
    if (check(date) == ERROR) {
        std::cout << "Ошибка: введена некорректная дата." << std::endl;
        exit(1);
    }
    return state;
}

Status set_values(Date* date, int day, int month, int year) {
    Status state = SUCCESS;
    date->day = day;
    date->month = month;
    date->year = year;
    return state;
}

Status convert(Date* date) {
    while (date->day > days_in_month(date->month, date->year)) {
        date->day -= days_in_month(date->month, date->year);
        date->month++;
        if (date->month > 12) {
            date->month = 1;
            date->year++;
        }
    }
    return SUCCESS;
}

Status add_days(Date* date, int days) {
    int total_days = date->day + days;
    while (total_days > days_in_month(date->month, date->year)) {
        total_days -= days_in_month(date->month, date->year);
        date->month++;
        if (date->month > 12) {
            date->month = 1;
            date->year++;
        }
    }
    date->day = total_days;
    return SUCCESS;
}

int compare(const Date* date1, const Date* date2) {
    if (date1->year > date2->year) return 1;
    if (date1->year < date2->year) return -1;

    if (date1->month > date2->month) return 1;
    if (date1->month < date2->month) return -1;

    if (date1->day > date2->day) return 1;
    if (date1->day < date2->day) return -1;

    return 0; // даты равны
}

Status assign(Date* date1, const Date* date2) {
    Status state = SUCCESS;
    if (date2 == nullptr) {
        state = ERROR;
        exit(1);
    }
    else {
        date1->day = date2->day;
        date1->month = date2->month;
        date1->year = date2->year;
    }
    return state;
}

Status output(const Date* date) {
    Status state = SUCCESS;
    if (date == nullptr) {
        state = ERROR;
        exit(1);
    }
    else {
        Date tempDate = *date;
        convert(&tempDate);

        std::cout << tempDate.day << "/"
            << tempDate.month << "/"
            << tempDate.year << std::endl;
    }
    return state;
}

int main() {
    setlocale(LC_ALL, "RU");

    Date date1 = { 11, 12, 2022 }, date2;
    output(&date1);
    assign(&date2, &date1);
    output(&date2);

    if (input(&date1) == ERROR) {
        return 1;
    }

    output(&date1);

    set_values(&date2, 20, 2, 2022);
    output(&date2);

    add_days(&date2, 10);
    output(&date2);

    int comparison = compare(&date1, &date2);

    if (comparison == 0) {
        std::cout << "Date1 равна Date2" << std::endl;
    }
    if (comparison == 1) {
        std::cout << "Date1 позже чем Date2" << std::endl;
    }
    if (comparison == -1) {
        std::cout << "Date1 раньше чем Date2" << std::endl;
    }

    system("pause");
    return 0;
}
