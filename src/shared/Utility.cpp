#include "Utility.h"
#include <string>

namespace Utility {
	bool CheckEqualsOrSubstring(const char *str, const char *str_or_substr, bool check_as_subString) {
		bool isMatching = false;
		std::string o_str = std::string(str);
		if (str != NULL) {
			if (!check_as_subString) {
				isMatching = !o_str.compare(str_or_substr);
			}
			else {
				isMatching = o_str.rfind(str_or_substr) != o_str.npos;
			}
		}
		o_str.clear();
		return isMatching;
	}

	std::list<Point2D>::iterator random_element(std::list<Point2D>::iterator begin, std::list<Point2D>::iterator end) {

		unsigned long n = std::distance(begin, end);
		unsigned long divisor = (RAND_MAX + 1) / n;

		unsigned long k;
		do {
			k = std::rand() / divisor;
		} while (k >= n);

		std::advance(begin, k);
		return begin;
	}
}