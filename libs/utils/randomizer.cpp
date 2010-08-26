/***************************************************************************
 *   FreeMedicalForms                                                      *
 *   (C) 2008-2010 by Eric MAEKER, MD                                      *
 *   eric.maeker@free.fr                                                   *
 *   All rights reserved.                                                  *
 *                                                                         *
 *   This program is a free and open source software.                      *
 *   It is released under the terms of the new BSD License.                *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *   - Redistributions of source code must retain the above copyright      *
 *   notice, this list of conditions and the following disclaimer.         *
 *   - Redistributions in binary form must reproduce the above copyright   *
 *   notice, this list of conditions and the following disclaimer in the   *
 *   documentation and/or other materials provided with the distribution.  *
 *   - Neither the name of the FreeMedForms' organization nor the names of *
 *   its contributors may be used to endorse or promote products derived   *
 *   from this software without specific prior written permission.         *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 ***************************************************************************/
/***************************************************************************
 *   Main Developper : Eric MAEKER, <eric.maeker@free.fr>                  *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADRESS>                                                *
 ***************************************************************************/
/**
  \class Utils::Randomizer
  Randomizer can be used for populating database with random: names, firstnames, zipcodes and cities, strings, numbers, dates...
*/

#include "randomizer.h"
#include "global.h"
#include "log.h"

#include <time.h>

#include <QFile>
#include <QVector>

#include <time.h>

using namespace Utils;
using namespace std;

#define makeRand(max) (int)((double)rand() / ((double)RAND_MAX + 1) * max)

namespace Utils {
namespace Internal {
class RandomizerPrivate
{
public:
    RandomizerPrivate() {}

    ~RandomizerPrivate()
    {
        boysFirstnames.clear();
        girlsFirstnames.clear();
    }

    void readBoysFirstnames()
    {
        if (!boysFirstnames.isEmpty())
            return;
        QString c = Utils::readTextFile(m_Path + "/boys_firstnames.csv");
        if (c.isEmpty())
            Utils::Log::addError("Randomizer", "Can not read boy firstnames.",
                                 __FILE__, __LINE__);
        foreach(const QString &s, c.split("\n", QString::SkipEmptyParts)) {
            boysFirstnames.append(s);
        }
    }

    void readGirlsFirstnames()
    {
        if (!girlsFirstnames.isEmpty())
            return;
        QString c = Utils::readTextFile(m_Path + "/girls_firstnames.csv");
        if (c.isEmpty())
            Utils::Log::addError("Randomizer", "Can not read boy firtsnames.",
                                 __FILE__, __LINE__);
        foreach(const QString &s, c.split("\n", QString::SkipEmptyParts)) {
            girlsFirstnames.append(s);
        }
    }

    void readZipCodes()
    {
        if (!zipCodes.isEmpty())
            return;
        QString c = Utils::readTextFile(m_Path + "/zipcodes.csv");
        if (c.isEmpty())
            Utils::Log::addError("Randomizer", "Can not read zip codes.",
                                 __FILE__, __LINE__);
        foreach(const QString &s, c.split("\n", QString::SkipEmptyParts)) {
            QStringList z = s.split("\t");
            if (z.count() != 2)
                continue;
            zipCodes.insert(z.at(1).toInt(), z.at(0).toUpper());
        }
    }

    void readFrenchWords()
    {
        if (!words.isEmpty())
            return;
        QString c = Utils::readTextFile(m_Path + "/listemotsfr.txt");
        if (c.isEmpty())
            Utils::Log::addError("Randomizer", "Can not read french words.",
                                 __FILE__, __LINE__);
        foreach(const QString &s, c.split("\n", QString::SkipEmptyParts)) {
            words.append(s.toUpper());
        }
    }


public:
    QVector<QString> boysFirstnames;
    QVector<QString> girlsFirstnames;
    QVector<QString> words;
    QMap<int, QString> zipCodes;
    QString m_Path;
};
}
}


Randomizer::Randomizer() :
        d(0)
{
    d = new Internal::RandomizerPrivate;
    srand(time(NULL));
}

Randomizer::~Randomizer()
{
    if (d) {
        delete d;
        d = 0;
    }
}

void Randomizer::setPathToFiles(const QString &p)
{
    d->m_Path = p;
}

QString Randomizer::getRandomFirstname(bool male)
{
    if (d->boysFirstnames.isEmpty())
        d->readBoysFirstnames();
    if (d->girlsFirstnames.isEmpty())
        d->readGirlsFirstnames();
    if (male)
        return d->boysFirstnames.at(makeRand(d->boysFirstnames.size() - 1));
    return d->girlsFirstnames.at(makeRand(d->girlsFirstnames.size() - 1));
}

QString Randomizer::getRandomString(int length)
{
    static char consonnes[]="BCDFGHJKLMNPQRSTVWXZ";
    static char voyelles[]="AEIOUY";

    QString s;
    int l = length;
    if (length == 0) {
        l = 5;
    }
    for (int i=0; i<l; i++)
    {
        if ((l > 3) && (makeRand(5) == 2))
            s.append(" ");
        else if ((i % 2) == 0)
            s.append(QChar(consonnes[makeRand(20)]));
        else
            s.append(QChar(voyelles[makeRand(6)]));
    }
    return s;
}

QPair<int, QString> Randomizer::getRandomFrenchCity()
{
    if (d->zipCodes.isEmpty())
        d->readZipCodes();
    QPair<int, QString> p;
    int r = makeRand(d->zipCodes.count() - 1);
    p.first = d->zipCodes.keys().at(r);
    p.second = d->zipCodes.value(p.first);
    return p;
}

QString Randomizer::getRandomName()
{
    if (d->words.isEmpty())
        d->readFrenchWords();
    return d->words.at(makeRand(d->words.count() - 1));
}

int Randomizer::randomInt(int max)
{
    return makeRand(max);
}

int Randomizer::randomInt(int min, int max)
{
    Q_ASSERT(min < max);
    int i = min;
    int z = 0;
    while (i < min) {
        i = makeRand(max);
        if (++z == 20) {
            i = max;
            break;
        }
    }
    return i;
}

QDate Randomizer::randomDate(const int minYear, const int minMonth, const int minDay)
{
    int r = -1;
    QDate toReturn(minYear, minMonth, minDay);
    int i = 0;
    int days = toReturn.daysTo(QDate::currentDate());
    if (randomInt(1, 7) > 5) {
        days = days / 2;
    }
    if (days > 1) {
        while (r < 1) {
            r = randomInt(days);
            if (++i == 20)
                break;
        }
    } else {
        return toReturn.addDays(1);
    }
    return toReturn.addDays(r);
}

QDateTime Randomizer::randomDateTime(const QDateTime &minDate)
{
    QDateTime toReturn(randomDate(minDate.date().year(), minDate.date().month(), minDate.date().day()));
    if (toReturn.date() == minDate.date()) {
        int i = 0;
        while (toReturn < minDate) {
            int r = 0;
            int j = 0;
            while (r < 1) {
                r = randomInt(23452634);
                if (++j == 20) {
                    r = i + 1;
                    break;
                }
            }
            toReturn.addMSecs(r);
            if (++i == 20)
                break;
        }
    } else {
        toReturn.setTime(QTime(randomInt(23), randomInt(59), randomInt(59), randomInt(99)));
    }
    return toReturn;
}
