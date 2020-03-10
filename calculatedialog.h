#ifndef CALCULATEDIALOG_H
#define CALCULATEDIALOG_H

#include <QDialog>

#include "dbservice.h"
#include "calculatelogic.h"

namespace Ui {
class CalculateDialog;
}

class CalculateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalculateDialog(DBService &dbs, const Patient &patient,
                             CalculateLogic &calculateLogic, QWidget *parent = nullptr);
    ~CalculateDialog();

private:
    Ui::CalculateDialog *ui;
};

#endif // CALCULATEDIALOG_H
