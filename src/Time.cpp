#include "Time.h"

using namespace std;

char Time::text[13] = "XX:XX:XX.XXX";

Time::Time(){
    hour = minute = second = millisecond = 0;
}

Time::Time(int hour, int minute, int second, int millisecond) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    this->millisecond = millisecond;
}

int Time::getHour() {
    return hour;
}

int Time::getMinute() {
    return minute;
}

int Time::getSecond() {
    return second;
}

int Time::getMillisecond() {
    return millisecond;
}

char* Time::toString() {
    sprintf(Time::text, "%02d:%02d:%02d.%03d", hour, minute, second, millisecond);
    return text;
}

bool Time::isEqual(Time other) {
    return hour == other.getHour() && minute == other.getMinute() &&
           second == other.getSecond() && millisecond == other.getMillisecond();
}

bool Time::isEqual(Time* other) {
    return isEqual(*other);
}

bool Time::isBefore(Time other) {
    if (hour < other.getHour()) return true;
    if (minute < other.getMinute()) return true;
    if (second < other.getSecond()) return true;
    if (millisecond < other.getMillisecond()) return true;
    return false;
}

bool Time::isBefore(Time* other) {
    return isBefore(*other);
}
