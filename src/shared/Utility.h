//
// Created by Jacopo on 20/09/2019.
//

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace Utility {

	/**
	* @Brief Verifica se una stringa combacia con una seconda stringa, o contiene una sottostringa
	* @PreCondition str e str_or_substr devono essere stringhe C
	* @param str stringa principale
	* @param str_or_substr stringa da confrontare
	* @param check_as_subString true si se vuole controllare se str_or_substr sia strsottostringa di str
	* @return true se il confronto risulata positivo
	*/
	bool CheckEqualsOrSubstring(const char *str, const char *str_or_substr, bool check_as_subString);

}

#endif
