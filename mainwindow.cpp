#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

int cursorLocation = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->inputFieldLineEdit, &QLineEdit::textEdited,this, &MainWindow::textInInputFieldEdited);
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onConvertButtonClicked);

    connect(ui->radioButtonFrom2, &QRadioButton::clicked, this, &MainWindow::on_radioButtonFrom2_clicked);
    connect(ui->radioButtonFrom8, &QRadioButton::clicked, this, &MainWindow::on_radioButtonFrom8_clicked);
    connect(ui->radioButtonFrom10, &QRadioButton::clicked, this, &MainWindow::on_radioButtonFrom10_clicked);
    connect(ui->radioButtonTo2, &QRadioButton::clicked, this, &MainWindow::on_radioButtonTo2_clicked);
    connect(ui->radioButtonTo8, &QRadioButton::clicked, this, &MainWindow::on_radioButtonTo8_clicked);
    connect(ui->radioButtonTo10, &QRadioButton::clicked, this, &MainWindow::on_radioButtonTo10_clicked);
    connect(ui->cleanButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyButtonClicked);
    ui->inputFieldLineEdit->setMaxLength(32);
    updateLabels();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::textInInputFieldEdited(){
    cursorLocation = ui->inputFieldLineEdit->cursorPosition();
    interfaceState.textInInputFieldEntered = YES;

    doOperation(Initialization, &context);
    strcat_s(context.initialValueFromLineEdit, (ui->inputFieldLineEdit->text()).toStdString().c_str());
    doOperation(Validation, &context);

    doOperation(CheckingStrIsEmpty, &context);
    doOperation(CheckingInputIsIncorrect, &context);
    doOperation(CheckingNumSystemsIsNotDefined, &context);


    if (context.strIsEmpty == YES){
        interfaceState.textInInputFieldEntered = NO;
        ui->statusField->setText("");
    }

    else if (context.strIsIncorrect == YES){
        ui->statusField->setText("Некорректный ввод");
        context.resultStr[0] = '\0';
    }
    else if (context.numSystemsIsNotDefined == YES)
        ui->statusField->setText("");

    else{
         ui->statusField->setText("Корректный ввод");
    }
    updateLabels();
}

void MainWindow::onConvertButtonClicked()
{
    doOperation(Initialization, &context);
    strcat(context.initialValueFromLineEdit, (ui->inputFieldLineEdit->text()).toStdString().c_str());
    doOperation(Validation, &context);

    if ((context.initialValueFromLineEdit[0] == '\0') && (interfaceState.fromNumSystemButtonSelected == YES) && (interfaceState.toNumSystemButtonSelected == YES)){ // Если ничего не введено но выбраны системв счисления
        ui->outputField->setText("");
        ui->statusField->setText("");
    }

    doOperation(CheckingConditionsForConvertion, &context);
    if (context.conditionsCompliance == YES){
        doOperation(Convertion, &context);
        if (context.currentNumSystem == 2){
            doOperation(ConvertionFromBinCode, &context);
        }

        if (context.currentNumSystem == 8){
            doOperation(ConvertionEightSystemToBinCode, &context);
            doOperation(CheckingEightSystemNumberIsDopCode, &context);
            if (context.conditionsCompliance == YES){
                doOperation(ConvertionFromBinCode, &context);
            }
        }
        updateLabels();
        }
    else{
        if (context.overFlowState == YES)
            QMessageBox::warning(this, "Ошибка!", "Переполнение");
        if (context.inputStatus == INCORRECT_INPUT)
            QMessageBox::warning(this, "Ошибка!", "Некорректный ввод");
        if ((interfaceState.fromNumSystemButtonSelected == NO) || (interfaceState.toNumSystemButtonSelected == NO))
            QMessageBox::warning(this, "Ошибка!", "Выберите системы счисления");
        }

}


void MainWindow::updateLabels(){
    ui->inputFieldLineEdit->setText(context.initialValueFromLineEdit);
    ui->inputFieldLineEdit->setCursorPosition(cursorLocation);
    ui->outputField->setText(context.resultStr);

}

void MainWindow::on_radioButtonFrom2_clicked()
{
    context.currentNumSystem = ui->radioButtonFrom2->text().toInt();
    interfaceState.fromNumSystemButtonSelected = YES;
    checkNumSystemsAndStrForButtons();
}

void MainWindow::on_radioButtonFrom8_clicked()
{
    context.currentNumSystem = ui->radioButtonFrom8->text().toInt();
    interfaceState.fromNumSystemButtonSelected = YES;
    checkNumSystemsAndStrForButtons();

}

void MainWindow::on_radioButtonFrom10_clicked()
{
    context.currentNumSystem = ui->radioButtonFrom10->text().toInt();
    interfaceState.fromNumSystemButtonSelected = YES;
    checkNumSystemsAndStrForButtons();
}

void MainWindow::on_radioButtonTo2_clicked()
{
    context.toNumSystem = ui->radioButtonTo2->text().toInt();
    interfaceState.toNumSystemButtonSelected = YES;
    checkNumSystemsAndStrForButtons();
}

void MainWindow::on_radioButtonTo8_clicked()
{
    context.toNumSystem = ui->radioButtonTo8->text().toInt();
    interfaceState.toNumSystemButtonSelected = YES;
    checkNumSystemsAndStrForButtons();
}

void MainWindow::on_radioButtonTo10_clicked()
{
    context.toNumSystem = ui->radioButtonTo10->text().toInt();
    interfaceState.toNumSystemButtonSelected = YES;
    checkNumSystemsAndStrForButtons();
}

void MainWindow::onClearButtonClicked(){
    doOperation(Initialization, &context);

    interfaceState.textInInputFieldEntered = NO;
    ui->statusField->setText("");
    updateLabels();
}


void MainWindow::checkNumSystemsAndStrForButtons()
{
    doOperation(Initialization, &context);
    strcat_s(context.initialValueFromLineEdit, (ui->inputFieldLineEdit->text()).toStdString().c_str());
    doOperation(Validation, &context);
    doOperation(CheckingStrIsIncorrect, &context);

    if ((interfaceState.textInInputFieldEntered == NO) && (interfaceState.fromNumSystemButtonSelected == YES) && (interfaceState.toNumSystemButtonSelected == YES)){
        ui->statusField->setText("");
        context.resultStr[0] = '\0';
    }

    if (interfaceState.textInInputFieldEntered == YES && context.overFlowState == NO && interfaceState.fromNumSystemButtonSelected == YES && interfaceState.toNumSystemButtonSelected == YES) //
        ui->statusField->setText("Корректный ввод");

    if (context.currentNumSystem == context.toNumSystem){
        ui->statusField->setText("");
        if ((context.currentNumSystem == context.toNumSystem) && (interfaceState.textInInputFieldEntered == YES))
            ui->statusField->setText("Корректный ввод");
    }
    if (context.strIsIncorrect == YES)
        ui->statusField->setText("Некорректный ввод");


    updateLabels();

}

void MainWindow::onCopyButtonClicked(){
    if (context.resultStr != "\0"){
        context.bufStr[0] = '\0';
        doOperation(Save, &context);
        updateLabels();
    }

}


