//
// Created by dangerous on 27/10/18.
//

#ifndef NETFLIX_LSS_UNIXTIME_H
#define NETFLIX_LSS_UNIXTIME_H

#include <ctime>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>



//==============================================================================
//! Convert date part of Unix timestamp (time_t) to boost date
//!
//! time_t contains the number of seconds since 00:00 hours, Jan 1, 1970 UTC
//!
//! \param time unix timestamp to convert
//! \return boost date of the timestamp's date
//
boost::gregorian::date to_bdate(time_t time);



//==============================================================================
//! Convert boost::gregorian::date to Unix timestamp (time_t)
//!
//! Converts a boost date to a Unix timestamp pointing to 00:00 hours, 0 seconds
//! of the day given by date.
//!
//! time_t contains the number of seconds since 00:00 hours, Jan 1, 1970 UTC.
//!
//! \param date to convert
//! \return unix timestamp
time_t to_time_t(const boost::gregorian::date& date );

long toMilliseconds(time_t time);

long toMillisecondsEpoch(const boost::gregorian::date& date);

#endif //NETFLIX_LSS_UNIXTIME_H
