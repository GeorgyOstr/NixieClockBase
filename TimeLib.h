struct Time
{
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
    unsigned char date;
    unsigned char weekday;
    unsigned char month;
    unsigned int  year;
};

unsigned char loopFebruaryDays(struct Time time)
{
    if(time.year%4==0)
    {
        return 29;
    }
    else
    {
        return 28;
    }
}

unsigned char daysInMonth(struct Time time)
{
    switch( time.month)
    {
        case 1: return 31;
        case 2: return loopFebruaryDays(time);
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
}

struct Time incrementTime(struct Time time, struct Time increment)
{   
    time.seconds += increment.seconds;
    if (time.seconds>59)
    {
        time.seconds-=60;
        time.minutes+=1;
    }

    time.minutes += increment.minutes;
    if (time.minutes>59)
    {
        time.minutes-=60;
        time.hours+=1;
    }

    time.hours += increment.hours;
    if (time.hours>23)
    {
        time.hours-=24;
        time.weekday+=1;
        time.date+=1;
    }
    
    time.date += increment.date;
    time.weekday += increment.weekday;
    
    if (time.date > daysInMonth(time))
    {
        time.date-=daysInMonth(time);
        time.month+=1;
    }
    if (time.weekday>6)
    {
        time.weekday-=7;
    }

    time.month += increment.month;
    if(time.month>12)
    {
        time.month-=12;
        time.year+=1;
    }
 
    time.year += increment.year;
    if(time.year>9999)
    {
        time.year=0;
    }

    return time;
}
