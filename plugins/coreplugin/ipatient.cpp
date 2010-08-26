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
 *       NAME <MAIL@ADRESS>                                                *
 ***************************************************************************/
/**
  \class Core::IPatient
  Abstract interface provided to access Patient's datas.
  \sa Core::setPatient(), Core::patient()
*/

#include "ipatient.h"
#include "constants_tokensandsettings.h"

#include <utils/global.h>

using namespace Core;

void IPatient::replaceTokens(QString &stringWillBeModified)
{
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTNAME,       data(IPatient::BirthName).toString());
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTFIRSTNAME,  data(IPatient::Firstname).toString());
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTSECONDNAME, data(IPatient::SecondName).toString());
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTFULLNAME,   data(IPatient::FullName).toString());
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTYEARSOLD,   data(IPatient::YearsOld).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTAGE,        data(IPatient::Age).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_WEIGHT,            data(IPatient::Weight).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_WEIGHT_UNIT,       data(IPatient::WeightUnit).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_HEIGHT,            data(IPatient::Height).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_HEIGHT_UNIT,       data(IPatient::HeightUnit).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTDATEOFBIRTH,data(IPatient::DateOfBirth).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_CLCR,              data(IPatient::CreatinClearance).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_CLCR_UNIT,         data(IPatient::CreatinClearanceUnit).toString() );
    Utils::replaceToken(stringWillBeModified, Constants::TOKEN_PATIENTTITLE,      data(IPatient::Title).toString() );
}

