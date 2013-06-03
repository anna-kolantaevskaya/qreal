#pragma once

#include <QWidget>
#include <QtGui>
#include <QDialog>
#include <QtCore/QSignalMapper>
#include "../models/logicalModelAssistApi.h"

namespace Ui {
	class createPatternDialog;
}


class createPatternDialog : public QDialog
{
	Q_OBJECT
public:
	explicit createPatternDialog(QWidget *parent);
	QList <QString> getFields();
	void setElementName(QString name);

signals:

private slots:
	void onOk();

private:
	/// Dialods ui.
	QString mQuan;
	QString mXShift;
	QString mYShift;
	Ui::createPatternDialog *mUi;
};

