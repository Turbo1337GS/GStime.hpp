#include <iostream>
#include <cmath>
#include <string>

class GStime {
private:
    int hours;
    int minutes;
    int seconds;

public:
    GStime() : hours(0), minutes(0), seconds(0) {}
    GStime(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    GStime& operator+=(const GStime& other) {
        seconds += other.seconds;
        minutes += other.minutes + seconds / 60;
        hours += other.hours + minutes / 60;
        seconds %= 60;
        minutes %= 60;
        return *this;
    }

    GStime operator+(const GStime& other) const {
        GStime result = *this;
        result += other;
        return result;
    }

    bool operator==(const GStime& other) const {
        return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
    }

    bool operator!=(const GStime& other) const {
        return !(*this == other);
    }

    bool operator<(const GStime& other) const {
        return toSeconds() < other.toSeconds();
    }

    bool operator>(const GStime& other) const {
        return toSeconds() > other.toSeconds();
    }

    bool operator<=(const GStime& other) const {
        return !(*this > other);
    }

    bool operator>=(const GStime& other) const {
        return !(*this < other);
    }

    GStime operator-(const GStime& other) const {
        int diffInSeconds = std::abs(toSeconds() - other.toSeconds());
        return GStime::fromSeconds(diffInSeconds);
    }

    GStime& operator-=(const GStime& other) {
        *this = *this - other;
        return *this;
    }

    GStime operator+(int seconds) const {
        GStime result = *this;
        result.addSeconds(seconds);
        return result;
    }

    GStime operator-(int seconds) const {
        GStime result = *this;
        result.subtractSeconds(seconds);
        return result;
    }

    GStime& operator++() {
        addSeconds(1);
        return *this;
    }

    GStime operator++(int) {
        GStime result = *this;
        ++(*this);
        return result;
    }

    GStime& operator--() {
        subtractSeconds(1);
        return *this;
    }

    GStime operator--(int) {
        GStime result = *this;
        --(*this);
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const GStime& time) {
        os << time.hours << "h " << time.minutes << "m " << time.seconds << "s";
        return os;
    }

    void setTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
    }

    int getHours() const {
        return hours;
    }

    int getMinutes() const {
        return minutes;
    }

    int getSeconds() const {
        return seconds;
    }

    void addSeconds(int s) {
        seconds += s;
        minutes += seconds / 60;
        hours += minutes / 60;
        seconds %= 60;
        minutes %= 60;
    }

    void addMinutes(int m) {
        minutes += m;
        hours += minutes / 60;
        minutes %= 60;
    }

    void addHours(int h) {
        hours += h;
    }

    void subtractSeconds(int s) {
        seconds -= s;
        if (seconds < 0) {
            int minutesToBorrow = (-seconds + 59) / 60;
            seconds += minutesToBorrow * 60;
            minutes -= minutesToBorrow;
            hours -= minutes / 60;
            minutes %= 60;
            if (hours < 0)
                hours = 0;
        }
    }

    void subtractMinutes(int m) {
        minutes -= m;
        if (minutes < 0) {
            int hoursToBorrow = (-minutes + 59) / 60;
            minutes += hoursToBorrow * 60;
            hours -= hoursToBorrow;
            if (hours < 0)
                hours = 0;
        }
    }

    void subtractHours(int h) {
        hours -= h;
        if (hours < 0)
            hours = 0;
    }

    static GStime sumTimes(const GStime* times, int size) {
        GStime result;
        for (int i = 0; i < size; ++i) {
            result += times[i];
        }
        return result;
    }

    static GStime addSecondsToTime(const GStime& time, int s) {
        GStime result = time;
        result.addSeconds(s);
        return result;
    }

    static GStime addMinutesToTime(const GStime& time, int m) {
        GStime result = time;
        result.addMinutes(m);
        return result;
    }

    static GStime addHoursToTime(const GStime& time, int h) {
        GStime result = time;
        result.addHours(h);
        return result;
    }

    static GStime subtractSecondsFromTime(const GStime& time, int s) {
        GStime result = time;
        result.subtractSeconds(s);
        return result;
    }

    static GStime subtractMinutesFromTime(const GStime& time, int m) {
        GStime result = time;
        result.subtractMinutes(m);
        return result;
    }

    static GStime subtractHoursFromTime(const GStime& time, int h) {
        GStime result = time;
        result.subtractHours(h);
        return result;
    }

    int toSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    static GStime fromSeconds(int seconds) {
        int h = seconds / 3600;
        seconds %= 3600;
        int m = seconds / 60;
        seconds %= 60;
        return GStime(h, m, seconds);
    }

    int getTotalMinutes() const {
        return hours * 60 + minutes + (seconds > 0 ? 1 : 0);
    }

    int getTotalHours() const {
        return hours + (minutes > 0 || seconds > 0 ? 1 : 0);
    }

    static int getDifferenceInSeconds(const GStime& time1, const GStime& time2) {
        return std::abs(time1.toSeconds() - time2.toSeconds());
    }

    static int getDifferenceInMinutes(const GStime& time1, const GStime& time2) {
        int diffInSeconds = getDifferenceInSeconds(time1, time2);
        return diffInSeconds / 60 + (diffInSeconds % 60 > 0 ? 1 : 0);
    }

    static int getDifferenceInHours(const GStime& time1, const GStime& time2) {
        int diffInMinutes = getDifferenceInMinutes(time1, time2);
        return diffInMinutes / 60 + (diffInMinutes % 60 > 0 ? 1 : 0);
    }

    static bool isValidTime(int h, int m, int s) {
        return h >= 0 && m >= 0 && s >= 0;
    }

    static bool isValidTime(const GStime& time) {
        return time.hours >= 0 && time.minutes >= 0 && time.seconds >= 0;
    }

    static bool areTimesEqual(const GStime& time1, const GStime& time2) {
        return time1 == time2;
    }

    bool isEmptyTime() const {
        return hours == 0 && minutes == 0 && seconds == 0;
    }

    void setEmptyTime() {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    GStime getTimeDifference(const GStime& other) const {
        int diffInSeconds = std::abs(toSeconds() - other.toSeconds());
        return GStime::fromSeconds(diffInSeconds);
    }

    GStime to12HourFormat() const {
        int h = hours % 12;
        if (h == 0)
            h = 12;
        return GStime(h, minutes, seconds);
    }

    std::string toAMPMFormat() const {
        std::string ampm = hours < 12 ? "AM" : "PM";
        GStime twelveHourFormat = to12HourFormat();
        return twelveHourFormat.toString() + " " + ampm;
    }

    std::string toString() const {
        std::string str = "";
        if (hours < 10)
            str += "0";
        str += std::to_string(hours) + ":";
        if (minutes < 10)
            str += "0";
        str += std::to_string(minutes) + ":";
        if (seconds < 10)
            str += "0";
        str += std::to_string(seconds);
        return str;
    }

    std::string toFullString() const {
        return toString() + " " + toAMPMFormat();
    }
};



GStime operator+(int seconds, const GStime& time) {
    return time + seconds;
}

GStime operator-(int seconds, const GStime& time) {
    return time - seconds;
}

GStime operator*(const GStime& time, int factor) {
    GStime result = time;
    result.addSeconds(time.toSeconds() * (factor - 1));
    return result;
}

GStime operator*(int factor, const GStime& time) {
    return time * factor;
}

GStime operator/(const GStime& time, int divisor) {
    if (divisor == 0) {
        throw std::logic_error("Division by zero");
    }
    int totalSeconds = time.toSeconds();
    int dividedSeconds = totalSeconds / divisor;
    return GStime::fromSeconds(dividedSeconds);
}

GStime operator%(const GStime& time, int divisor) {
    if (divisor == 0) {
        throw std::logic_error("Division by zero");
    }
    int totalSeconds = time.toSeconds();
    int remainderSeconds = totalSeconds % divisor;
    return GStime::fromSeconds(remainderSeconds);
}

bool operator<(const GStime& time, int seconds) {
    return time.toSeconds() < seconds;
}

bool operator>(const GStime& time, int seconds) {
    return time.toSeconds() > seconds;
}

bool operator<=(const GStime& time, int seconds) {
    return !(time > seconds);
}

bool operator>=(const GStime& time, int seconds) {
    return !(time < seconds);
}

bool operator==(const GStime& time, int seconds) {
    return time.toSeconds() == seconds;
}

bool operator!=(const GStime& time, int seconds) {
    return !(time == seconds);
}
/*
int main() {
    GStime time1(1, 30, 45);
    GStime time2(0, 45, 30);
    GStime time3 = time1 + time2;

    std::cout << "Time 1: " << time1 << std::endl;
    std::cout << "Time 2: " << time2 << std::endl;
    std::cout << "Time 3: " << time3 << std::endl;

    if (time1 == time2) {
        std::cout << "Time 1 is equal to Time 2" << std::endl;
    } else {
        std::cout << "Time 1 is not equal to Time 2" << std::endl;
    }

    time3 += GStime(0, 0, 15);
    std::cout << "Time 3 after adding 15 seconds: " << time3 << std::endl;

    time3 += GStime(0, 20, 0); 
    std::cout << "Time 3 after adding 20 minutes: " << time3 << std::endl;

    time3 += GStime(2, 0, 0); 
    std::cout << "Time 3 after adding 2 hours: " << time3 << std::endl;

    GStime time4 = time3 - GStime(0, 40, 0); 
    std::cout << "Time 4 after subtracting 40 minutes from Time 3: " << time4 << std::endl;

    GStime time5 = GStime(0, 0, 10) + time2; 
    std::cout << "Time 5 after adding 10 seconds to Time 2: " << time5 << std::endl;

    GStime timeArray[] = { time1, time2, time3, time4, time5 };
    GStime totalTime = GStime::sumTimes(timeArray, sizeof(timeArray) / sizeof(GStime));
    std::cout << "Total time: " << totalTime << std::endl;

    return 0;
}
*/
