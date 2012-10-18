#include "addremovecombobox.h"

#include <coreplugin/itheme.h>
#include <coreplugin/icore.h>
#include <coreplugin/constants_icons.h>
#include <utils/log.h>
#include <translationutils/constanttranslations.h>
#include <translationutils/constants.h>

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStylePainter>
#include <QDebug>

using namespace Views;
using namespace Trans::ConstantTranslations;

static inline Core::ITheme *theme() { return Core::ICore::instance()->theme(); }

/*!
 * \class Views::AddRemoveComboBox
 * \brief This class provides a QComboBox with a label and a +/- button to add/remove items.
 *
 * The widget can be used instead of a QComboBox. Just set the model via setModel(), and connect to the events
 * for easy interactions with the UI around. Set the Model column via setModelColumn()
 *



/*! Default constructor */
AddRemoveComboBox::AddRemoveComboBox(QWidget *parent) :
    QWidget(parent)
{
    mLabel = new QLabel("");
    initialize();
}

/*! \brief Constructor with a given \e labelText
 *
 * Per default the label is placed on the left side of the ComboBox.
 */
AddRemoveComboBox::AddRemoveComboBox(const QString &labelText, QWidget *parent) :
    QWidget(parent)
{
    mLabel = new QLabel(labelText);
    initialize();
}

/*! Does all the work for the constructor: button creating, signal/slot connections. */
void AddRemoveComboBox::initialize()
{
    QHBoxLayout *layout = new QHBoxLayout();

    mCombo = new QComboBox(this);
    mCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mLabel->setBuddy(mCombo);

    mAddButton = new QPushButton(this);
    mAddButton->setMinimumSize(22, 22);
    mAddButton->setMaximumSize(22, 22);
    mAddButton->setIcon(theme()->icon(Core::Constants::ICONADD));

    mRemoveButton = new QPushButton(this);
    mRemoveButton->setMinimumSize(22, 22);
    mRemoveButton->setMaximumSize(22, 22);
    mRemoveButton->setIcon(theme()->icon(Core::Constants::ICONREMOVE));
    mRemoveButton->setEnabled(false);

    layout->addWidget(mLabel);
    layout->addWidget(mCombo);
    layout->addWidget(mAddButton);
    layout->addWidget(mRemoveButton);
    setLayout(layout);

    connect(mAddButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(mRemoveButton, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect(mCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(currentIndexChanged(int)));
    connect(mCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUi()));
}

/*! Default destructor*/
AddRemoveComboBox::~AddRemoveComboBox()
{
}

/*! Sets the label on the left of the QComboBox. */
void AddRemoveComboBox::setLabel(const QString &text)
{
    Q_ASSERT(mLabel);
    mLabel->setText(text);
}

/*! \brief Appends a new item to the ComboBox' model.
 *
 * After successfully inserting the item, the itemAdded(int) signal is emitted.
 * \sa removeItem, itemAdded, itemRemoved
 */
void AddRemoveComboBox::addItem()
{
    QAbstractItemModel *model = mCombo->model();
    if (!model)
        return;
    // insert an empty row
    if(!model->insertRow(model->rowCount()))
        LOG_ERROR("Unable to add row " + QString::number(mCombo->currentIndex()));

    // set the ComboBox to that row
    mCombo->setCurrentIndex(model->rowCount()-1);
    mRemoveButton->setEnabled(true);

    //inform other widgets of successfully added item
    Q_EMIT itemAdded(model->index(model->rowCount()-1, 0));
}

/*! \brief Removes the currentItem from the combobox model
 *
 * After succesful removal, the itemRemoved() signal is emitted.
 * \sa addItem, itemAdded, itemRemoved
 */
void AddRemoveComboBox::removeItem()
{
    QAbstractItemModel *model = mCombo->model();
    if (model->rowCount() == 0)
        return;

    if (!model->removeRow(mCombo->currentIndex())) {
          LOG_ERROR("Unable to remove row " + QString::number(mCombo->currentIndex()));
    }
    // check if there are any items left afterwords
    const bool enabled = (model->rowCount() > 0);
    mRemoveButton->setEnabled(enabled);
//    mCombo->setCurrentIndex(mCombo->count() - 1);

    // inform other widgets of change
    Q_EMIT itemRemoved();

}

/*! Updates the visual state of the UI: enables/disables widgets etc. */
void AddRemoveComboBox::updateUi()
{
    mRemoveButton->setEnabled(mCombo->currentIndex() != -1);
}

/*! Reimplemented event handler to handle state changes. Used for language change. */
void AddRemoveComboBox::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        mAddButton->setToolTip(tkTr(Trans::Constants::FILENEW_TEXT));
        mRemoveButton->setToolTip(tkTr(Trans::Constants::REMOVE_TEXT));
        break;
    default:
        break;
    }
}

/*! Sets the visible text of the actual item in the QComboBox. */
void AddRemoveComboBox::setEditText(const QString &text)
{
    mCombo->setEditText(text);
}

