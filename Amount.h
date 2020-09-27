/*
 * Amount.h
 *  Author: Umer Farooq
 */

#ifndef AMOUNT_H_
#define AMOUNT_H_

#include<string>
#include<map>



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
