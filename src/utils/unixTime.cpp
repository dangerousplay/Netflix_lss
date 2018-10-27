//
// Created by dangerous on 27/10/18.
//

#include "unixTime.h"


boost::gregorian::date to_bdate(time_t time) {
    return boost::posix_time::from_time_t(time).date();
}

time_t to_time_t(const boost::gregorian::date& date ){
    using namespace boost::posix_time;
    static ptime epoch(boost::gregorian::date(1970, 1, 1));
    time_duration::sec_type secs = (ptime(date,seconds(0)) - epoch).total_seconds();
    return time_t(secs);
}

long toMillisecondsEpoch(const boost::gregorian::date &date) {
    return toMilliseconds(to_time_t(date));
}

long toMilliseconds(time_t time) {
    return boost::posix_time::microseconds(time).total_milliseconds();
}
