#include "../excel-urdu-extension/Amount.h"

#include <regex>
#include <iterator>
#include <windows.h>


Amount::Amount()
{
	buidDigitsToUrduMappings();
	buildUrduTemplate();
}

// Invoking Constructor "Amount()" from this constructor
Amount::Amount(const std::string& digits) : Amount()
{
	setDigits(digits);
}

void Amount::setDigits(const std::string& digits)
{
	this->digits = digits;
}

std::string Amount::getDigits() const
{
	return this->digits;
}

/*@return Urdu text (UTF-8 encoded) representing amount in Urdu language.
 * Empty string is returned if the amount figure provided by the caller is invalid or exceeds 99 kharab (i-e more than 13 digits)
 */
std::string Amount::toUrduUTF8()
{

	//If this->digits is invalid return empty string
	if(!validateDigits())
		return "";


		/*
		 *  Since we need to modify digits to reach result,
		    Therefore we will work on copy of "this->digits" so that original digits provided by caller don't get modified
		    getDigits() must return the digits provided by the caller as it is.
		*/
		std::string _digits = getDigits();


		//If digits are valid but has n number of prefix of zeros, then just get the 13 digits part
		if(_digits.length() > MAX_DIGITS)
			_digits = _digits.substr(_digits.length()-MAX_DIGITS, _digits.length());

		// if digits count is less than 13 (MAX_DIGITS) prefix required No of Zeros
		else
		{

			//Completing given digits to 13 digits by prefixing required number of zeros
			//(required zeros = MAX_DIGITS - digits.length())
			std::string zeros;
			zeros.clear();
			zeros.append(MAX_DIGITS - _digits.length(),'0');
			_digits = zeros + _digits;

			/*
			 * We have only Urdu of two digits from 01 to 99
			 * 1. Prefixing zeros helps us by avoiding occurrence of single digit while filling up empty strings in urduTemplate[] array
			 * 2. Prefixing zeros are a part of algorithm since we need to fill all empty string of urduTemplate[] from given digits
             */
		}


		/*
		 * 1. Filling up the empty strings of urduTemplate[] array
		 * 2. Since all the empty string of urduTemplate[] array are at even indexes, so we need to loop through even indexes only
		*/
		for(int i = 0; i<=12; i+=2)
		{
				std::string temp;
				//Avoid '+' operator for creating string from characters
				if(i == 2)
				{
					temp.clear();
					temp.push_back('0') ;temp.push_back(_digits.at(10));

					this->urduTemplate[i] = temp;
				}
				else if(i == 0)
				{
					temp.clear();
					temp.push_back(_digits.at(11)); temp.push_back(_digits.at(12));

					this->urduTemplate[i] = temp;
				}
				else
				{
					temp.clear();
					temp.push_back(_digits.at(12-i)); temp.push_back(_digits.at(13-i));

					this->urduTemplate[i] =  temp;
				}
		}


		//Stores UTF-8 string containing amount in urdu
		std::string urdu;

		// Looping through urduTemplate[] array to create final urdu text
		for(int i = 12; i >=0 ; i-=2)
		{

			if(!(this->urduTemplate[i] == "00"))
			{
				if(i != 0)
					/* As per algorithm this should be urdu += urduTemplate[i-1] + urduOf(urduTemplate[i]);
					   But since Urdu is written from right to left '+' operator concatenates Urdu text in reverse order
					   therefore we have to write statement in reverse order i-e urduOf(urduTemplate[i]) + urduTemplate[i-1];
					*/
					urdu += urduOf(this->urduTemplate[i]) + this->urduTemplate[i-1];
				else
					urdu += urduOf(this->urduTemplate[i]);

			}
		}

		//If urdu text is empty it means _digits contains only zeros [0]+ (i-e 0 to 0000.....n zeros)
		if(urdu == "")
			return "صفر";

		return urdu;
}

/* @Return Urdu text (Unicode) representing amount in Urdu language
 * Empty string is returned if the amount figure provided by the caller is invalid or exceeds 99 kharab (i-e more than 13 digits)
 */
std::wstring Amount::toUrduUnicode()
{

	return string_to_wstring(this->toUrduUTF8());

}

bool Amount::validateDigits() const
{

	 //only accept (any no of zeros)(0 to 9999999999999) i-e (n zeros)(13 digits)
	 std::regex digitsRegex("[0]*([0-9]{1,13})");

	 return std::regex_match(this->digits,digitsRegex);

}

/*
 *	@param twoDigits
 *	string of 2 digits from 01 to 99
 *
 *	@return	string representing Urdu text of corresponding two digits value.
 *	For @param 'twoDigits' value other than 01 to 99, @param 'twoDigits' is returned back to the caller
 *
 *  This private Method is called by toUrdu() method several time.
 *  toUrdu() method never passes value other than 01 to 99 to this method
 */
std::string Amount::urduOf(const std::string& twoDigits)
{


	std::map<std::string, std::string>::iterator it = this->digitsToUrduMapping.find(twoDigits);

	if( it != this->digitsToUrduMapping.end() ) // if key found then return the corresponding value
		return it->second;
	else
		return twoDigits; // if no value is found then return back @param twoDigits
}



//Converts std::string (UTF-8) to std::wstring (Unicode)
//Found @ https://gist.github.com/pezy/8571764
std::wstring Amount::string_to_wstring(const std::string &str)
{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;

}


/*
 * Creates mappings of two digits from 01 to 99 to corresponding Urdu text
 *
 */

void Amount::buildUrduTemplate()
{

	//Urdu is written from right to left therefore single line array initialization wont work perfectly
	this->urduTemplate[0] = "";
	this->urduTemplate[1] = " سو ";
	this->urduTemplate[2] = "";
	this->urduTemplate[3] = " ہزار ";
	this->urduTemplate[4] = "";
	this->urduTemplate[5] = " لاکھ ";
	this->urduTemplate[6] = "";
	this->urduTemplate[7] = " کروڑ ";
	this->urduTemplate[8] = "";
	this->urduTemplate[9] = " ارب ";
	this->urduTemplate[10] = "";
	this->urduTemplate[11] = " کھرب ";
	this->urduTemplate[12] = "";
}

void Amount::buidDigitsToUrduMappings()
{


	this->digitsToUrduMapping.insert(std::make_pair("01","ایک"));
	this->digitsToUrduMapping.insert(std::make_pair("02","دو"));
	this->digitsToUrduMapping.insert(std::make_pair("03","تین"));
	this->digitsToUrduMapping.insert(std::make_pair("04","چار"));
	this->digitsToUrduMapping.insert(std::make_pair("05","پانچ"));
	this->digitsToUrduMapping.insert(std::make_pair("06","چھ"));
	this->digitsToUrduMapping.insert(std::make_pair("07","سات"));
	this->digitsToUrduMapping.insert(std::make_pair("08","آٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("09","نو"));
	this->digitsToUrduMapping.insert(std::make_pair("10","دس"));
	this->digitsToUrduMapping.insert(std::make_pair("11","گیارہ"));
	this->digitsToUrduMapping.insert(std::make_pair("12","بارہ"));
	this->digitsToUrduMapping.insert(std::make_pair("13","تیرہ"));
	this->digitsToUrduMapping.insert(std::make_pair("14","چودہ"));
	this->digitsToUrduMapping.insert(std::make_pair("15","پندرہ"));
	this->digitsToUrduMapping.insert(std::make_pair("16","سولہ"));
	this->digitsToUrduMapping.insert(std::make_pair("17","سترہ"));
	this->digitsToUrduMapping.insert(std::make_pair("18","اٹھارہ"));
	this->digitsToUrduMapping.insert(std::make_pair("19","انیس"));
	this->digitsToUrduMapping.insert(std::make_pair("20","بیس"));
	this->digitsToUrduMapping.insert(std::make_pair("21","اکیس"));
	this->digitsToUrduMapping.insert(std::make_pair("22","بائیس"));
	this->digitsToUrduMapping.insert(std::make_pair("23","تئیس"));
	this->digitsToUrduMapping.insert(std::make_pair("24","چوبیس"));
	this->digitsToUrduMapping.insert(std::make_pair("25","پچیس"));
	this->digitsToUrduMapping.insert(std::make_pair("26","چھببیس"));
	this->digitsToUrduMapping.insert(std::make_pair("27","ستائیس"));
	this->digitsToUrduMapping.insert(std::make_pair("28","اٹھائیس"));
	this->digitsToUrduMapping.insert(std::make_pair("29","انتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("30","تیس"));
	this->digitsToUrduMapping.insert(std::make_pair("31","اکتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("32","بتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("33","تینتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("34","چونتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("35","پینتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("36","چھتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("37","سینتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("38","اڑتیس"));
	this->digitsToUrduMapping.insert(std::make_pair("39","انتالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("40","چالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("41","اکتالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("42","بیالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("43","تینتالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("44","چوالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("45","پینتالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("46","چھیالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("47","سینتالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("48","اڑتالیس"));
	this->digitsToUrduMapping.insert(std::make_pair("49","انچاس"));
	this->digitsToUrduMapping.insert(std::make_pair("50","پچاس"));
	this->digitsToUrduMapping.insert(std::make_pair("51","اکیاون"));
	this->digitsToUrduMapping.insert(std::make_pair("52","باون"));
	this->digitsToUrduMapping.insert(std::make_pair("53","ترپن"));
	this->digitsToUrduMapping.insert(std::make_pair("54","چون"));
	this->digitsToUrduMapping.insert(std::make_pair("55","پچپن"));
	this->digitsToUrduMapping.insert(std::make_pair("56","چھپن"));
	this->digitsToUrduMapping.insert(std::make_pair("57","ستاون"));
	this->digitsToUrduMapping.insert(std::make_pair("58","اٹھاون"));
	this->digitsToUrduMapping.insert(std::make_pair("59","انسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("60","ساٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("61","اکسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("62","باسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("63","ترسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("64","چوسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("65","پینسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("66","چھیاسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("67","سڑسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("68","اٹھسٹھ"));
	this->digitsToUrduMapping.insert(std::make_pair("69","انہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("70","ستر"));
	this->digitsToUrduMapping.insert(std::make_pair("71","اکہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("72","بہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("73","تہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("74","چوہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("75","پچہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("76","چھہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("77","ستتر"));
	this->digitsToUrduMapping.insert(std::make_pair("78","اٹھہتر"));
	this->digitsToUrduMapping.insert(std::make_pair("79","اناسی"));
	this->digitsToUrduMapping.insert(std::make_pair("80","اسی"));
	this->digitsToUrduMapping.insert(std::make_pair("81","اکیاسی"));
	this->digitsToUrduMapping.insert(std::make_pair("82","بیاسی"));
	this->digitsToUrduMapping.insert(std::make_pair("83","تراسی"));
	this->digitsToUrduMapping.insert(std::make_pair("84","چوراسی"));
	this->digitsToUrduMapping.insert(std::make_pair("85","پچاسی"));
	this->digitsToUrduMapping.insert(std::make_pair("86","چھیاسی"));
	this->digitsToUrduMapping.insert(std::make_pair("87","ستاسی"));
	this->digitsToUrduMapping.insert(std::make_pair("88","اٹھاسی"));
	this->digitsToUrduMapping.insert(std::make_pair("89","نواسی"));
	this->digitsToUrduMapping.insert(std::make_pair("90","نوے"));
	this->digitsToUrduMapping.insert(std::make_pair("91","اکانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("92","بانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("93","ترانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("94","چورانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("95","پچانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("96","چھیانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("97","ستانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("98","اٹھانوے"));
	this->digitsToUrduMapping.insert(std::make_pair("99","ننانوے"));



}




