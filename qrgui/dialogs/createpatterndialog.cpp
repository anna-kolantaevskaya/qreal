#include "createpatterndialog.h"
#include "ui_createPatternDialog.h"

createPatternDialog::createPatternDialog(QWidget *parent) :
	QDialog(parent)
  , mUi(new Ui::createPatternDialog)
{
	mUi->setupUi(this);
	connect(mUi->okButton, SIGNAL(clicked()), this, SLOT(onOk()));
	setWindowTitle(tr("Creating pattern"));
}

void createPatternDialog::onOk(){
	mQuan = mUi->quanLine->text();
	mXShift = mUi->xShiftLine->text();
	mYShift = mUi->yShiftLine->text();
	this->close();
}

void createPatternDialog::setElementName(QString name){
	mUi->elementNameLabel->setText(name.operator +=(":"));
}

QList <QString> createPatternDialog::getFields(){
	QList<QString> res;
	res.append(mQuan);
	res.append(mXShift);
	res.append(mYShift);
	return res;
}

