#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CalculatorWindow; }
QT_END_NAMESPACE

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private slots:
    void handleButtonClicked();
    void resizeEvent(QResizeEvent* e);

private:
    Ui::CalculatorWindow *ui;
    Calculator* calculator = new Calculator();
    int currentFontSize = 14;
};
#endif // CALCULATORWINDOW_H
