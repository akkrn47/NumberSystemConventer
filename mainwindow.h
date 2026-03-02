#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdlib.h>
#include "appcontext.h"
#include "entrypoint.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    AppContext context;
    InterfaceElementsState interfaceState;

    void textInInputFieldEdited();
    void onConvertButtonClicked();
    void updateLabels();
    void checkNumSystemsAndStrForButtons();
    void on_radioButtonFrom2_clicked();
    void on_radioButtonFrom8_clicked();
    void on_radioButtonFrom10_clicked();
    void on_radioButtonTo2_clicked();
    void on_radioButtonTo8_clicked();
    void on_radioButtonTo10_clicked();
    void onClearButtonClicked();
    void onCopyButtonClicked();


};
#endif // MAINWINDOW_H
