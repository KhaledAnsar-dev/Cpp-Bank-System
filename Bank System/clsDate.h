#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	short _Year;
	short _Mounth;
	short _Day;


public:

	// Constructors

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Mounth = now->tm_mon + 1;
		_Day = now->tm_mday;
	}

	clsDate(string Date)
	{
		vector <string> vcDate;
		vcDate = clsString::Split(Date, "/");
		_Day = stoi(vcDate[0]);
		_Mounth = stoi(vcDate[1]);
		_Year = stoi(vcDate[2]);
	}

	clsDate(int Day, int Mounth, int Year)
	{
		_Day = Day;
		_Mounth = Mounth;
		_Year = Year;
	}

	clsDate(int Number, int Year)
	{
		clsDate Date1;
		Date1 = GetDateFromDayCount(Year, Number);

		_Day = Date1._Day;
		_Mounth = Date1._Mounth;
		_Year = Date1._Year;
	}

	// Property Set and Get

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short _Year;

	// ------------------------------
	void SetMounth(short Mounth)
	{
		_Mounth = Mounth;
	}

	short GetMounth()
	{
		return _Mounth;
	}

	__declspec(property(get = GetMounth, put = SetMounth)) short _Mounth;

	// ------------------------------

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short _Day;


	// Class methods

	void Print()
	{
		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Mounth, Year;

		Year = now->tm_year + 1900;
		Mounth = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Mounth, Year);
	}


	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date._Day < 1 || Date._Day >31)
			return false;
		if (Date._Mounth < 1 || Date._Mounth > 12)
			return false;

		if (Date._Mounth == 2)
		{
			if (IsLeapYear(Date._Year))
			{
				if (Date._Day > 29)
					return false;
			}
			else
			{
				if (Date._Day > 28)
					return false;
			}
		}

		if (Date._Day > DaysInMonth(Date._Year, Date._Mounth))
			return false;


		return true;
	}

	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date._Day) + "/" + to_string(Date._Mounth)
			+ "/" + to_string(Date._Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static bool IsLeapYear(int Year)
	{
		return (Year % 400 == 0 || (Year % 100 != 0 && Year % 4 == 0));
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short DaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short DaysInYear()
	{
		return DaysInYear(_Year);
	}

	static short DaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
			return 0;

		short Array[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : (Array[Month - 1]);
	}

	short DaysInMonth()
	{
		return DaysInMonth(_Year, _Mounth);
	}

	static int HoursInYear(short Year)
	{
		return DaysInYear(Year) * 24;
	}

	int HoursInYear()
	{
		return HoursInYear(_Year);
	}

	static int MinutesInYear(short Year)
	{
		return HoursInYear(Year) * 60;
	}

	int MinutesInYear()
	{
		return MinutesInYear(_Year);
	}

	static int SecondsInYear(short Year)
	{
		return MinutesInYear(Year) * 60;
	}

	int SecondsInYear()
	{
		return SecondsInYear(_Year);
	}

	static short DayOfWeekOrder(short Year, short Mounth, short Day)
	{
		short A = (14 - Mounth) / 12;
		short Y = Year - A;
		short M = Mounth + (12 * A) - 2;

		short D = (Day + Y + (Y / 4) - (Y / 100) + (Y / 400) + ((31 * M) / 12)) % 7;

		return D;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Year, _Mounth, _Day);
	}

	static string FindDayName(short D)
	{
		string Array[] = { "Sun" , "Mon" , "Tue" , "Wed" , "Thu" , "Fri" , "Sat" };

		return Array[D];
	}

	static string FindDayName(short Day, short Mounth, short Year)
	{
		short D = DayOfWeekOrder(Year, Mounth, Day);
		return FindDayName(D);
	}

	string FindDayName()
	{
		return FindDayName(_Day, _Mounth, _Year);
	}

	static string GetMounthName(short Mounth)
	{
		string MounthsName[] =
		{
			"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul" , "Aug", "Sep", "Oct", "Nov", "Dec"
		};

		return MounthsName[Mounth - 1];
	}

	string GetMounthName()
	{
		return GetMounthName(_Mounth);
	}

	static void PrintCalender(short Year, short Mounth)
	{
		short NumberOfDays = DaysInMonth(Year, Mounth), Current = DayOfWeekOrder(Year, Mounth, 1);
		string DaysName[] = { "Sun" , "Mon" , "Tue" , "Wed" , "Thu" , "Fri" , "Sat" };

		printf("  _______________%s_______________\n\n", GetMounthName(Mounth).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < Current; i++)
			printf("     ");

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n\n");

	}

	void PrintCalender()
	{
		PrintCalender(_Year, _Mounth);
	}

	static void PrintYearCalender(short Year)
	{
		printf("  _________________________________\n\n");
		printf("            Calendar - %d          ", Year);
		printf("\n  _________________________________\n\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintCalender(Year, i);
		}
	}

	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}

	static bool CheckLastMounthInYear(short Mounth)
	{
		return (Mounth == 12);
	}

	static bool CheckLastDayInMounth(clsDate DateOne)
	{
		return (DateOne._Day == DaysInMonth(DateOne._Year, DateOne._Mounth));
	}

	static bool YoungestDate(clsDate DateOne, clsDate DateTwo)
	{
		return (DateOne._Year < DateTwo._Year) ? true : ((DateOne._Year == DateTwo._Year) ? ((DateOne._Mounth < DateTwo._Mounth) ? true : ((DateOne._Mounth == DateTwo._Mounth) ? DateOne._Day < DateTwo._Day : false)) : false);
	}

	static bool IsDate1BeforeDate2(clsDate DateOne, clsDate DateTwo)
	{
		return (DateOne._Year < DateTwo._Year) ? true : ((DateOne._Year == DateTwo._Year) ? ((DateOne._Mounth < DateTwo._Mounth) ? true : ((DateOne._Mounth == DateTwo._Mounth) ? DateOne._Day < DateTwo._Day : false)) : false);
	}

	static clsDate IncreaseDateByOneDay(clsDate& DateOne)
	{
		if (CheckLastDayInMounth(DateOne))
		{
			if (CheckLastMounthInYear(DateOne._Mounth))
			{
				DateOne._Year++;
				DateOne._Mounth = 1;
				DateOne._Day = 1;
			}
			else
			{
				DateOne._Mounth++;
				DateOne._Day = 1;
			}
		}
		else
			DateOne._Day++;

		return DateOne;
	}

	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate._Day = Date1._Day;
		TempDate._Mounth = Date1._Mounth;
		TempDate._Year = Date1._Year;

		Date1._Day = Date2._Day;
		Date1._Mounth = Date2._Mounth;
		Date1._Year = Date2._Year;

		Date2._Day = TempDate._Day;
		Date2._Mounth = TempDate._Mounth;
		Date2._Year = TempDate._Year;


	}

	static short GetDifferenceBetweenDay1AndDay2(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short Days = 0, SwapFlagValue = 1;

		if (!YoungestDate(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (YoungestDate(Date1, Date2))
		{
			Days++;
			IncreaseDateByOneDay(Date1);
		}


		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

		/* else
		 {
			 while (BiggestDate(Date1, Date2))
			 {
				 Days++;
				 Date1 = DecreaseDateByOneDay(Date1);
			 }
			 RemainderDays = Days * -1;

			 return IncludeEndDay ? --RemainderDays : RemainderDays;
		 }*/

	}

	short GetDifferenceBetweenDayAndDay2(clsDate Date2)
	{
		return GetDifferenceBetweenDay1AndDay2(*this, Date2);
	}

	static int GetYourAge(clsDate DateOBith)
	{
		int Days = 0;
		clsDate CurrentDay = GetSystemDate();
		while (YoungestDate(DateOBith, CurrentDay))
		{
			Days++;
			IncreaseDateByOneDay(DateOBith);
		}
		return ++Days;
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short Days = 0, SwapFlagValue = 1;

		if (!YoungestDate(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (YoungestDate(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}


		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

		/* else
		 {
			 while (BiggestDate(Date1, Date2))
			 {
				 Days++;
				 Date1 = DecreaseDateByOneDay(Date1);
			 }
			 RemainderDays = Days * -1;

			 return IncludeEndDay ? --RemainderDays : RemainderDays;
		 }*/

	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, short XDays)
	{
		for (short i = 0; i < XDays; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short XDays)
	{
		IncreaseDateByXDays(*this, XDays);
	}

	static clsDate IncreaseDateByXWeek(clsDate& Date, short XWeeks)
	{
		for (short j = 0; j < XWeeks; j++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeek(short XWeeks)
	{
		IncreaseDateByXWeek(*this, XWeeks);
	}

	static clsDate IncreaseDateByOneMounth(clsDate& Date)
	{
		short DaysInMounth = 0;
		if (Date._Mounth == 12)
		{
			Date._Year++;
			Date._Mounth = 1;
		}
		else
			Date._Mounth++;

		DaysInMounth = DaysInMonth(Date._Year, Date._Mounth);

		if (Date._Day > DaysInMounth)
			Date._Day = DaysInMounth;

		return Date;
	}

	void IncreaseDateByOneMounth()
	{
		IncreaseDateByOneMounth(*this);
	}

	static clsDate IncreaseDateByXMounth(clsDate& Date, short XMounth)
	{
		for (short i = 0; i < XMounth; i++)
		{
			Date = IncreaseDateByOneMounth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMounth(short XMounth)
	{
		IncreaseDateByXMounth(*this, XMounth);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date._Year = Date._Year++;

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByTenYear(clsDate& Date, short XYear)
	{
		for (short i = 0; i < XYear; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByTenYear(short XYear)
	{
		IncreaseDateByTenYear(*this, XYear);
	}

	static clsDate IncreaseDateByTenYear_Faster(clsDate Date, short XYear)
	{
		Date._Year += XYear;

		return Date;
	}

	void IncreaseDateByTenYear_Faster(short XYear)
	{
		IncreaseDateByTenYear_Faster(*this, XYear);
	}

	static clsDate DecreaseDateByOneDay(clsDate& DateOne)
	{
		if (DateOne._Day == 1)
		{
			if (DateOne._Mounth == 1)
			{
				DateOne._Year--;
				DateOne._Mounth = 12;
				DateOne._Day = 31;
			}
			else
			{
				DateOne._Mounth -= 1;
				DateOne._Day = DaysInMonth(DateOne._Year, DateOne._Mounth);
			}
		}
		else
			DateOne._Day--;

		return DateOne;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short XDays)
	{
		for (short i = 0; i < XDays; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short XDays)
	{
		DecreaseDateByXDays(*this, XDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(clsDate& Date, short XWeeks)
	{
		for (short j = 0; j < XWeeks; j++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
	}

	void DecreaseDateByXWeek(short XWeeks)
	{
		DecreaseDateByXWeek(*this, XWeeks);
	}

	static clsDate DecreaseDateByOneMounth(clsDate& Date)
	{
		short DaysInMounth = 0;
		if (Date._Mounth == 1)
		{
			Date._Year--;
			Date._Mounth = 12;
		}
		else
			Date._Mounth--;

		DaysInMounth = DaysInMonth(Date._Year, Date._Mounth);

		if (Date._Day > DaysInMounth)
			Date._Day = DaysInMounth;

		return Date;

	}

	void DecreaseDateByOneMounth()
	{
		DecreaseDateByOneMounth(*this);
	}

	static clsDate DecreaseDateByXMounth(clsDate& Date, short XMounth)
	{
		for (short i = 0; i < XMounth; i++)
		{
			Date = DecreaseDateByOneMounth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMounth(short XMounth)
	{
		DecreaseDateByXMounth(*this, XMounth);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date._Year = Date._Year--;

		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static bool IsItEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date._Year, Date._Mounth, Date._Day) == 6);
	}

	bool IsItEndOfWeek()
	{
		return IsItEndOfWeek(*this);
	}

	static bool IsItWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date._Year, Date._Mounth, Date._Day);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsItWeekEnd()
	{
		return IsItWeekEnd(*this);
	}

	static bool IsItBussinesDay(clsDate Date)
	{
		return !IsItWeekEnd(Date);
	}

	bool IsItBussinesDay()
	{
		return IsItBussinesDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._Year, Date._Mounth, Date._Day);
	}

	short DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMounth(clsDate Date)
	{
		clsDate EndMounthDate;
		EndMounthDate._Day = DaysInMonth(Date._Year, Date._Mounth);
		EndMounthDate._Mounth = Date._Mounth;
		EndMounthDate._Year = Date._Year;

		return GetDifferenceBetweenDay1AndDay2(Date, EndMounthDate);
	}

	short DaysUntilTheEndOfMounth()
	{
		return DaysUntilTheEndOfMounth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		clsDate EndYearDate;
		EndYearDate._Day = 31;
		EndYearDate._Mounth = 12;
		EndYearDate._Year = Date._Year;

		return GetDifferenceBetweenDay1AndDay2(Date, EndYearDate);

	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate Date1, clsDate Date2)
	{
		short Count = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			if (IsItBussinesDay(Date1))
				Count++;

			Date1 = IncreaseDateByOneDay(Date1);
		}

		return Count;
	}

	static short CalculateVacationPeriod(clsDate Date1, clsDate Date2)
	{
		return CalculateBusinessDays(Date1, Date2);
	}

	static clsDate GetReturnDate(clsDate Date1, short VacationPeriod)
	{
		while (VacationPeriod != 0)
		{
			if (IsItBussinesDay(Date1))
				VacationPeriod--;

			IncreaseDateByOneDay(Date1);
		}

		while (IsItWeekEnd(Date1))
			IncreaseDateByOneDay(Date1);

		return Date1;
	}

	static bool IsDate1EqualDate2(clsDate DateOne, clsDate DateTwo)
	{
		return (DateOne._Year == DateTwo._Year) ? ((DateOne._Mounth == DateTwo._Mounth) ? ((DateOne._Day == DateTwo._Day) ? true : false) : false) : false;
	}

	bool DateEqualDate2(clsDate DateTwo)
	{
		return IsDate1EqualDate2(*this, DateTwo);
	}

	static bool IsDate1AfterDate2(clsDate DateOne, clsDate DateTwo)
	{
		return (!IsDate1BeforeDate2(DateOne, DateTwo) && !IsDate1EqualDate2(DateOne, DateTwo));
	}

	bool DateIsAfterDate2(clsDate DateTwo)
	{
		return IsDate1AfterDate2(*this, DateTwo);
	}

	enum enDateCompare { After = 1, Equal = 0, Before = -1 };

	static enDateCompare DateCompare(clsDate DateOne, clsDate DateTwo)
	{

		//return (Date1IsBeforeDate2(DateOne, DateTwo)) ? enDateCompare::Before : (Date1EqualDate2(DateOne, DateTwo) ? enDateCompare::Equal : enDateCompare::After );

		if (IsDate1BeforeDate2(DateOne, DateTwo))
			return enDateCompare::Before;

		else if (IsDate1EqualDate2(DateOne, DateTwo))
			return enDateCompare::Equal;

		else
			return enDateCompare::After;
	}

	enDateCompare DateCompare(clsDate DateTwo)
	{
		return DateCompare(*this, DateTwo);
	}

	static clsDate GetDateFromDayCount(short Year, short NumberOfDays)
	{
		clsDate Date;
		Date._Year = Year;
		Date._Mounth = 1;

		short MounthDaysNumber = 0;

		while (true)
		{
			MounthDaysNumber = DaysInMonth(Year, Date._Mounth);

			if (NumberOfDays > MounthDaysNumber)
			{
				NumberOfDays -= MounthDaysNumber;
				Date._Mounth++;
			}
			else
			{
				Date._Day = NumberOfDays;
				break;
			}
		}
		return Date;
	}
};