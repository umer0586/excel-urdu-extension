/*
 * Amount.h
 *  Author: Umer Farooq
 */

#ifndef AMOUNT_H_
#define AMOUNT_H_

#include<string>
#include<map>

/*

 int main() {

  Amount amount("23445");


  // or you can also do the following
  // Amount amount;
  // amount.setDigits("23445");



  //To get Unicode Urdu string
  std::wstring amountInUrdu = amount.toUrduUnicode();

  //To get UTF-8 encoded Urdu string
  std::string amountInUrduUTF8 = amount.toUrduUTF8();

  // If console doesn't support UTF-8 you will not be able to see Urdu text
  std::cout << amountInUrduUTF8;

  // To check if code works you can write output to file
  std::ofstream ofs("output.txt");

  ofs << amount.getDigits()  << " = " << amountInUrduUTF8 ;

  ofs.close();

 return 0;

 }

 If you compile and run this code you will get output.txt file containing the text 23445 = تئیس ہزار چار سو پینتالیس

 */


class Amount {

public:
	Amount();
	Amount(const std::string&);
	std::string toUrduUTF8();
	std::wstring toUrduUnicode();
	void setDigits(const std::string&);
	std::string getDigits() const;
	bool validateDigits() const;

private:
	std::string digits;
	std::string urduTemplate[13];
	std::map<std::string, std::string> digitsToUrduMapping;
	static const unsigned int MAX_DIGITS = 13; // Maximum number of digits in 10 Kharab


	void buidDigitsToUrduMappings();
	std::string urduOf(const std::string&);
	void buildUrduTemplate();
	std::wstring string_to_wstring(const std::string&);

};

#endif /* AMOUNT_H_ */
