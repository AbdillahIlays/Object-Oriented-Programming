#include <iostream>
using namespace std;

class MyString {
private:
   char* str;
   int length;

   int stringLength(const char* s) const {
       if (s == NULL) return 0;
       int len = 0;
       while (s[len] != '\0') len++;
       return len;
   }

   void stringCopy(char* dest, const char* src) {
       int i = 0;
       while (src[i] != '\0') {
           dest[i] = src[i];
           i++;
       }
       dest[i] = '\0';
   }

public:
   // Default 
   MyString() {
       length = 0;
       str = new char[1];
       str[0] = '\0';
   }

   // Parameterized 
   MyString(const char* input) {
       length = stringLength(input);
       str = new char[length + 1];
       stringCopy(str, input);
   }

   // Copy 
   MyString(const MyString& other) {
       length = other.length;
       str = new char[length + 1];
       stringCopy(str, other.str);
   }

   // Destructor
   ~MyString() {
       delete[] str;
   }

   // Assignment
   MyString& operator=(const MyString& other) {
       if (this == &other) return *this;

       delete[] str;
       length = other.length;
       str = new char[length + 1];
       stringCopy(str, other.str);

       return *this;
   }

   int lengthOfString() const {
       return length;
   }

   void display() const {
       cout << str;
   }

   int countWords() const {
       int count = 0;
       bool inWord = false;

       for (int i = 0; i < length; i++) {
           if (str[i] != ' ') {
               if (!inWord) {
                   count++;
                   inWord = true;
               }
           }
           else {
               inWord = false;
           }
       }
       return count;
   }

   void toUpperCase() {
       for (int i = 0; i < length; i++) {
           if (str[i] >= 'a' && str[i] <= 'z')
               str[i] = str[i] - 'a' + 'A';
       }
   }

   void toLowerCase() {
       for (int i = 0; i < length; i++) {
           if (str[i] >= 'A' && str[i] <= 'Z')
               str[i] = str[i] - 'A' + 'a';
       }
   }

   void toSentenceCase() {
       if (length == 0) return;

       toLowerCase();

       if (str[0] >= 'a' && str[0] <= 'z')
           str[0] = str[0] - 'a' + 'A';
   }

   // Reverse
   MyString reverse() const {
       MyString result;

       result.length = length;
       result.str = new char[length + 1];

       for (int i = 0; i < length; i++) {
           result.str[i] = str[length - 1 - i];
       }

       result.str[length] = '\0';
       return result;
   }

   // Concatenation
   MyString operator+(const MyString& other) const {
       MyString result;

       result.length = length + other.length;
       result.str = new char[result.length + 1];

       int i = 0;

       for (; i < length; i++)
           result.str[i] = str[i];

       for (int j = 0; j < other.length; j++)
           result.str[i++] = other.str[j];

       result.str[i] = '\0';

       return result;
   }

   MyString& operator+=(const MyString& other) {
       *this = *this + other;
       return *this;
   }

   // Comparisons
   bool operator==(const MyString& other) const {
       if (length != other.length) return false;

       for (int i = 0; i < length; i++)
           if (str[i] != other.str[i]) return false;

       return true;
   }

   bool operator!=(const MyString& other) const {
       return !(*this == other);
   }

   bool operator<(const MyString& other) const {
       int i = 0;
       while (i < length && i < other.length) {
           if (str[i] < other.str[i]) return true;
           if (str[i] > other.str[i]) return false;
           i++;
       }
       return length < other.length;
   }

   bool operator>(const MyString& other) const {
       return other < *this;
   }

   bool operator<=(const MyString& other) const {
       return !(*this > other);
   }

   bool operator>=(const MyString& other) const {
       return !(*this < other);
   }

   // Index operator
   char& operator[](int index) {
       if (index < 0 || index >= length) {
           cout << "Index out of range!\n";
           exit(0);
       }
       return str[index];
   }

   // Function call operator (reverse)
   MyString operator()() const {
       return reverse();
   }

   // Output
   friend ostream& operator<<(ostream& out, const MyString& s) {
       out << s.str;
       return out;
   }

   // Input
   friend istream& operator>>(istream& in, MyString& s) {
       char buffer[1000];
       in.getline(buffer, 1000);

       delete[] s.str;
       s.length = s.stringLength(buffer);
       s.str = new char[s.length + 1];
       s.stringCopy(s.str, buffer);

       return in;
   }
};

int main() {
   MyString s1, s2;
   int choice;

   do {
       cout << "\n1. Enter string\n2. Display\n3. Length\n4. Words\n5. Upper\n6. Lower\n7. Sentence\n8. Reverse\n9. Concatenate\n10. Compare\n11. Index\n12. Exit\nChoice: ";
       cin >> choice;
       cin.ignore();

       switch (choice) {
       case 1:
           cout << "Enter string: ";
           cin >> s1;
           break;

       case 2:
           cout << "String: " << s1 << endl;
           break;

       case 3:
           cout << "Length: " << s1.lengthOfString() << endl;
           break;

       case 4:
           cout << "Words: " << s1.countWords() << endl;
           break;

       case 5: {
           MyString t = s1;
           t.toUpperCase();
           cout << t << endl;
           break;
       }

       case 6: {
           MyString t = s1;
           t.toLowerCase();
           cout << t << endl;
           break;
       }

       case 7: {
           MyString t = s1;
           t.toSentenceCase();
           cout << t << endl;
           break;
       }

       case 8:
           cout << s1.reverse() << endl;
           break;

       case 9:
           cout << "Enter second string: ";
           cin >> s2;
           cout << s1 + s2 << endl;
           break;

       case 10:
           cout << "Enter second string: ";
           cin >> s2;
           cout << (s1 == s2 ? "Equal\n" : "Not Equal\n");
           break;

       case 11: {
           int i;
           cout << "Enter index: ";
           cin >> i;
           cout << s1[i] << endl;
           break;
       }

       case 12:
           break;

       default:
           cout << "Invalid\n";
       }

   } while (choice != 12);

   return 0;
}