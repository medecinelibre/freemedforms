/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2013 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *  Main Developer: Eric MAEKER, MD <eric.maeker@gmail.com>                *
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#include "druginteractor.h"

#include <utils/log.h>
#include <utils/global.h>

#include <QDomElement>
#include <QString>

#include <QDebug>

using namespace DDI;

namespace {
const char * const XML_ROOT_TAG = "Interactors";
const char * const XML_INTERACTOR_TAG = "I";
const char * const XML_CLASSINFORMATION_TAG = "CI";
const char * const XML_LABEL_TAG = "L";
const char * const XML_ATC_TAG = "ATC";
const char * const XML_CHILD_TAG = "M";
const char * const XML_OTHER_TAG = "O";

const char * const XML_ID_ATTRIB = "id";
const char * const XML_VALID_ATTRIB = "v";
const char * const XML_ISCLASS_ATTRIB = "c";
const char * const XML_REFERENCE_ATTRIB = "r";
const char * const XML_PMIDS_ATTRIB = "p";
const char * const XML_DATECREATE_ATTRIB = "dc";
const char * const XML_DATEUPDATE_ATTRIB = "lu";
const char * const XML_WARNDUPLICATES_ATTRIB = "nwd";
const char * const XML_LANG_ATTRIB = "l";
const char * const XML_NAME_ATTRIB = "n";
const char * const XML_TRANSLATION_ATTRIB = "t";
const char * const XML_ATCCODE_ATTRIB = "a";
const char * const XML_COMMENT_ATTRIB = "c";
const char * const XML_ISREVIEW_ATTRIB = "r";
const char * const XML_REVIEWERS_ATTRIB = "rv";
const char * const XML_DATEREVIEW_ATTRIB = "d";
const char * const XML_ISAUTOFOUND_ATTRIB = "af";
}

/** Create an empty invalid DDI::DrugInteractor */
DrugInteractor::DrugInteractor()
{
    setData(IsValid, false);
    setData(IsClass, false);
    setData(IsReviewed, false);
    setData(IsValid, false);
    setData(IsDuplicated, false);
}

DrugInteractor::~DrugInteractor()
{}

/**
 * Returns the internal data of this interactor.
 * Use the DDI::DrugInteractor::DataRepresentation for \e reference.
 */
QVariant DrugInteractor::data(const int reference) const
{
    if (reference == ReadOnly_TranslatedLabel) {
        QString loc = QLocale().name().left(2).toLower();
        if (loc=="en")
            return _data.value(EnLabel);
        else if (loc=="fr")
            return _data.value(FrLabel);
        else if (loc=="de")
            return _data.value(DeLabel);
        else if (loc=="es")
            return _data.value(EsLabel);
    } else if (reference==ATCCodeStringList) {
        if (!m_AtcLinks.isEmpty())
            return m_AtcLinks;
    }
    return _data.value(reference);
}

/**
 * Define the internal data of this interactor.
 * Use the DDI::DrugInteractor::DataRepresentation for \e reference.
 */
bool DrugInteractor::setData(const int reference, const QVariant &value)
{
    if (reference == ReadOnly_TranslatedLabel)
        return false;

    if (reference==ATCCodeStringList) {
        m_AtcLinks = value.toStringList();
        return true;
    }
    _data.insert(reference, value);
    return true;
}

QString DrugInteractor::label() const {return data(ReadOnly_TranslatedLabel).toString();}
QString DrugInteractor::id() const {return data(Id).toString();}
bool DrugInteractor::isValid() const {return data(IsValid).toBool();}
bool DrugInteractor::isClass() const {return data(IsClass).toBool();}
bool DrugInteractor::isReviewed() const {return data(IsReviewed).toBool();}

/** Add an ATC link for this interactor. Interactor can be linked to multiple ATC codes */
void DrugInteractor::addAtcLink(const QString &atcCode)
{
    if (m_AtcLinks.contains(atcCode))
        return;
    m_AtcLinks.append(atcCode);
    m_AtcLinks.sort();
}

/**
 * Add scientific documentation, using pubmed PMID, for a specific child (\e chilId)
 * classification into this interactor.\n
 * Eg: Interactor1 is ClassOne, Interactor2 is a child of this ClassOne, and a scientific
 * documentation is used to prove this. You can set the PMID here.
 */
void DrugInteractor::addChildClassificationPMIDs(const QString &childId, const QStringList &pmids)
{
    foreach(const QString &pmid, pmids)
        m_ChildClassifPMIDs.insertMulti(childId, pmid);
}

/**
 * Returns all PMID related to the \e childId classification into this interactor
 * \sa addChildClassificationPMIDs()
 */
QStringList DrugInteractor::childClassificationPMIDs(const QString &childId) const
{
    // We must return the list in the correct order ==> reverse order of the map value
    const QStringList &list = m_ChildClassifPMIDs.values(childId);
    QStringList ret;
    for (int i = list.count()-1; i > -1; --i)
        ret << list.at(i);
    return ret;
}

/** Returns all needed PMID for this interactor */
QStringList DrugInteractor::allNeededPMIDs() const
{
    return m_ChildClassifPMIDs.values();
}

/** Transform this interactor into XML */
QString DrugInteractor::toXml() const
{
    QDomDocument doc("FreeMedForms");
    QDomElement root = doc.createElement(::XML_ROOT_TAG);
    doc.appendChild(root);

    QDomElement element = doc.createElement(::XML_INTERACTOR_TAG);
    root.appendChild(element);
    element.setAttribute(::XML_ID_ATTRIB, data(InitialLabel).toString());
    element.setAttribute(::XML_VALID_ATTRIB, data(IsValid).toBool());
    element.setAttribute(::XML_ISCLASS_ATTRIB, data(IsClass).toBool());
    element.setAttribute(::XML_REFERENCE_ATTRIB, data(Reference).toString());
    element.setAttribute(::XML_PMIDS_ATTRIB, data(PMIDsStringList).toStringList().join(";"));
    element.setAttribute(::XML_DATECREATE_ATTRIB, data(DateOfCreation).toDate().toString(Qt::ISODate));
    element.setAttribute(::XML_DATEUPDATE_ATTRIB, data(DateLastUpdate).toDate().toString(Qt::ISODate));
    element.setAttribute(::XML_WARNDUPLICATES_ATTRIB, data(DoNotWarnDuplicated).toInt());

    // add class information
    if (isClass()) {
        if (!data(ClassInformationFr).isNull()) {
            element = doc.createElement(::XML_CLASSINFORMATION_TAG);
            root.appendChild(element);
            element.setAttribute(::XML_LANG_ATTRIB, "fr");
            element.setAttribute(::XML_TRANSLATION_ATTRIB, data(ClassInformationFr).toString());
        }
        if (!data(ClassInformationEn).isNull()) {
            element = doc.createElement(::XML_CLASSINFORMATION_TAG);
            root.appendChild(element);
            element.setAttribute(::XML_LANG_ATTRIB, "en");
            element.setAttribute(::XML_TRANSLATION_ATTRIB, data(ClassInformationEn).toString());
        }
        if (!data(ClassInformationDe).isNull()) {
            element = doc.createElement(::XML_CLASSINFORMATION_TAG);
            root.appendChild(element);
            element.setAttribute(::XML_LANG_ATTRIB, "de");
            element.setAttribute(::XML_TRANSLATION_ATTRIB, data(ClassInformationDe).toString());
        }
    }

    // Add labels
    if (!data(FrLabel).isNull()) {
        element = doc.createElement(::XML_LABEL_TAG);
        root.appendChild(element);
        element.setAttribute(::XML_LANG_ATTRIB, "fr");
        element.setAttribute(::XML_NAME_ATTRIB, data(FrLabel).toString());
    }
    if (!data(EnLabel).isNull()) {
        element = doc.createElement(::XML_CLASSINFORMATION_TAG);
        root.appendChild(element);
        element.setAttribute(::XML_LANG_ATTRIB, "en");
        element.setAttribute(::XML_NAME_ATTRIB, data(EnLabel).toString());
    }
    if (!data(DeLabel).isNull()) {
        element = doc.createElement(::XML_CLASSINFORMATION_TAG);
        root.appendChild(element);
        element.setAttribute(::XML_LANG_ATTRIB, "de");
        element.setAttribute(::XML_NAME_ATTRIB, data(DeLabel).toString());
    }

    // Add ATC Codes
    const QStringList &atc = data(ATCCodeStringList).toStringList();
    if (atc.count() > 0) {
        element = doc.createElement(::XML_ATC_TAG);
        root.appendChild(element);
        element.setAttribute(::XML_ATCCODE_ATTRIB, atc.join(";"));
    }

    // Add children
    QStringList children = childrenIds();
    children.removeDuplicates();
    foreach(const QString &c, children) {
        element = doc.createElement(::XML_CHILD_TAG);
        root.appendChild(element);
        QStringList pmids = m_ChildClassifPMIDs.values(c);
        pmids.removeAll("");
        pmids.removeDuplicates();
        element.setAttribute(::XML_NAME_ATTRIB, c);
        element.setAttribute(::XML_PMIDS_ATTRIB, pmids.join(";"));
    }

    // Add Review info
    element = doc.createElement(::XML_OTHER_TAG);
    root.appendChild(element);
    element.setAttribute(::XML_COMMENT_ATTRIB, data(Comment).toString());
    element.setAttribute(::XML_ISREVIEW_ATTRIB, data(IsReviewed).toInt());
    element.setAttribute(::XML_REVIEWERS_ATTRIB, data(ReviewersStringList).toStringList().join(";"));
    element.setAttribute(::XML_DATEREVIEW_ATTRIB, data(DateOfReview).toDate().toString(Qt::ISODate));
    element.setAttribute(::XML_ISAUTOFOUND_ATTRIB, data(IsAutoFound).toInt());

    return QString("<?xml version='1.0' encoding='UTF-8'?>\n%1").arg(doc.toString(2));
}

/** Create a DDI::DrugInteractor from an XML content \e element */
DrugInteractor &DrugInteractor::fromDomElement(const QDomElement &element)
{
    DrugInteractor *di = new DrugInteractor;
    di->setData(IsDuplicated, false);
    if (element.tagName()!="I") {
        di->setData(IsValid, false);
        return *di;
    }
    // get attribs
    di->setData(InitialLabel, element.attribute("id"));
    di->setData(IsValid, element.attribute("v").toInt());
    bool isClass = element.attribute("c").toInt();
    di->setData(IsClass, isClass);
    di->setData(DoNotWarnDuplicated, element.attribute("nwd").toInt());
    di->setData(Reference, element.attribute("r"));
    di->setData(PMIDsStringList, element.attribute("p").split(";"));
    di->setData(DateOfCreation, QDate::fromString(element.attribute("dc"), Qt::ISODate));
    di->setData(DateLastUpdate, QDate::fromString(element.attribute("lu"), Qt::ISODate));

    // get class information
    if (isClass) {
        QDomElement ci = element.firstChildElement("CI");
        while (!ci.isNull()) {
            const QString &l = ci.attribute("l");
            if (l == "fr")
                di->setData(ClassInformationFr, ci.attribute("t"));
            else if (l == "en")
                di->setData(ClassInformationEn, ci.attribute("t"));
            else if (l == "de")
                di->setData(ClassInformationDe, ci.attribute("t"));
//            else if (l == "sp")
//                di->setData(ClassInformationEs, ci.attribute("t"));
            ci = ci.nextSiblingElement("CI");
        }
    }

    // get Labels
    QDomElement label = element.firstChildElement("L");
    while (!label.isNull()) {
        const QString &l = label.attribute("l");
        if (l == "fr")
            di->setData(FrLabel, label.attribute("n"));
        else if (l == "en")
            di->setData(EnLabel, label.attribute("n"));
        else if (l == "de")
            di->setData(DeLabel, label.attribute("n"));
        else if (l == "es")
            di->setData(EsLabel, label.attribute("n"));
        label = label.nextSiblingElement("L");
    }

    // get Review info
    QDomElement rev = element.firstChildElement("O");
    di->setData(Comment, rev.attribute("c"));
    di->setData(IsReviewed, rev.attribute("r"));
    di->setData(ReviewersStringList, rev.attribute("rv").split(";"));
    di->setData(DateOfReview, QDate::fromString(element.attribute("d"), Qt::ISODate));
    di->setData(IsAutoFound, rev.attribute("af"));

    // get children item
    QDomElement child = element.firstChildElement("M");
    while (!child.isNull()) {
        di->addChildId(child.attribute("n"));
        if (!child.attribute("p").isEmpty()) {
            di->addChildClassificationPMIDs(child.attribute("n"), child.attribute("p").split(";"));
        }
        child = child.nextSiblingElement("M");
    }

    // get ATC codes
    child = element.firstChildElement("ATC");
    while (!child.isNull()) {
        di->m_AtcLinks.append(child.attribute("a").split(";"));
        child = child.nextSiblingElement("ATC");
    }
    return *di;
}

/** Check interactor equality */
bool DrugInteractor::operator==(const DrugInteractor &other) const
{
    return (other._data == _data &&
            other.m_ParentIds ==  m_ParentIds &&
            other.m_ChildrenId== m_ChildrenId &&
            other.m_AtcLinks == m_AtcLinks &&
            other.m_ChildClassifPMIDs == m_ChildClassifPMIDs
            );
}

/** Sort helper (using DDI::DrugInteractor::ReadOnly_TranslatedLabel) */
bool DrugInteractor::lowerThan(const DrugInteractor &d1, const DrugInteractor &d2)
{
    bool d1IsClass, d2IsClass;
    d1IsClass = d1.isClass();
    d2IsClass = d2.isClass();
    if (d1IsClass && !d2IsClass)
        return true;
    if (d2IsClass && !d1IsClass)
        return false;
    return d1.data(DrugInteractor::ReadOnly_TranslatedLabel).toString() < d2.data(DrugInteractor::ReadOnly_TranslatedLabel).toString();
}
