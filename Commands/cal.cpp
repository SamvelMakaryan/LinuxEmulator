#include "cal.hpp"

std::string cal::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    std::time_t current_time = std::time(nullptr);
    std::tm* local_time = std::localtime(&current_time);
    int current_month = local_time->tm_mon + 1;
    int current_year = local_time->tm_year + 1900;
    std::string months[] = {
        "January",
        "February",
        "March",
        "April", 
        "May", 
        "June",
        "July", 
        "August", 
        "September", 
        "October", 
        "November", 
        "December"
    };
    std::cout << "\033[1;97m" << std::setw(15) << std::right << months[current_month - 1] 
              << std::setw(6) << std::right << current_year << std::endl;
    std::cout << "  Su  Mo  Tu  We  Th  Fr  Sa" << std::endl;
    std::tm first_day_of_month = *local_time;
    first_day_of_month.tm_mday = 1;
    std::mktime(&first_day_of_month);
    int first_day_of_week = first_day_of_month.tm_wday;
    int days_in_month;
    if (current_month == 2) {
        days_in_month = (current_year % 4 == 0 && (current_year % 100 != 0 || current_year % 400 == 0)) ? 29 : 28;
    } else if (current_month == 4 || current_month == 6 || current_month == 9 || current_month == 11) {
        days_in_month = 30;
    } else {
        days_in_month = 31;
    }
    int day = 1;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if ((row == 0 && col < first_day_of_week) || day > days_in_month) {
                std::cout << "    ";
            } else {
                std::cout << std::setw(4) << std::right << day;
                ++day;
            }
        }
        std::cout << std::endl;
        if (day > days_in_month) {
            break;
        }
    }
    std::cout << "\033[0m";
    return "";
}
