#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets>
#include <QDialog>
#include <QLineEdit>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
   Q_OBJECT

public:
   bool is_closed = false;
   explicit Dialog(QWidget *parent = 0);
   double value;
   int need_to_show_id;
   ~Dialog();

private slots:
   void onStartPress();
   void onClosePress();

private:
   Ui::Dialog *ui;
   QLineEdit *r_field;
   QLabel *text;
   QCheckBox *simple_it_vis;
   QCheckBox *phi_it_vis;
   QFormLayout *layout;
   QCheckBox *seq_vis;
   QCheckBox *bifur_diag;
};

#endif // DIALOG_H
