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
#ifndef CORE_CONSTANTS_TOKENS_SETTINGS_H
#define CORE_CONSTANTS_TOKENS_SETTINGS_H

/**
 * \file constants_tokensandsettings.h
 * \author Eric MAEKER <eric.maeker@free.fr>
 * \version 0.4.0
 * \date 13 June 2010
*/


namespace Core {

namespace Constants {

// TEXT COMPLETION tokens

// For Documents
const char * const  TOKEN_DOCUMENTTITLE     = "DOCUMENTTITLE";


// For Patients
const char * const  TOKEN_PATIENTAGE        = "PATIENTAGE";
const char * const  TOKEN_PATIENTYEARSOLD   = "PATIENTYEARSOLD";
const char * const  TOKEN_PATIENTFULLNAME   = "PATIENTFULLNAME";
const char * const  TOKEN_PATIENTNAME       = "PATIENTNAME";
const char * const  TOKEN_PATIENTSECONDNAME = "PATIENTSECONDNAME";
const char * const  TOKEN_PATIENTFIRSTNAME  = "PATIENTFIRSTNAME";
const char * const  TOKEN_PATIENTTITLE      = "PATIENTTITLE";
const char * const  TOKEN_PATIENTDATEOFBIRTH= "PATIENTDATEOFBIRTH";
const char * const  TOKEN_WEIGHT            = "WEIGHT";
const char * const  TOKEN_WEIGHT_UNIT       = "WEIGHT_UNIT";
const char * const  TOKEN_HEIGHT            = "HEIGHT";
const char * const  TOKEN_HEIGHT_UNIT       = "HEIGHT_UNIT";
const char * const  TOKEN_CLCR              = "CLCR";
const char * const  TOKEN_CLCR_UNIT         = "CLCR_UNIT";
const char * const  TOKEN_DATE              = "DATE";
const char * const  TOKEN_NUMBEROFDRUGS     = "NBDRUGS";

// For Users
const char * const  TOKEN_USERAGE            = "USERAGE";
const char * const  TOKEN_USERYEARSOLD       = "USERYEARSOLD";
const char * const  TOKEN_USERFULLNAME       = "USERFULLNAME";
const char * const  TOKEN_USERTITLE          = "USERTITLE";
const char * const  TOKEN_USERNAME           = "USERNAME";
const char * const  TOKEN_USERSECONDNAME     = "USERSECONDNAME";
const char * const  TOKEN_USERFIRSTNAME      = "USERFIRSTNAME";
const char * const  TOKEN_USERSPECIALITIES   = "USERSPECIALITIES";
const char * const  TOKEN_USERIDENTIFIANTS   = "USERIDENTIFIANTS";
const char * const  TOKEN_USERQUALIFICATIONS = "USERQUALIFICATIONS";
const char * const  TOKEN_USERFULLADRESS     = "USERFULLADRESS";
const char * const  TOKEN_USERFULLCONTACT    = "USERFULLCONTACT";


// Some path tags
const char * const  TAG_APPLICATION_RESOURCES_PATH = "%appResources%";
const char * const  TAG_APPLICATION_THEME_PATH     = "%theme%";

// Settings keys
const char * const  S_RECENTFILES_GROUP = "RecentFiles";
const char * const  S_RECENTFILES_KEY   = "File";
const char * const  S_PATIENT_UUID_HISTORY = "PatientsUuids";
const char * const  S_SAVEINTERVAL      = "Core/SaveInterval";
const char * const  S_OPENLAST          = "Core/OpenLastOpenedFile";
const char * const  S_SHOWHELPTEXT      = "Core/ShowFormHelpText";
const char * const  S_LASTLOGIN         = "Login/userLogin";
const char * const  S_LASTPASSWORD      = "Login/userPassword";
const char * const  S_DATEFORMAT        = "Dates/Format";

const char * const  S_PATIENTFORMS_FILENAME  = "Core/PatientFormsFile";

const char * const  S_USE_EXTERNAL_DATABASE  = "ExternalDatabase/UseIt";
const char * const  S_EXTERNAL_DATABASE_LOG  = "ExternalDatabase/Log";
const char * const  S_EXTERNAL_DATABASE_PASS = "ExternalDatabase/Pass";
const char * const  S_EXTERNAL_DATABASE_HOST = "ExternalDatabase/Host";
const char * const  S_EXTERNAL_DATABASE_PORT = "ExternalDatabase/Port";

const char * const  S_ALWAYS_SAVE_WITHOUT_PROMPTING = "Core/SaveInDatabaseWithoutPrompringUser";

}  // end Constants
} // end Core

#endif // CORE_CONSTANTS_TOKENS_SETTINGS_H
