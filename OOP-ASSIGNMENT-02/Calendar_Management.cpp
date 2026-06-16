#include <iostream>
using namespace std;

class CalendarDate {
private:
   int day, month, year;

   int getDaysInMonth(int m, int y) const {
       if (m < 1 || m > 12) return 0;

       int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

       if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)))
           return 29;

       return days[m - 1];
   }

   bool isValidDate(int d, int m, int y) const {
       if (y < 1 || m < 1 || m > 12 || d < 1) return false;
       return d <= getDaysInMonth(m, y);
   }

   void resetToDefault() {
       day = 1; month = 1; year = 2000;
   }

public:
  
   CalendarDate() {
       resetToDefault();
   }

   CalendarDate(int d, int m, int y) {
       if (isValidDate(d, m, y)) {
           day = d; month = m; year = y;
       }
       else {
           cout << "Invalid Date! Reset to: 01-01-2000\n";
           resetToDefault();
       }
   }

   CalendarDate(int totalDays) {
       resetToDefault();
       addDays(totalDays);
   }

   CalendarDate(const CalendarDate& other) {
       day = other.day;
       month = other.month;
       year = other.year;
   }
   int getYear() const { return year; }

   bool isLeapYear() const {
       return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
   }

   int toTotalDays() const {
       int total = 0;

       for (int y = 2000; y < year; y++) {
           total += ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 366 : 365;
       }

       for (int m = 1; m < month; m++) {
           total += getDaysInMonth(m, year);
       }

       total += (day - 1);
       return total;
   }


   void addDays(int n) {
       for (int i = 0; i < n; i++) {
           day++;
           if (day > getDaysInMonth(month, year)) {
               day = 1;
               month++;
               if (month > 12) {
                   month = 1;
                   year++;
               }
           }
       }
   }

   void subtractDays(int n) {
       for (int i = 0; i < n; i++) {
           day--;
           if (day < 1) {
               month--;
               if (month < 1) {
                   month = 12;
                   year--;
               }
               day = getDaysInMonth(month, year);
           }
       }
   }

   void print(int fmt) const {
       const char* months[] = { "January","February","March","April","May","June",
                              "July","August","September","October","November","December" };

       if (fmt == 1) {
           cout << (day < 10 ? "0" : "") << day << "-"
               << (month < 10 ? "0" : "") << month << "-"
               << year;
       }
       else if (fmt == 2) {
           cout << months[month - 1] << " " << day << ", " << year;
       }
       else if (fmt == 3) {
           cout << year << "/"
               << (month < 10 ? "0" : "") << month << "/"
               << (day < 10 ? "0" : "") << day;
       }
   }

   CalendarDate operator+(int d) const {
       CalendarDate temp = *this;
       temp.addDays(d);
       return temp;
   }

   CalendarDate operator-(int d) const {
       CalendarDate temp = *this;
       temp.subtractDays(d);
       return temp;
   }

   int operator-(const CalendarDate& other) const {
       return toTotalDays() - other.toTotalDays();
   }

   friend CalendarDate operator+(int d, const CalendarDate& obj) {
       return obj + d;
   }

   CalendarDate& operator+=(int d) {
       addDays(d);
       return *this;
   }

   CalendarDate& operator-=(int d) {
       subtractDays(d);
       return *this;
   }

   CalendarDate& operator++() {
       addDays(1);
       return *this;
   }

   CalendarDate operator++(int) {
       CalendarDate temp = *this;
       addDays(1);
       return temp;
   }

   CalendarDate& operator--() {
       subtractDays(1);
       return *this;
   }

   CalendarDate operator--(int) {
       CalendarDate temp = *this;
       subtractDays(1);
       return temp;
   }


   bool operator==(const CalendarDate& o) const {
       return day == o.day && month == o.month && year == o.year;
   }

   bool operator!=(const CalendarDate& o) const {
       return !(*this == o);
   }

   bool operator<(const CalendarDate& o) const {
       return toTotalDays() < o.toTotalDays();
   }

   bool operator>(const CalendarDate& o) const {
       return toTotalDays() > o.toTotalDays();
   }

   bool operator<=(const CalendarDate& o) const {
       return !(*this > o);
   }

   bool operator>=(const CalendarDate& o) const {
       return !(*this < o);
   }


   void operator()() const {
       print(1); cout << endl;
       print(2); cout << endl;
       print(3); cout << endl;
   }
   friend ostream& operator<<(ostream& out, const CalendarDate& d) {
       out << (d.day < 10 ? "0" : "") << d.day << "-"
           << (d.month < 10 ? "0" : "") << d.month << "-"
           << d.year;
       return out;
   }

   friend istream& operator>>(istream& in, CalendarDate& d) {
       int dd, mm, yy;
       in >> dd >> mm >> yy;

       if (d.isValidDate(dd, mm, yy)) {
           d.day = dd;
           d.month = mm;
           d.year = yy;
       }
       else {
           cout << "Invalid Date! Reset to: 01-01-2000\n";
           d.resetToDefault();
       }
       return in;
   }
};

int main() {
   CalendarDate d1, d2;
   int choice, days;

   do {
       cout << "1. Enter Date\n2. Display\n3. Add Days\n4. Subtract Days\n";
       cout << "5. Compare\n6. Difference\n7. ++ Test\n8. -- Test\n";
       cout << "9. += / -=\n10. Leap Year\n11. All Formats\n12. Exit\n";
       cout << "Choice: ";
       cin >> choice;

       switch (choice) {
       case 1:
           cin >> d1;
           break;

       case 2:
           cout << d1 << endl;
           break;

       case 3:
           cin >> days;
           cout << d1 + days << endl;
           break;

       case 4:
           cin >> days;
           cout << d1 - days << endl;
           break;

       case 5:
           cin >> d1 >> d2;
           cout << (d1 == d2) << endl;
           break;

       case 6:
           cin >> d1 >> d2;
           cout << abs(d1 - d2) << " days\n";
           break;

       case 7:
           cin >> d1;
           cout << ++d1 << endl;
           break;

       case 8:
           cin >> d1;
           cout << --d1 << endl;
           break;

       case 9:
           cin >> d1 >> days;
           d1 += days;
           cout << d1 << endl;
           break;

       case 10:
           cin >> d1;
           cout << (d1.isLeapYear() ? "Leap Year\n" : "Not Leap\n");
           break;

       case 11:
           cin >> d1;
           d1();
           break;

       }
   } while (choice != 12);

   return 0;
}