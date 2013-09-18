# Keywords to be deleted and keywords to be modified.

/^[0123456789]\{1,\}.\{0,1\} / d
/^[aA] / d
/^[aA]nd / d
/^[aA]t / d
/^[bB]y / d
/^[fF]or / d
/^[iI]s / d
/^[oO]f.\{0,1\} / d
/^[oO]n / d
/^[tT]he / d
/^[tT]o / d

/^[^ ]\{1,\}\. / s/\. / /1
/^[^ ]\{1,\}\.$/ s/\.//1
/^[^ ]\{1,\}, / s/, / /1
/^[^ ]\{1,\},$/ s/,//1
/^[^ ]\{1,\}) / s/) / /1
/^[^ ]\{1,\})$/ s/)//1
/^(/ s/(//1
