#include "word.h"

void parseWord(Word *word, QJsonObject d)
{
    if ( d.isEmpty() ) return;

    word->id = d["id"].toInt();
    word->ja = d["ja"].toString();
    word->ru = d["ru"].toString();
    word->pr = d["pr"].toString();
}
