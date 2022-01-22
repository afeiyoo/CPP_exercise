#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>
using namespace std;

struct Sales_data {
  Sales_data() = default; // 默认构造函数，执行默认初始化
  Sales_data(const string& s): bookNo(s){}
  Sales_data(const string& s, unsigned n, double p):bookNo(s), units_sold(n), revenue(p*n){}
  Sales_data(istream& is){ //不能再直接用read()了，因为在这里read()还是不可见的
    double price = 0;
    is >> this->bookNo >> this->units_sold >> price;
    this->revenue = this->units_sold * price;
  }

  string bookNo;
  string bookName;
  unsigned int units_sold = 0;
  double revenue = 0.0;  // 总收入

  Sales_data &combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
  }

  string isbn() const { return bookNo; }

  double avg_price() const;
};

double Sales_data::avg_price() const {
  return units_sold ? revenue / units_sold : 0;
}

Sales_data add(const Sales_data &data1, const Sales_data &data2) {
  Sales_data sum = data1;
  return sum.combine(data2);
}

istream &read(istream &is, Sales_data &data) {
  double price = 0;
  is >> data.bookNo >> data.units_sold >> price;
  data.revenue = data.units_sold * price;
  return is;
}

ostream &print(ostream &os, const Sales_data &data) {
  os << data.isbn() << " " << data.units_sold << " " << data.revenue << " "
     << data.avg_price();
  return os;
}

#endif